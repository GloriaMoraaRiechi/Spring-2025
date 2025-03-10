#include <iostream>
#include <string>

using namespace std;

int main()
{
	int *int_ptr {nullptr};
	float *float_ptr {nullptr};
	double *double_ptr {nullptr};

	cout << sizeof(int_ptr) << endl;
	cout << sizeof(double_ptr) << endl;
	cout << sizeof(float_ptr) << endl;

	return 0;
}
