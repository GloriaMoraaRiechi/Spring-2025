/*
	Program with 10 MPI processes where each process stores the number 10, and MPI_Reduce function multiplies all the values together and prints the result.
*/

#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);  // Initialize the MPI environment

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	long long value = 10;

	// Variable to store the result of the reduction
	long long result = 0;

	// Perform the reduction using multiplication
	MPI_Reduce(&value, &result, 1, MPI_LONG_LONG, MPI_PROD, 0, MPI_COMM_WORLD);

	// Print the result
	if (rank == 0)
	{
		cout << "The product of the numbers is " << result << endl;
	}

	MPI_Finalize(); // Shut down the MPI environment
	return 0;
}
