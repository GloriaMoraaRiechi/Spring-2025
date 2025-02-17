// Create a program that shows how much memory it takes to store the values of a short integer, long integer and a long double number in memorr

#include <iostream>

using namespace std;

int main()
{
	size_t shortIntSize = sizeof(short int);
	size_t longIntSize = sizeof(long int);
	size_t longDoubleSize = sizeof(long double);

	cout << "A short integer value uses " << shortIntSize << " bytes of memory" << endl;
	cout << "A long integer value uses " << longIntSize << " bytes of memory" << endl;
	cout << "A long double value uses " << longDoubleSize << " bytes of memory" << endl;

	return 0;
}
