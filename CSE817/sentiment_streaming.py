from pyspark import SparkContext
from pyspark.streaming import StreamingContext

# Step 1: Initialize Spark Context and Streaming Context
sc = SparkContext(appName="SentimentWordCount")
ssc = StreamingContext(sc, batchDuration=5)  # Process every 5 seconds

# Step 2: Define sentiment word sets
positive_words = {'good', 'great', 'happy', 'excellent', 'awesome', 'love', 'nice', 'fantastic'}
negative_words = {'bad', 'sad', 'terrible', 'awful', 'worst', 'hate', 'poor', 'horrible'}

# Step 3: Create DStream from Netcat stream
lines = ssc.socketTextStream("localhost", 9999)

# Step 4: Split lines into words
words = lines.flatMap(lambda line: line.split(" "))

# Step 5: Function to categorize words
def categorize(word):
    word_lower = word.lower()
    if word_lower in positive_words:
        return ("positive", 1)
    elif word_lower in negative_words:
        return ("negative", 1)
    else:
        return ("neutral", 0)

sentiment_pairs = words.map(categorize)

# Step 6: Reduce by key to count sentiments
sentiment_counts = sentiment_pairs.reduceByKey(lambda a, b: a + b)

# Step 7: Output the results
sentiment_counts.pprint()

# Step 8: Start streaming
ssc.start()
ssc.awaitTermination()

