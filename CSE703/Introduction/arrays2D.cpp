#include <iostream>

using namespace std;

int main()
{
	const int row {5};
	const int col {3};
	int x [row][col]
	{
		{20, 18, 25},
		{33, 23, 21},
		{15, 22, 27},
		{19, 14, 19},
		{22, 19, 28}
	};
	cout << x[2][1] << endl;

	// accessing an element using loop
	for (int i=0; i<row; i++)
	{
		for (int j=0; j<col; j++)
		{
			cout << x[i][j] << "\t";
		}
		cout << endl;
	}

	return 0;
}
