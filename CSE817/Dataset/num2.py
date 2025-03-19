# Import PySpark
from pyspark.sql import SparkSession
from pyspark.sql.functions import monotonically_increasing_id, col, when, isnan, count
from pyspark.ml.feature import Imputer, VectorAssembler, StringIndexer, ChiSqSelector
from pyspark.ml.classification import LogisticRegression, RandomForestClassifier, LinearSVC
from pyspark.ml.evaluation import MulticlassClassificationEvaluator
from pyspark.ml.tuning import CrossValidator, ParamGridBuilder
from functools import reduce

# Import Scikit-learn & SMOTE
import pandas as pd
from imblearn.over_sampling import SMOTE
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import StratifiedKFold, cross_val_score

# Initialize Spark session
spark = SparkSession.builder.appName("MulticlassClassification").getOrCreate()

# Load dataset from HDFS
train_data = spark.read.csv("hdfs:///user/hadoop/assignment/TrainData1.txt", sep=" ", inferSchema=True)
train_labels = spark.read.csv("hdfs:///user/hadoop/assignment/TrainLabel1.txt", inferSchema=True).toDF("label")

# Correct row alignment
train_data = train_data.withColumn("id", monotonically_increasing_id())
train_labels = train_labels.withColumn("id", monotonically_increasing_id())

# Join the training data and labels on the index
train_combined = train_data.join(train_labels, "id").drop("id")

# Confirm missing values
missing_condition = reduce(lambda a, b: a | b, [(col(c).isNull() | isnan(col(c))) for c in train_data.columns])
missing_rows = train_data.filter(missing_condition).count()
print(f"Number of rows with missing values: {missing_rows}")

# Handle missing values (KNN Imputation)
feature_cols = [col for col in train_combined.columns if col != "label"]
if missing_rows > 0:
    imputer = Imputer(inputCols=feature_cols, outputCols=feature_cols, strategy="mean")
    train_combined = imputer.fit(train_combined).transform(train_combined)
    print("Missing values imputed.")

# Feature Selection
feature_cols = [col for col in train_combined.columns if col != "label"]

# Convert categorical features to numerical
indexed_features = []
for col_name in feature_cols:
    if dict(train_combined.dtypes)[col_name] == "string":
        indexer = StringIndexer(inputCol=col_name, outputCol=f"{col_name}_indexed")
        train_combined = indexer.fit(train_combined).transform(train_combined)
        indexed_features.append(f"{col_name}_indexed")
    else:
        indexed_features.append(col_name)

# Assemble feature vector
vector_assembler = VectorAssembler(inputCols=indexed_features, outputCol="features")
train_combined = vector_assembler.transform(train_combined)

# Select features using Chi-Square
selector = ChiSqSelector(numTopFeatures=10, featuresCol="features", outputCol="selected_features", labelCol="label")
train_combined = selector.fit(train_combined).transform(train_combined)

# Convert Spark DataFrame to Pandas
train_pandas = train_combined.select("selected_features", "label").toPandas()
X = train_pandas["selected_features"].apply(lambda x: x.toArray()).tolist()
y = train_pandas["label"]

# Apply SMOTE for balancing classes
smote = SMOTE()
X_resampled, y_resampled = smote.fit_resample(X, y)

# Model Training
models = {
    "Logistic Regression": LogisticRegression(),
    "Random Forest": RandomForestClassifier(numTrees=50, maxBins=100),
    "SVM (Linear Kernel)": LinearSVC(),
}

# Train KNN with different k values
for k in [1, 2, 5, 10, 20]:
    knn = KNeighborsClassifier(n_neighbors=k)
    cv = StratifiedKFold(n_splits=5)  # Ensure balanced splits
    scores = cross_val_score(knn, X_resampled, y_resampled, cv=cv, scoring="accuracy")
    print(f"KNN (K={k}) - Mean Accuracy: {scores.mean():.4f}")

# Cross-Validation (3, 5, 10 folds)
cross_val_results = {}
for k in [3, 5, 10]:
    print(f"\nRunning {k}-Fold Cross Validation...")

    for model_name, model in models.items():
        evaluator = MulticlassClassificationEvaluator(metricName="accuracy")
        param_grid = ParamGridBuilder().build()
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

# Print Final Results
print("\nFinal Model Accuracies:")
for (model_name, k), acc in cross_val_results.items():
    print(f"{model_name} with {k}-Fold CV: {acc:.4f}")

