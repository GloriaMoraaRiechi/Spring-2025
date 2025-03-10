#include <iostream>

using namespace std;

int main()
{
	int n = 5;
	float x [n] {3.1, 3.4, 6.7, 9.7, 5.3};
	float y [n]; 

	for (int i=0; i<n; i++)
	{
		y[i] = x[i] * 3;
	}

	for (int i=0; i<n; i++)
	{
		cout << y[i] << endl;
	}
	return 0;
}
