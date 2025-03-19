# Creating a spark DataFrame from a list of data

#1. Generate a sample dictionary list with toy data
data =  [{"Category": 'A', "ID": 1, "Value": 121.44, "Truth": True},
	 {"Category": 'B', "ID": 2, "Value": 300.01, "Truth": False},
	 {"Category": 'c', "ID": 3, "Value": 10.99, "Truth": None},
	 {"Category": 'E', "ID": 4, "Value": 33.87, "Truth": True}
 ]

#2. Import and create a SparkSession
from pyspark.sql import SparkSession
spark = SparkSession.builder.getOrCreate()

#3. Create a DataFrame using the createDataFrame method
df = spark.createDataFrame(data)
print(type(df))
