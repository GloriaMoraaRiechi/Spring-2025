from pyspark.sql import SparkSession
from pyspark.sql.functions import col, monotonically_increasing_id
from pyspark.ml.feature import Imputer, VectorAssembler, StringIndexer
from pyspark.ml.classification import LogisticRegression, RandomForestClassifier
from pyspark.ml.evaluation import MulticlassClassificationEvaluator
from pyspark.ml.tuning import CrossValidator, ParamGridBuilder

# Initialize Spark session
spark = SparkSession.builder.appName("MulticlassClassification").getOrCreate()

# Load TrainData1 and TrainLabel1 from HDFS
train_data = spark.read.csv("hdfs:///user/hadoop/assignment/TrainData1.txt", sep=" ", inferSchema=True)
train_labels = spark.read.csv("hdfs:///user/hadoop/assignment/TrainLabel1.txt", inferSchema=True).toDF("label")

# Convert all columns to numeric
train_data = train_data.select([col(c).cast("double") for c in train_data.columns])

# Ensure correct row-wise alignment using an index
train_data = train_data.withColumn("id", monotonically_increasing_id())
train_labels = train_labels.withColumn("id", monotonically_increasing_id())

# Join the training data and labels on the index and drop the temporary id column
train_combined = train_data.join(train_labels, "id").drop("id")

# Handle missing values using Imputer
feature_cols = train_combined.columns[:-1]  # All columns except 'label'
imputer = Imputer(inputCols=feature_cols, outputCols=feature_cols)
train_combined = imputer.fit(train_combined).transform(train_combined)

# Convert categorical labels to numerical labels
indexer = StringIndexer(inputCol="label", outputCol="indexedLabel")
train_combined = indexer.fit(train_combined).transform(train_combined)

# Assemble features into a single vector
assembler = VectorAssembler(inputCols=feature_cols, outputCol="features")
train_combined = assembler.transform(train_combined).select("features", "indexedLabel")

# Split data into training and testing sets
train_data, test_data = train_combined.randomSplit([0.8, 0.2], seed=42)

# Define classifiers
lr = LogisticRegression(labelCol="indexedLabel", featuresCol="features")
rf = RandomForestClassifier(labelCol="indexedLabel", featuresCol="features")

# Define evaluation metric
evaluator = MulticlassClassificationEvaluator(labelCol="indexedLabel", metricName="accuracy")

# Cross-validation setup for Logistic Regression
paramGrid = ParamGridBuilder().addGrid(lr.regParam, [0.01, 0.1, 1.0]).build()
crossval = CrossValidator(estimator=lr, estimatorParamMaps=paramGrid, evaluator=evaluator, numFolds=5)

# Train and evaluate Logistic Regression model
cvModel = crossval.fit(train_data)
lr_predictions = cvModel.transform(test_data)
lr_accuracy = evaluator.evaluate(lr_predictions)

# Train and evaluate Random Forest model
rf_model = rf.fit(train_data)
rf_predictions = rf_model.transform(test_data)
rf_accuracy = evaluator.evaluate(rf_predictions)

# Print model performance
print(f"Logistic Regression Accuracy: {lr_accuracy}")
print(f"Random Forest Accuracy: {rf_accuracy}")

# Stop Spark session
spark.stop()

