// Program that uses openMP to parallelize addition of elements in an array

#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	// Initialize the array
	const int size = 1000;
	int arr[size];

	for (int i = 0; i < size; ++i)
	{
		arr[i] = i * 100;
	}

	int globalSum = 0;       // The shared variable

	omp_set_num_threads(10);

	// Parallel region
	#pragma omp parallel shared(arr, globalSum)
	{
		int localSum = 0;    // The private variable

		// Distribute the work across the threads
		#pragma omp for
		for  (int i = 0; i < size; ++i)
		{
			localSum += arr[i];     // Each thread builds its local sum
		}

		// Merge into global sum
		#pragma omp critical
		{
			cout << "Thread " << omp_get_thread_num() << " adding localSum = " << localSum << " to globalSum." << endl;
			globalSum += localSum;
		}
	}

	cout << "\nFinal total sum = " << globalSum << endl;

	return 0;
}
