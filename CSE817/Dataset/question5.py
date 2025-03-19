from pyspark.sql import SparkSession
from pyspark.sql.functions import upper, col, expr

# Initialize Spark Session
spark = SparkSession.builder.appName('SparkByExamples.com').getOrCreate()

simpleData = [
    ("Java", 4000, 5),
    ("Python", 4600, 10),
    ("Scala", 4100, 15),
    ("PHP", 3000, 20),
]

# Define columns
columns = ["CourseName", "fee", "discount"]

# Create DataFrame
df = spark.createDataFrame(data=simpleData, schema=columns)

# Function to convert CourseName to uppercase
def to_upper_str_columns(df):
    return df.withColumn("CourseName", upper(col("CourseName")))

# Function to reduce fee by 1000
def reduce_price(df, reduceBy):
    return df.withColumn("nef_fee", col("fee") - reduceBy)

# Function to apply discount to fee
def apply_discount(df):
    return df.withColumn("discounted_fee", col("new_fee") - (col("new_fee") * col("discount") / 100))


# Apply transformations
df2 = df.transform(to_upper_str_columns).transform(reduce_price, 1000).transform(apply_discount)

# Show results
df2.show()

