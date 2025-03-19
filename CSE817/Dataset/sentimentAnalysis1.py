from pyspark.sql import SparkSession
from pyspark.sql.functions import col, regexp_replace, split, explode
from pyspark.ml.feature import Tokenizer, StopWordsRemover, HashingTF, IDF
from pyspark.ml.classification import LogisticRegression
from pyspark.ml import Pipeline

# Initialize Spark session
spark = SparkSession.builder.appName("Covid19_Sentiment_Analysis").getOrCreate()

# Load Training Data
train_df = spark.read.csv("hdfs://localhost:9000/user/hadoop/assignment/training.csv", header=True, inferSchema=True)
train_df = train_df.withColumnRenamed("Tweet", "text").withColumnRenamed("Labels", "labels")
print("Original Training Data:")
train_df.show(5)

# Preprocessing: cleaning of the text
def preprocess_text(df):
    df = df.withColumn("text", regexp_replace(col("text"), r"http\S+", ""))  # Remove URLs
    df = df.withColumn("text", regexp_replace(col("text"), r"@\W+", ""))  # Remove mentions
    df = df.withColumn("text", regexp_replace(col("text"), r"[^a-zA-Z ]", ""))  # Remove special characters
    return df

train_df = preprocess_text(train_df)
print("Preprocessed Training Data:")
train_df.show(5)

# Tokenization
tokenizer = Tokenizer(inputCol="text", outputCol="tokenized_text")  # Tokenize the text

train_df = tokenizer.transform(train_df)
print("Tokenized Data:")
train_df.select("text", "tokenized_text").show(5, truncate=False)

# StopWords Removal
remover = StopWordsRemover(inputCol="tokenized_text", outputCol="filtered_text")  # Remove stop words
train_df = remover.transform(train_df)
print("Stopwords Removed:")
train_df.select("tokenized_text", "filtered_text").show(5, truncate=False)

# Feature extraction using HashingTF and IDF
hashingTF = HashingTF(inputCol="filtered_text", outputCol="rawFeatures", numFeatures=10000)
train_df = hashingTF.transform(train_df)
idf = IDF(inputCol="rawFeatures", outputCol="features")

# Fit IDF model on the training data
idf_model = idf.fit(train_df)
train_df = idf_model.transform(train_df)

print("TF Features for Training Data:")
train_df.select("filtered_text", "rawFeatures", "features").show(5, truncate=False)

# Multi-label conversion: explode labels into multiple rows
train_df = train_df.withColumn("labels", split(col("labels"), r"\s+"))
train_df = train_df.withColumn("label", explode(col("labels")))
train_df = train_df.withColumn("label", col("label").cast("int"))
print("Exploded labels:")
train_df.select("text", "label").show(5)

# Train a logistic regression model
lr = LogisticRegression(featuresCol="features", labelCol="label", maxIter=10)

# Fit the model
lr_model = lr.fit(train_df)

# Make predictions on the training data
predictions = lr_model.transform(train_df)
predictions.select("text", "label", "prediction").show(5, truncate=False)

# Load validation data
val_df = spark.read.csv("hdfs://localhost:9000/user/hadoop/assignment/Validation.csv", header=True, inferSchema=True)
val_df = val_df.withColumnRenamed("Tweet", "text")
val_df = preprocess_text(val_df)
print("Validation Data:")
val_df.show(5)

# Tokenize, remove stop words, and extract features for validation data
val_df = tokenizer.transform(val_df)
val_df = remover.transform(val_df)
val_df = hashingTF.transform(val_df)

# Use the fitted IDF model to transform the validation data
val_df = idf_model.transform(val_df)

print("Validation Data with Features:")
val_df.select("text", "features").show(5, truncate=False)

# Predict sentiments on validation data
predictions = lr_model.transform(val_df)
print("Predictions:")
predictions.select("ID", "text", "prediction").show(10, truncate=False)

# Save predictions to CSV
predictions.select("ID", "prediction").write.csv("predictions.csv", header=True)

# Stop the Spark session
spark.stop()

