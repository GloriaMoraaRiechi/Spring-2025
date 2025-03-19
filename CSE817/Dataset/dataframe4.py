# Read csv and convert to DataFrame
from pyspark.sql import SparkSession

#1. Initialize SparkSession
spark = SparkSession.builder.appName("CSVtoDataFrame").master("local[*]").getOrCreate()

#2. Read the CSV file into a DataFrame
hdfs_path = "hdfs://localhost:9000/user/hadoop/assignment/data.csv"
df = spark.read.csv(hdfs_path, header=True, inferSchema=True)

df.show()

