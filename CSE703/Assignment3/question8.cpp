/*
Create two overloading functions (a function with the same name) with the name add
One passes two double floating point values as arguments and the second passes three double floating point values as arguments
Then call the two functions from inside the main function to compute the sum of:
73.9 and 56.6
68.7, 37.4 and 44.3
*/

#include <iostream>

using namespace std;

// Function to add two double floating point values
double add(double num1, double num2)
{
	return num1 + num2;
}

// Function to add three double floating point values
double add(double num1, double num2, double num3)
{
	return num1 + num2 + num3;
}

int main()
{
	double sum1 = add(73.9, 56.6);
	double sum2 = add(68.7, 37.4, 44.3);

	cout << "The sum of 73.9 and 56.6 is " << sum1 << endl;
	cout << "The sum of 68.7, 37.4 and 44.3 is " << sum2 << endl;

	return 0;
}
