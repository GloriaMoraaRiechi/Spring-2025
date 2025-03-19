from pyspark.sql import SparkSession
from pyspark.ml.clustering import KMeans, GaussianMixture
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.evaluation import ClusteringEvaluator
from pyspark.sql.functions import col

# Initialize spark session
spark = SparkSession.builder.appName("WheatClustering").getOrCreate()

# Load dataset
file_path = "hdfs://localhost:9000/user/hadoop/assignment/seed.txt"
data = spark.read.csv(file_path, header=False, inferSchema=True, sep="\t")
data.show(5)

# Rename columns
columns = ["area", "perimeter", "compactness", "length", "width", "asymmetry", "lengthOfGroove", "class"]
data = data.toDF(*columns)
data.show(5)

# handle missing values
data = data.dropna()

# Convert feature vectors to a single vector
featureColumns = ["area", "perimeter", "compactness", "length", "width", "asymmetry", "lengthOfGroove"]

# Cast all feature columns to double type
data = data.select(*[col(c).cast("double") for c in featureColumns], "class")

# Assemble feature values
assembler = VectorAssembler(inputCols=featureColumns, outputCol="features")
data = assembler.transform(data)
data.show(5)

# KMeans clustering
kmeans = KMeans(featuresCol="features", k=3, seed=42)
kmeansModel = kmeans.fit(data)
kmeansPredictions = kmeansModel.transform(data)
kmeansPredictions.select("features", "prediction").show(5)

# Evaluate the kmeans clustering
evaluator = ClusteringEvaluator(predictionCol="prediction", featuresCol="features", metricName="silhouette")
kmeansSilhouette = evaluator.evaluate(kmeansPredictions)
print(f"K-Means Silhouette Score: {kmeansSilhouette}")
wssse = kmeansModel.summary.trainingCost
print("K-means WSSSE:", wssse)

# Gaussian Mixture Model
gmm = GaussianMixture(featuresCol="features", k=3, seed=42)
gmmModel = gmm.fit(data)
gmmPredictions = gmmModel.transform(data)
gmmPredictions.select("features", "prediction").show(5)

# Evaluate the gaussian mixture model clustering
gmmSilhoutte = evaluator.evaluate(gmmPredictions)
print(f"Gaussian Mixture Silhouette Score: {gmmSilhoutte}")
logLikelihood = gmmModel.summary.logLikelihood
print("GMM Log-Likelihood:", logLikelihood)

#show the result
centers = kmeansModel.clusterCenters()
print("K-Means Cluster centers: ")
for i, center in enumerate(centers):
	print(f"Cluster {i}: {center}")

spark.stop()
