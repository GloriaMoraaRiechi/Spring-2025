from pyspark.sql import SparkSession
from pyspark.ml.feature import HashingTF, IDF, Tokenizer
from pyspark.ml import Pipeline
from pyspark.sql.functions import array_contains, col

spark = SparkSession.builder.appName("NLPFeatureExtractionHashingTF").getOrCreate()

# Load Dataset
file_path = "hdfs://localhost:9000/user/hadoop/assignment/shakespeare.txt"
data = spark.read.csv(file_path, header=False, inferSchema=True, sep="\t")

#data.show(10, truncate=False)
#data.printSchema()

data = data.withColumnRenamed("_c0", "value")
data.show(10, truncate=False)
data.printSchema()

# Split the sentences into individual words (creates a new column "words"
tokenizer = Tokenizer(inputCol="value", outputCol="words")
tokenizedData = tokenizer.transform(data)
tokenizedData.select("value", "words").show(5, truncate=False)

# Convert the words into a fixed-length numerical factor
hashingTF = HashingTF(inputCol="words", outputCol="rawFeatures", numFeatures=1000)
hashedData = hashingTF.transform(tokenizedData)
#hashedData.select("words", "rawFeatures").show(truncate=False)

# Apply inverse document frequency (determines how important a word is by computing the term frequency inverse document frequency)
idf = IDF(inputCol="rawFeatures", outputCol="features")

idfModel = idf.fit(hashedData) # fit the IDF model on the hashed data
idfData = idfModel.transform(hashedData) 
#idfData.select("words", "features").show(truncate=False)

# Combine all the transformations into a single workflow
pipeline = Pipeline(stages=[tokenizer, hashingTF, idf])

# Fit and transform the data
model = pipeline.fit(data)
result = model.transform(data)
result.select("value", "features").show(5, truncate=False)

# Search for "grief"
keyword = "grief"
filteredResult = result.filter(array_contains(col("words"), keyword))
filteredResult.show(truncate=False)
