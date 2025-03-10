#include <iostream>

using namespace std;

int main()
{
	int *x = new int[5]; //alocation memory for 5 integers
	for (int i = 0; i < 5; i++)
	{
		x[i] = i * 10;
	}
	for (int i = 0; i < 5; i++)
	{
		cout << x[i] << endl;
	}
	delete x;  //deeallocating memory

	return 0;

}
