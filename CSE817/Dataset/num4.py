from pyspark.sql import SparkSession
from pyspark.ml.clustering import KMeans
from pyspark.ml.feature import VectorAssembler
from pyspark.sql.functions import col

# Initialize Spark session
spark = SparkSession.builder.appName("WheatClustering").getOrCreate()

# Load dataset
file_path = "hdfs://localhost:9000/user/hadoop/assignment/seed.txt"
data = spark.read.csv(file_path, header=False, inferSchema=True, sep="\t")

# Rename columns to match feature names
columns = ["area", "perimeter", "compactness", "length", "width", "asymmetry", "lengthOfGroove", "class"]
data = data.toDF(*columns)

# Handle missing values by dropping rows with nulls
data = data.dropna()

# Cast all feature columns to double type for proper processing
featureColumns = ["area", "perimeter", "compactness", "length", "width", "asymmetry", "lengthOfGroove"]
data = data.select(
    *[col(c).cast("double") for c in featureColumns],  # Cast feature columns to double
    "class"
)

# Assemble features into a single vector
assembler = VectorAssembler(inputCols=featureColumns, outputCol="features")
data = assembler.transform(data)

# Perform KMeans clustering
kmeans = KMeans(featuresCol="features", k=3, seed=42)
kmeansModel = kmeans.fit(data)
kmeansPredictions = kmeansModel.transform(data)

# Show clustering results
kmeansPredictions.select("features", "prediction").show(5)

