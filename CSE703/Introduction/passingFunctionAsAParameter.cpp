#include <iostream>

using namespace std;

int add(int x, int y)
{
	return x + y;
}

int multiply(int x, int y)
{
	return x * y;
}

// function that takes a pointer to a function
int invoke(int x, int y, int(*func)(int, int))
{
	return func(x, y);
}

int main()
{
	int m = 20;
	int n = 30;
	int sum, product;
	sum = invoke(m, n, add);
	product = invoke(m, n, multiply);
	cout << "Sum: " << sum << endl;
	cout << "Product: " << product << endl;

	return 0;
}
