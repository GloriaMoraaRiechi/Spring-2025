# Creating a DataFrame from RDD

#1. make a dictionary list containing toy data
data =  [('A', 1, 121.44, True),
         ('B', 2, 300.01, False),
         ('C', 3, 10.99, None),
         ('E', 4, 33.87, True)]

#2. Import and create a sparkContext
from pyspark.sql import SparkSession

# Initialize spark session
spark = SparkSession.builder.appName("projectName").master("local[*]").getOrCreate()

#3. Generate an RDD from the created data
rdd = spark.sparkContext.parallelize(data)
print(type(rdd))


#4. define column names for the DataFrame
columns = ["Category", "ID", "Value", "Truth"]

#5. Convert RDD to DataFrame using toDf()
df = rdd.toDF(columns)

df.show()
