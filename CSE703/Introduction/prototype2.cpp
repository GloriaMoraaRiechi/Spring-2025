#include <iostream>

using namespace std;

// Function prototype
int add(int, int);

int main()
{
	int result = add(5, 7);
	cout << "Sum: " << result << endl;
	return 0;
}

int add(int a, int b)
{
	return a + b;
}

