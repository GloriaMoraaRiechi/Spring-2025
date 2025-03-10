#include <iostream>

using namespace std;

int main()
{
	int sum = 0;
	for (int i: {3, 5, 7, 9, 11})
	{
		sum = sum + i;
	}

	cout << sum << endl;
	return 0;
}
