/*
Create a function that can take both a 1D array and its size as arguments and then compute the mean of the array.
Let the function be after the main function and use the function prototype
Call that function from the main function to compute and display the mean of [3.9, 15.2, 13.7, 11.2, 7.9]
*/

#include <iostream>

using namespace std;

double computeMean(double arr[], int size); // prototype

int main()
{
	double arr[] = {3.9, 15.2, 13.7, 11.2, 7.9};
	int size = sizeof(arr) / sizeof(arr[0]);

	double mean = computeMean(arr, size);
	cout << "Mean of the array: " << mean << endl;

	return 0;
}

double computeMean(double arr[], int size)
{
	double sum = 0.0;

	for (int i = 0; i < size; i++)
	{
		sum += arr[i];
	}

	return sum / size;
}
