# Create SparkSession and sparkcontext
from pyspark.sql import SparkSession

spark = SparkSession.builder.master("local").appName('FirstProgram').getOrCreate()
sc = spark.sparkContext

# Read the input file
text_file = sc.textFile("hdfs://localhost:9000/user/hadoop/assignment/firstprogram.txt")
counts = text_file.flatMap(lambda line: line.split(" ")).map(lambda word: (word, 1)).reduceByKey(lambda x, y: x + y)

# Printing each word with its respective count
output = counts.collect()
for word, count in output:
	print(word, count)


