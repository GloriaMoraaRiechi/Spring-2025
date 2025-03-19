from pyspark.sql import SparkSession
from pyspark.sql.functions import monotonically_increasing_id, col, when, isnan, count
from pyspark.ml.feature import Imputer, VectorAssembler, StringIndexer, ChiSqSelector
from pyspark.ml.classification import LogisticRegression, RandomForestClassifier, LinearSVC
from pyspark.ml.evaluation import MulticlassClassificationEvaluator, BinaryClassificationEvaluator
from pyspark.ml.tuning import CrossValidator, ParamGridBuilder
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import StratifiedKFold, cross_val_score
import pandas as pd
from functools import reduce

# Initialize Spark Session
spark = SparkSession.builder.appName("MulticlassClassification").getOrCreate()

# Load Data
train_data = spark.read.csv("hdfs:///user/hadoop/assignment/TrainData1.txt", sep=" ", inferSchema=True)
train_labels = spark.read.csv("hdfs:///user/hadoop/assignment/TrainLabel1.txt", inferSchema=True).toDF("label")

# Align Data Using an Index Column
train_data = train_data.withColumn("id", monotonically_increasing_id())
train_labels = train_labels.withColumn("id", monotonically_increasing_id())

# Join the training data and labels on the index
train_combined = train_data.join(train_labels, "id").drop("id")

# Check for Missing Values
missing_counts = train_combined.select([count(when(col(c).isNull(), c)).alias(c) for c in train_combined.columns]).collect()
has_missing_values = any(row[c] > 0 for row in missing_counts for c in row.asDict())

# Impute Missing Values (KNN-like imputation using Spark's Imputer)
feature_cols = [col for col in train_combined.columns if col != "label"]

if has_missing_values:
    imputer = Imputer(inputCols=feature_cols, outputCols=feature_cols)
    train_combined = imputer.fit(train_combined).transform(train_combined)
    print("Imputation completed.")
else:
    print("No missing values detected. Skipping imputation.")

# Feature Selection
# Convert Categorical Features Using StringIndexer
indexed_features = []
indexers = []
for col_name in feature_cols:
    if dict(train_combined.dtypes)[col_name] == "string":
        indexer = StringIndexer(inputCol=col_name, outputCol=f"{col_name}_indexed")
        train_combined = indexer.fit(train_combined).transform(train_combined)
        indexed_features.append(f"{col_name}_indexed")
        indexers.append(indexer)
    else:
        indexed_features.append(col_name)

# Convert Features into a Single Vector Column
vector_assembler = VectorAssembler(inputCols=indexed_features, outputCol="features")
train_combined = vector_assembler.transform(train_combined)

# Apply Chi-Square Feature Selection
selector = ChiSqSelector(numTopFeatures=10, featuresCol="features", outputCol="selected_features", labelCol="label")
train_combined = selector.fit(train_combined).transform(train_combined)

# Keep only the selected features and label
train_combined = train_combined.select("selected_features", "label").withColumnRenamed("selected_features", "features")

# Convert Spark DataFrame to Pandas for KNN Training
train_pandas = train_combined.toPandas()
X = train_pandas["features"].apply(lambda x: x.toArray()).tolist()
y = train_pandas["label"]

# Model Training
models = {
    "Logistic Regression": LogisticRegression(),
    "Random Forest": RandomForestClassifier(numTrees=50, maxBins=32),
    "SVM (Linear Kernel)": LinearSVC(),
}

# Train KNN Using Scikit-learn
for k in [1, 2, 5, 10, 20]:
    knn = KNeighborsClassifier(n_neighbors=k)
    scores = cross_val_score(knn, X, y, cv=5, scoring="accuracy")
    print(f"KNN (K={k}) - Mean Accuracy: {scores.mean():.4f}")

# Define Cross-Validation (3, 5, 10 Folds)
cv = StratifiedKFold(n_splits=5)
scores = cross_val_score(knn, X, y, cv=cv, scoring="accuracy")
for k in [3, 5, 10]:
    print(f"\nRunning {k}-Fold Cross Validation...")

    for model_name, model in models.items():
        evaluator = MulticlassClassificationEvaluator(metricName="accuracy")

        param_grid = ParamGridBuilder() \
            .addGrid(models["Logistic Regression"].regParam, [0.01, 0.1, 1.0]) \
            .addGrid(models["Random Forest"].numTrees, [50, 100, 200]) \
            .build()

        cross_val = CrossValidator(
            estimator=model,
            estimatorParamMaps=param_grid,
            evaluator=evaluator,
            numFolds=k
        )

        # Train Model
        cv_model = cross_val.fit(train_combined)
        accuracy = evaluator.evaluate(cv_model.transform(train_combined))
        cross_val_results[(model_name, k)] = accuracy

        print(f"{model_name} ({k}-Fold CV) - Accuracy: {accuracy:.4f}")

# Compute Evaluation Metrics
evaluator = MulticlassClassificationEvaluator(labelCol="label")

for metric in ["accuracy", "weightedPrecision", "weightedRecall", "f1"]:
    score = evaluator.evaluate(cv_model.transform(train_combined), {evaluator.metricName: metric})
    print(f"{metric}: {score:.4f}")

# Compute AUC and ROC Curve
binary_evaluator = BinaryClassificationEvaluator(labelCol="label", metricName="areaUnderROC")
auc = binary_evaluator.evaluate(cv_model.transform(train_combined))
print(f"AUC: {auc:.4f}")

# Print Final Cross-Validation Results
print("\nFinal Model Accuracies:")
for (model_name, k), acc in cross_val_results.items():
    print(f"{model_name} with {k}-Fold CV: {acc:.4f}")

