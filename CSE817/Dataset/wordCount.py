from pyspark.sql import SparkSession

# Initialize spark
spark = SparkSession.builder .appName("WordCount").getOrCreate()
spark.sparkContext.setLogLevel("ERROR")

sc = spark.sparkContext

# Read the text file into RDD
rdd = sc.textFile("hdfs://localhost:9000/user/hadoop/assignment/wc.txt")

# Perform word count using mapreduce
word_counts = (rdd.flatMap(lambda line: line.split())
               .map(lambda word: (word, 1))
               .reduceByKey(lambda a, b: a + b))
results = word_counts.collect()
print(f"{'Word':20} | {'Count':5}")
print("-" * 30)
for word, count in results:
    print(f"{word:20} | {count:5}")

#for word, count in word_counts.collect():
#    print(f"{word}: {count}")

spark.stop()
