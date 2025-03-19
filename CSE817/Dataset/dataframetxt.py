# Read csv, txt and json and convert to DataFrame

# Import spark session
from pyspark.sql import SparkSession

# Initialize SparkSession
spark = SparkSession.builder.appName("dataFramesFromRDD").master("local[*]").getOrCreate()

# Create spark context
sc = spark.sparkContext

#. Read the CSV file into RDD
csvPath = "hdfs://localhost:9000/user/hadoop/assignment/data.csv"
csvRDD = sc.textFile(csvPath)

# Extract header
header = csvRDD.first()
csvRDD = csvRDD.filter(lambda row: row != header).map(lambda line: line.split(",")

# Convert RDD to dataframe
dfCSV = csvRDD.toDF("column1", "column2", "column3"])

dfCSV.show()

# TXT
# Read txt into RDD
txtPath = "hdfs://localhost:9000/user/hadoop/assignment/data.txt"
txtRDD = sc.textFile(txtPath)

# Convert RDD to dataframe
dfTXT = txtRDD.toDF(["value"])

dfTXT.show()

#JSON
import json

# Read json into RDD
jsonPath = "hdfs://localhost:9000/user/hadoop/assignment/data.json"
jsonRDD = sc.textFile(jsonPath) 

# Convert RDD to dataframe
dfJSON = spark.createDataFrame(jsonRDD)

dfJSON.show()
dfJSON.printSchema()
