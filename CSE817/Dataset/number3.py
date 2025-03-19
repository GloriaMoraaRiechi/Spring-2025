from pyspark.sql import SparkSession

# Initialize Spark Session
spark = SparkSession.builder.appName("RelationalJoin").getOrCreate()
sc = spark.sparkContext  # Get Spark Context

# Offences Data: (Code, Date, Officer, Dept, Registration)
offences = [
    (142356, "26/10/1992", 56, 75, "5964 FR"),
    (98745, "26/10/1992", 56, 75, "7124 HT"),
    (98076, "12/10/1992", 56, 47, "6544 XY"),
    (39845, "12/10/1992", 47, 47, "6544 XY"),
]

# Cars Data: (Registration, Dept, Owner)
cars = [
    ("6544 XY", 47, "Manual Bernard"),
    ("7124 HT", 75, "Cordoan"),
    ("5964 FR", 75, "Labour Hortense"),
]

# Convert to RDDs
offences_rdd = sc.parallelize(offences)
cars_rdd = sc.parallelize(cars)

# Map Phase: Emit (Dept, Record)
offences_mapped = offences_rdd.map(lambda x: (x[3], ("Offence", x)))  # Key: Dept
cars_mapped = cars_rdd.map(lambda x: (x[1], ("Car", x)))  # Key: Dept

# Combine both datasets
combined_rdd = offences_mapped.union(cars_mapped)

# Reduce Phase: Group by Dept
grouped_rdd = combined_rdd.groupByKey()

# Join based on Registration
def join_records(records):
    offences_list = []
    cars_list = []
    
    for record in records:
        if record[0] == "Offence":
            offences_list.append(record[1])  # Store offence records
        else:
            cars_list.append(record[1])  # Store car records

    joined_results = []
    for offence in offences_list:
        for car in cars_list:
            if offence[4] == car[0]:  # Matching Registration
                joined_results.append((offence[0], offence[1], offence[2], offence[3], offence[4], car[2]))

    return joined_results

# Apply Join Logic
joined_rdd = grouped_rdd.flatMapValues(join_records).map(lambda x: x[1])  # Remove Dept key

# Collect and Display Results
result = joined_rdd.collect()

from pyspark.sql import Row

# Convert RDD to DataFrame
df = spark.createDataFrame(joined_rdd, schema=["Code", "Date", "Officer", "Dept", "Registration", "Owner"])

# Show results as a formatted table
df.show(truncate=False)
