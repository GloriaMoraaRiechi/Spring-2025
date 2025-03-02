// modify the following program to add and multiply double floating point values

#include <iostream>

using namespace std;

// Fucntion that adds two numbers
double add(double x, double y)
{
	return x + y;
}

// Function that multiplies two numbers
double multiply(double x, double y)
{
	return x * y;
}

// Function that takes a pointer to a function
double invoke(double x, double y, double (*func)(double, double))
{
	return func(x, y);
}

int main()
{
	// pass pointers to add and multiply function as required
	cout << invoke(20.0, 10.0, &add) << endl;
	cout << invoke(20, 10, &multiply) << endl;

	return 0;
}
