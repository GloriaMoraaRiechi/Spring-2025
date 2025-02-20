/*
Write a simple program that defines a 1-D array for 1000 double numeric elements and then prints how much bytes of memory will be allocated duing the run-time
Copy that program and instead of 1000 double elements declare the array to store 1000000000000000 elements
Compile and run both programs and very briefly comment on the results of the two programs
*/

#include <iostream>

using namespace std;

int main()
{
	double arr[1000];

	cout << "Memory allocated for 1000 doubles is " << sizeof(arr) << " bytes" << endl;

	return 0;
}

