from pyspark.sql import SparkSession
from pyspark.sql.functions import monotonically_increasing_id
from pyspark.ml.feature import Imputer, VectorAssembler, StringIndexer, ChiSqSelector
from pyspark.ml.classification import LogisticRegression, RandomForestClassifier, LinearSVC
from sklearn.neighbors import KNeighborsClassifier
from pyspark.ml.evaluation import MulticlassClassificationEvaluator
from pyspark.ml.tuning import CrossValidator, ParamGridBuilder
from pyspark.sql.functions import col, when, isnan, isnull, count
from functools import reduce
from sklearn.model_selection import cross_val_score
from functools import reduce
import pandas as pd

# Initialize spark session
spark = SparkSession.builder.appName("MulticlassClassification").getOrCreate()

# Load the data
train_data = spark.read.csv("hdfs:///user/hadoop/assignment/TrainData1.txt", sep=" ", inferSchema=True)
train_labels = spark.read.csv("hdfs:///user/hadoop/assignment/TrainLabel1.txt", inferSchema=True).toDF("label")

train_data.show(5)
train_labels.show(5)

# Correct rwo-wise alignment using an index
train_data = train_data.withColumn("id", monotonically_increasing_id())
train_labels = train_labels.withColumn("id", monotonically_increasing_id())

#train_data.show(5)
#train_labels.show(5)

# Join the training data and labels on the index
train_combined = train_data.join(train_labels, "id").drop("id")

train_combined.printSchema()
train_combined.show(5)

# Check if there are missing values
missing_condition = reduce(
        lambda a, b: a | b,
        [(col(c).isNull() | isnan(col(c))) for c in train_data.columns]
)

missing_rows = train_data.filter(missing_condition).count()

print(f"Number of rows with missing values: {missing_rows}")
# Count the number of null values in each column
#train_combined.select([count(when(col(c).isNull(), c)).alias(c) for c in train_combined.columns]).show()

# Convert categorical labels to numerical labels
#feature_cols = train_combined.columns[:-1] # exlude the label
#for col_name in feature_cols:
#    train_combined = train_combined.withColumn(col_name, col(col_name).cast("float"))

# Handle missing values
#imputer = Imputer(inputCols=feature_cols, outputCols=feature_cols)
#train_combined = imputer.fit(train_combined).transform(train_combined)

feature_cols = [col for col in train_combined.columns if col != "label"]

# 1. Handle missing values
missing_counts = train_combined.select([count(when(col(c).isNull(), c)).alias(c) for c in train_combined.columns]).collect()
has_missing_values = any(row[c] > 0 for row in missing_counts for c in row.asDict())


if has_missing_values:
    imputer = Imputer(inputCols=feature_cols, outputCols=feature_cols)
    train_combined = imputer.fit(train_combined).transform(train_combined)
    print("Imputation completed.")
else:
    print("No missing values detected. Skipping imputation.")

# 2. FEATURE SELECTION
from pyspark.ml.feature import VectorAssembler, StringIndexer

# Identify feature columns (excluding label)
feature_cols = [col for col in train_combined.columns if col != "label"]

# Convert string columns to numerical format
indexed_features = []
indexers = []
for col_name in feature_cols:
    if dict(train_combined.dtypes)[col_name] == "string":  # Check if column is string
        indexer = StringIndexer(inputCol=col_name, outputCol=f"{col_name}_indexed")
        train_combined = indexer.fit(train_combined).transform(train_combined)
        indexed_features.append(f"{col_name}_indexed")
        indexers.append(indexer)
    else:
        indexed_features.append(col_name)

# Step 1: Convert feature columns into a single vector column
vector_assembler = VectorAssembler(inputCols=indexed_features, outputCol="features")
train_combined = vector_assembler.transform(train_combined)

# Step 2: Select only the transformed features and label
train_combined = train_combined.select("features", "label")

train_combined.show(5)


# Feature selection using Chi-Square test
selector = ChiSqSelector(numTopFeatures=10, featuresCol="features", outputCol="selected_features", labelCol="label")
train_combined = selector.fit(train_combined).transform(train_combined)

train_combined.select("selected_features", "label").show(5)

# Convert Spark DataFrame to Pandas
train_pandas = train_combined.toPandas()
X = train_pandas["features"].apply(lambda x: x.toArray()).tolist()  # Convert to list of NumPy arrays
y = train_pandas["label"]


# 3. MODEL TRAINING
models = {
    "Logistic Regression": LogisticRegression(),
    "Random Forest": RandomForestClassifier(numTrees=50, maxBins=100),
    "SVM (Linear Kernel)": LinearSVC(),
}

# Train KNN using Scikit-learn (k=1,2,5,10,20)
for k in [1, 2, 5, 10, 20]:
    knn = KNeighborsClassifier(n_neighbors=k)
    scores = cross_val_score(knn, X, y, cv=5, scoring="accuracy")  # 5-Fold Cross Validation
    print(f"KNN (K={k}) - Mean Accuracy: {scores.mean():.4f}")

# Define Cross Validation with 3, 5, and 10 folds
cross_val_results = {}
for k in [3, 5, 10]:
    print(f"\nRunning {k}-Fold Cross Validation...")
    
    for model_name, model in models.items():
        evaluator = MulticlassClassificationEvaluator(metricName="accuracy")

        param_grid = ParamGridBuilder().build()  # Default hyperparameter tuning
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

# Print Final Cross Validation Results
print("\nFinal Model Accuracies:")
for (model_name, k), acc in cross_val_results.items():
    print(f"{model_name} with {k}-Fold CV: {acc:.4f}")

