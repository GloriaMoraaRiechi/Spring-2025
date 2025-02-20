#include <iostream>

using namespace std;

// Function that modifies a variable using a reference
void doubleValue(int &num)
{
	num *= 2;
}

int main()
{
	int value = 10;
	cout << "Before: " << value << endl;

	doubleValue(value); //Passing by reference

	cout << "After: " << value << endl; 

	return 0;

}
