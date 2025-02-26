/*
write a program that defines an empty 5X4 array named z and the matrices x and y
The program then uses for loop to multiply matrix x by matrix y element-wise and stores the result in matrix z
Then use a different for loop to print the content of matrix z.
*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	const int rows = 5;
	const int cols = 4;

	double x[rows][cols]{
	{2.1, 6.4, 0.1, 4.4},
	{2.2, 7.1, 0.3, 2.6},
	{3.2, 5.4, 0.2, 3.1},
	{1.0, 3.9, 0.4, 1.1},
	{3.1, 7.3, 0.5, 2.8}
	};

	double y[rows][cols]{
	{4.4, 4.2, 2.3, 9.5},
	{5.4, 5.3, 2.3, 5.1},
	{0.2, 1.1, 4.2, 7.3},
	{1.9, 4.1, 2.4, 9.2},
	{4.2, 4.4, 1.4, 5.7}
	};

	double z[rows][cols];

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			z[i][j] = x[i][j] * y[i][j];
		}
	}
	
	cout << "Matrix Z:" << endl;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			cout << z[i][j] << "\t";
		}

		cout << endl;
	}

	return 0;
}
