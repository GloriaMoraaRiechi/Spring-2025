from pyspark.sql import SparkSession
from pyspark.sql.functions import col, regexp_replace, split, explode
from pyspark.ml.feature import Tokenizer, StopWordsRemover, HashingTF, IDF
from pyspark.ml.classification import LogisticRegression
from pyspark.ml import Pipeline

# Initialize spark session
spark = SparkSession.builder.appName("Covid19_Sentiment_Analysis").getOrCreate()

# Load Training Data
train_df = spark.read.csv("hdfs://localhost:9000/user/hadoop/assignment/training.csv", header=True, inferSchema=True)
train_df = train_df.withColumnRenamed("Tweet", "text").withColumnRenamed("Labels", "labels")
print("Ogininal Training Data:")
train_df.show(5)

# Preprocessing: cleaning of the text
def preprocess_text(df):
	df = df.withColumn("text", regexp_replace(col("text"), r"http\S+", "")) # Remove URLs
	df = df.withColumn("text", regexp_replace(col("text"), r"@\W+", "")) # Remove mentions
	df = df.withColumn("text", regexp_replace(col("text"), r"[^a-zA-Z ]", "")) # Remove special characters
	return df

train_df = preprocess_text(train_df)
print("Preprocessed Training Data:")
train_df.show(5)

train_df = train_df.drop("tokenized_words")

# Tokenization and StopWord Removal
tokenizer = Tokenizer(inputCol="text", outputCol="tokenized_words")
remover = StopWordsRemover(inputCol="tokenized_words", outputCol="filtered")

train_df = tokenizer.transform(train_df)
print("Tokenized Data:")
train_df.select("text", "tokenized_words").show(5, truncate=False)

train_df = remover.transform(train_df)
print("Stopwords Removed:")
train_df.select("tokenized_words", "filtered").show(5, truncate=False)

# Feature extraction
hashingTF = HashingTF(inputCol="filtered", outputCol="rawFeatures", numFeatures=10000)
train_df = hashingTF.transform(train_df)

idf = IDF(inputCol="rawFeatures", outputCol="features")
train_df = idf.fit(train_df).transform(train_df)
print("TF Features:")
train_df.select("filtered", "rawFeatures").show(5, truncate=False)

# Multi-label conversion: explode labels into multiple rows
train_df = train_df.withColumn("labels", split(col("labels"), r"\s+"))
train_df = train_df.withColumn("label", explode(col("labels")))
train_df = train_df.withColumn("label", col("label").cast("int"))
print("Exploaded labels:")
train_df.select("text", "label").show(5)
#train_df.select("text", "label").write.csv("/mnt/c/Users/glori/Desktop/Fundamentals of Big Data Analytics/Dataset/output1.csv", header=True)

# Train a logistic regression model
lr = LogisticRegression(featuresCol="features", labelCol="label", maxIter=10)

# Pipeline
pipeline = Pipeline(stages=[tokenizer, remover, hashingTF, idf, lr])
model = pipeline.fit(train_df)
