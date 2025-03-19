from pyspark.sql import SparkSession
from pyspark.sql.functions import col, avg

# Initialize Spark Session
spark = SparkSession.builder.appName("Car Data Analysis").getOrCreate()

# Load data
df = spark.read.csv("hdfs://localhost:9000/user/hadoop/assignment/mcar.txt", header=True, inferSchema=True)

# a) Create and display Spark DataFrames
print("Entire DataFrame: ")
df.show(n=1000, truncate=False)

# b) Filter the DataFrame to only retain rows with mpg less than 18
filtered_df = df.filter(df['mpg'] < 18)
print("Filtered Dataframe: ")
filtered_df.show(n=100, truncate=False)

# c) Compute the average weight of cars by their cylinders using group by or aggregation
average_weight_df = df.groupBy("cyl").avg("wt")
print("Average weight: ")
average_weight_df.show()

# d) Select gear of the car for the cylinder values greater or equal to 4 and less or equal than 9
#gear_df = df.filter((df['cyl'] >= 4 ) & (df['cyl'] <= 9)).select("car", "gear")
car_gear_df = df.filter((df['cyl'] >= 4) & (df['cyl'] <= 9)).select("car", "gear")
car_gear_df.show(n=1000, truncate=False)
