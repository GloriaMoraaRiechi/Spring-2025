// Write simple two programs. Each one uses a different variant of the C++ main function. (One with arguments and one without arguments)

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Program with Arguments" << endl;
	cout << "Number of arguments: " << argc << endl;

	for (int n = 0; n < argc; n++)
	{
		cout << "Argument " << n << ": " << argv[n] << endl;
	}

	return 0;
}
