// Write a simple program that accepsts 10 double numbers as command line arguments and uses "for loop" to multiply each number by 100 and then print it each in a separate line

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
	// Confirm that exactly 10 numbers are provides
	if (argc != 11)
	{
		cerr << "Format: " << argv[0] << " num1 num2 ... num10" << endl;
		return 1;
	}

	// Loop through the numbers entered
	for (int i = 1; i <= 10; ++i)
	{
		double num = atof(argv[i]);
		cout << num * 100 << endl;
	}

	return 0;


}
