// OpenMP Program to compute cosine similarity between two vectors

#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

int main()
{
	vector<double> v1 = {12.5, 11.6, 17.2, 9.9, 10.14, 17.3, 10.5, 13.8, 8.12};
	vector<double> v2 = {11.5, 17.4, 12.5, 8.8, 11.04, 14.2, 15.6, 11.9, 7.16};

	// Get the length of the vectors
	int n = v1.size();

	// Initialize dot product and the Euclidean norm of the vectors
	double dotProduct = 0.0;
	double normV1 = 0.0;
	double normV2 = 0.0;

	// The parallel region with the three threads
	#pragma omp parallel for reduction(+:dotProduct, normV1, normV2) num_threads(3)
	for (int i = 0; i < n; i++)
	{
		// Get the thread number
		int thread_id = omp_get_thread_num();
		
		printf("Thread %d is working on index %d\n", thread_id, i);

		dotProduct += v1[i] * v2[i];
		normV1 += v1[i] * v1[i];
		normV2 += v2[i] * v2[i];
	}

	// Compute Euclidean norms
	normV1 = sqrt(normV1);
	normV2 = sqrt(normV2);

	// Compute the cosine similarity
	double cosineSimilarity = dotProduct / (normV1 * normV2);

	cout << "The cosine similarity of the two vectors is " << cosineSimilarity << endl;

	return 0;
}
