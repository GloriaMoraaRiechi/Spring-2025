from pyspark import SparkContext

# Create a SparkContext
# SparkContext establishes a connection to the spark cluster
sc = SparkContext("local", "wordCount")

# Sample text
text = "Hello World, This is a Fundamentals of Big Data Analytics Course, big data is Interesting, Hello World"

# Split the text into words
words = sc.parallelize(text.split(" "))  #words is a resilient distributed dataset

# Match each value to a key value pair
word_counts = words.map(lambda word: (word, 1))

# Reduce by adding up the counts for each word
word_counts = word_counts.reduceByKey(lambda a, b: a + b)

# Collect the results and print
print(word_counts.collect())
