from pyspark.sql import SparkSession
from pyspark.ml.feature import Imputer, VectorAssembler, StringIndexer
from pyspark.ml.classification import LogisticRegression, RandomForestClassifier
from pyspark.ml.evaluation import MulticlassClassificationEvaluator
from pyspark.ml.tuning import CrossValidator, ParamGridBuilder

# Initialize Spark session
spark = SparkSession.builder.appName("MulticlassClassification").getOrCreate()

# Load TrainData1 and TrainLabel1 from HDFS
train_data = spark.read.csv("hdfs:///user/hadoop/assignment/TrainData1.txt", sep=" ", inferSchema=True)
train_labels = spark.read.csv("hdfs:///user/hadoop/assignment/TrainLabel1.txt", sep=" ", inferSchema=True).toDF("label")

# Combine train data and labels into one dataset
train_combined = train_data.withColumn("label", train_labels["label"])

# Handle missing values using Imputer
imputer = Imputer(inputCols=train_combined.columns[:-1], outputCols=train_combined.columns[:-1])
train_combined = imputer.fit(train_combined).transform(train_combined)

# Convert categorical labels to numerical labels
indexer = StringIndexer(inputCol="label", outputCol="indexedLabel")
train_combined = indexer.fit(train_combined).transform(train_combined)

# Assemble features into a single vector
assembler = VectorAssembler(inputCols=train_combined.columns[:-1], outputCol="features")
train_combined = assembler.transform(train_combined).select("features", "indexedLabel")

# Split data into training and testing sets
train_data, test_data = train_combined.randomSplit([0.8, 0.2], seed=42)

# Define classifiers
lr = LogisticRegression(labelCol="indexedLabel", featuresCol="features")
rf = RandomForestClassifier(labelCol="indexedLabel", featuresCol="features")

# Define evaluation metric
evaluator = MulticlassClassificationEvaluator(labelCol="indexedLabel", metricName="accuracy")

# Cross-validation setup
paramGrid = ParamGridBuilder().addGrid(lr.regParam, [0.01, 0.1, 1.0]).build()
crossval = CrossValidator(estimator=lr, estimatorParamMaps=paramGrid, evaluator=evaluator, numFolds=5)

# Train and evaluate models
cvModel = crossval.fit(train_data)
lr_predictions = cvModel.transform(test_data)
lr_accuracy = evaluator.evaluate(lr_predictions)

rf_model = rf.fit(train_data)
rf_predictions = rf_model.transform(test_data)
rf_accuracy = evaluator.evaluate(rf_predictions)

print(f"Logistic Regression Accuracy: {lr_accuracy}")
print(f"Random Forest Accuracy: {rf_accuracy}")

spark.stop()

