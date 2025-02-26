/*
Create a simple program that includes a variable with the double (x=200) and a pointer variable (x_ptr) that points to x. The program should print:
*/

#include <iostream>

using namespace std;

int main()
{
	double x = 200;
	double* x_ptr = &x;

	// a. value of x
	cout << "The value of x is " << x << endl;

	// b. The address of x using the address operator
	cout << "The address of x using &x is " << &x << endl;

	// c. The address of x using the pointer variable
	cout << "The address of using x_ptr is " << x_ptr << endl;

	// d. The memory address of the pointer variable
	cout << "The memory address of x_ptr is " << &x_ptr << endl;

	// e. The value of the variable that the pointer variable is pointing at using deferencing(*) operators
	cout << "The vaue pointed by x_ptr using *x_ptr is " << *x_ptr << endl;

	return 0;
}
