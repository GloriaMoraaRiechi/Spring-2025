#include <iostream>
#include <string>

using namespace std;

float multiply(float x, float y)
{
	float product;
	product = x * y;
	return product;
}

int main()
{
	float n = 12.50;
	float m = 17.25;
	float result;
	result = multiply(n, m);
	cout << result << endl;

	return 0;
}
