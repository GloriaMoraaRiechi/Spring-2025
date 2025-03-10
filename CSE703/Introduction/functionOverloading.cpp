// Function overloading allows multiple functions with the same name but different parameters to exist in the program

#include <iostream>

using namespace std;

int add(int a, int b)
{
	return a + b;
}


double add(double a, double b)
{
	return a + b;
}

int add(int a, int b, int c)
{
	return a + b + c;
}

int main()
{
	cout << "Sum of two integers: " << add(5, 10) << endl;
	cout << "Sum of two doubles: " << add(5.5, 6.8) << endl;
	cout << "sum of three integers: " << add(1, 2, 3) << endl;

	return 0;
}

