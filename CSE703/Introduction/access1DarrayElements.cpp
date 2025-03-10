#include <iostream>

using namespace std;

int main()
{
	int n = 5;
	float x[n] {3.1, 2.8, 5.6, 98.0, 4.6};
	for (int i=0; i<n; i++)
	{
		cout << x[i] << endl;
	}

	return 0;
}
