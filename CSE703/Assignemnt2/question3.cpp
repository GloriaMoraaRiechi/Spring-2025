/* 
Create a simple program that defines two 1-D arrays: 
x=[15, 10, 30, 20, 17] and y=[2, 7, 3, 4, 5] and a third empty array of size 5. 
Then first use the for loop to subtract array y from array x element-wise and store the results on the array z.
Second use another for loop to print the elements of the array z each element isn a separate line
*/

#include <iostream>

using namespace std;

int main()
{
	int x[] = {15, 10, 30, 20, 17};
	int y[] = {2, 7, 3, 4, 5};
	int z[5];

	// Subtract y from x
	for (int i = 0; i < 5; ++i)
	{
		z[i] = x[i] - y[i];
	}

	// Print elements of z
	for (int i = 0; i < 5; ++i)
	{
		cout << z[i] << endl;
	}

	return 0;
}
