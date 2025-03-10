#include <iostream>

using namespace std;

int main()
{
	int x = 100;
	int *x_ptr = &x;
	cout << x << endl;
	cout << &x << endl; // print the address of the variable x
	cout << x_ptr << endl; // print the address of variable x
	cout << &x_ptr << endl; // print address of the pointer
	x_ptr = nullptr;    // the pointer points to nowhere
	cout << x_ptr << endl;
	
	return 0;
}
