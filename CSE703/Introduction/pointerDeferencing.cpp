#include <iostream>

using namespace std;

int main()
{
	int x = 100;
	int *ptr = &x;

	cout << x << endl;
	cout << *ptr << endl;
	*ptr = 300;
	cout << x << endl;
	cout << *ptr << endl;

	return 0;
}
