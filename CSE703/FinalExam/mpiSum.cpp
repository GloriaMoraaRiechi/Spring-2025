/*
	MPI program that uses three processes where process 1 and 2 each compute the sum of their respective elements using a custom sumVect fuction, send their sums to process 0 which multiplies the two sums and prints the result.
*/

#include <iostream>
#include <mpi.h>

using namespace std;

// Function to sum up elements of the array
int sumVect(const int arr[], int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += arr[i];
	}

	return sum;
}

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);   // Initializes the MPI environment
	
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 1)
	{
		// Process 1
		int array1[] = {10, 11, 13, 9, 7};
		int size1 = 5;
		int sum1 = sumVect(array1, size1);

		// Send result of process 1 to process 0
		MPI_Send(&sum1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		cout << "Process 1: sent sum " << sum1 << " to process 0." << endl;
	}
	else if (rank == 2)
	{
		// Process 2
		int array2[] = {8, 14, 17, 20, 9, 12};
		int size2 = 6;
		int sum2 = sumVect(array2, size2);

		// Send result of process 2 to process 0;
		MPI_Send(&sum2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		cout << "Process 2: sent sum " << sum2 << " to process 0." << endl;
	}
	else if (rank == 0)
	{
		int sum_process1, sum_process2;

		// Receive results from process 1 and process 2
		MPI_Recv(&sum_process1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&sum_process2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		cout << "Process 0: received sums " << sum_process1 << " and " << sum_process2 << "." << endl;

		int product = sum_process1 * sum_process2;
		cout << "Process 0: The product of the sums is " << product << endl;

	}
	
	MPI_Finalize(); // Shut down the MPI environment
	return 0;
}
