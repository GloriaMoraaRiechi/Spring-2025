# word2Vec converts words into numerical vector representations to find similarities between them

from pyspark.sql import SparkSession
from pyspark.ml.feature import Tokenizer, Word2Vec
from pyspark.sql.functions import col

spark = SparkSession.builder.appName("NLPFeatureExtractionWord2Vec").getOrCreate()

# Load the dataset
file_path = "hdfs://localhost:9000/user/hadoop/assignment/shakespeare.txt"
data = spark.read.csv(file_path, header=False, inferSchema=True, sep="\t")

# Rename column
data = data.withColumnRenamed("_c0", "value")
data.show(5, truncate=False)

# Split the sentences into individual words
tokenizer = Tokenizer(inputCol="value", outputCol="words")
wordsData = tokenizer.transform(data)
wordsData.select("value", "words").show(5, truncate=False)

# Convert the words into numerical vector representations
word2Vec = Word2Vec(vectorSize=3, minCount=0, inputCol="words", outputCol="result")
model = word2Vec.fit(wordsData)

# Transform the data to get word vectors (each sentence is converted to sentence-level embeddings
result = model.transform(wordsData)
result.select("words", "result").show(5, truncate=False)

# Get word vector for a specific word
word = "grief"
wordVector = model.getVectors().filter(f"word == '{word}'")
wordVector.show(truncate=False)

# Find similar words
synonyms = model.findSynonyms("love", 5)
synonyms.show(truncate=False)
