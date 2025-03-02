/*
Create a function that can take both a vector and iyts isze as arguments and then compute the mean of the array
Let that function be after the main and use the function prototype
Call that function from the main function to compute and display the mean of [3.9, 15.2, 13.7, 11.2, 7.9]
Use auto for the for loop
*/

#include <iostream>
#include <vector>

using namespace std;

double computeMean(const vector<double>& vec); // prototype

int main()
{
	vector<double> vec = {3.9, 15.2, 13.7, 11.2, 7.9};

	double mean = computeMean(vec);
	cout << "Mean of the vetor: " << mean << endl;

	return 0;
}

double computeMean(const vector<double>& vec)
{
	double sum = 0.0;

	for (auto num : vec)
	{
		sum += num;
	}

	return sum / vec.size();
}
