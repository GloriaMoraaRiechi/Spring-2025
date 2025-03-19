from pyspark.sql import SparkSession
from pyspark.sql.functions import upper, col

# Initialize Spark Session
spark = SparkSession.builder.appName('SparkByExamples.com').getOrCreate()

simpleData = [
    ("Java", 4000, 5),
    ("Python", 4600, 10),
    ("Scala", 4100, 15),
    ("PHP", 3000, 20),
]

columns = ["CourseName", "fee", "discount"]

df = spark.createDataFrame(data=simpleData, schema=columns)

def to_upper_str_columns(df):
    return df.withColumn("CourseName", upper(col("CourseName")))
 
def reduce_price(df, reduceBy):
    return df.withColumn("new_fee", col("fee") - reduceBy)

def apply_discount(df):
    return df.withColumn("discounted_fee", col("new_fee") - (col("new_fee") * col("discount") / 100))

df2 = df.transform(to_upper_str_columns).transform(reduce_price, 1000).transform(apply_discount)

df2.show()

