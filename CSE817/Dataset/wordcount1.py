from pyspark.sql import SparkSession

# Initialize Spark
spark = SparkSession.builder.appName("WordCount").getOrCreate()
spark.sparkContext.setLogLevel("ERROR")
sc = spark.sparkContext

# Read the text file from HDFS (Dataset directory)
rdd = sc.textFile("hdfs://localhost:9000/user/hadoop/assignment/wc.txt")

# Perform word count using mapreduce
word_counts = (rdd.flatMap(lambda line: line.split())
               .map(lambda word: (word, 1))
               .reduceByKey(lambda a, b: a + b))

# Collect the results
results = word_counts.collect()

# Specify the local output path (your local directory)
output_path = "/mnt/c/Users/glori/Desktop/Fundamentals of Big Data Analytics/Dataset/output.txt"

# Save the results to the local output path
with open(output_path, 'w') as f:
    for word, count in results:
        f.write(f"{word}: {count}\n")

spark.stop()

print(f"Output saved to {output_path}")

