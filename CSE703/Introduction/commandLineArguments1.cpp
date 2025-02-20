#include <iostream>
#include <stdexcept>

using namespace std;

int main(int argc, char *argv[])
{
	float x = atof(argv[1]);
	float y = atof(argv[2]);
	cout << x*y << endl;

	return 0;
}
