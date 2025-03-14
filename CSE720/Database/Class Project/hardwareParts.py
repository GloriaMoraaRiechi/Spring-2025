import mysql.connector

# Define connection parameters
db_config = {
    'host': '127.0.0.1',
    'user': 'root',
    'password': '',
    'database': '`hardware parts specifications`'
}

# Establish connection
try:
    conn = mysql.connector.connect(**db_config)
    if conn.is_connected():
        print("Successfully connected to the database")
except mysql.connector.Error as err:
    print(f"Error: {err}")

cursor = conn.cursor()
cursor.execute("SHOW TABLES;")
tables = cursor.fetchall()

print("Tables in the database:")
for table in tables:
    print(table)


cursor.close()
conn.close()