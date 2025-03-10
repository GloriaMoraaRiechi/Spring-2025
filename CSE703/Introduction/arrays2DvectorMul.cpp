#include <iostream>

using namespace std;

int main()
{
	int row=4, col=4;
	int result[row] = {0};
	int m[row][col] = {
	{1, 0, 2, 0},
	{0, 3, 0, 4},
	{0, 0, 5, 0},
	{6, 0, 0, 7}};

	int v[col] = {2, 5, 1, 8};
	for (int i=0; i<row; i++)
	{
		for (int j=0; j<col; j++)
		{
			result[i] += m[i][j] * v[j];
		}
	}

	cout << "Result of matrix multiplication: " << endl;
	for (int i=0; i<row; i++)
	{
		cout << result[i] << " ";
	}
	cout << endl;
	return 0;
}
