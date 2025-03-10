#include <iostream>

using namespace std;

int main()
{
	int *x = new int;  // Allocate memory on the heap
	*x = 10;   // deferencing tp assign 10
	cout << *x << endl; // deferencing to access the value
	delete x;
	return 0;
}
