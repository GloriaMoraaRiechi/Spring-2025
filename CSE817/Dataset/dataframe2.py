# Creating a DataFrame from RDD

#1. make a dictionary list containing toy data
data =  [{"Category": 'A', "ID": 1, "Value": 121.44, "Truth": True},
         {"Category": 'B', "ID": 2, "Value": 300.01, "Truth": False},
         {"Category": 'c', "ID": 3, "Value": 10.99, "Truth": None},
         {"Category": 'E', "ID": 4, "Value": 33.87, "Truth": True}
 ]

#2. Import and create a sparkContext
from pyspark.sql import SparkSession
from pyspark import SparkContext, SparkConf

# Initialize spark session
spark = SparkSession.builder.appName("projectName").master("local[*]").getOrCreate()

#3. Generate and RDD from the created data
rdd = spark.sparkContext.parallelize(data)
print(type(rdd))


#4. Convert RDD to  DataFrame
df = spark.createDataFrame(rdd)
print(type(df))

df.show()
