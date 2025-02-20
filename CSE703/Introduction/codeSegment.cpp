// Stores the compiled machine code of the program (The actual executable instructions)

#include <iostream>

using namespace std;

void sayHello()
{
	cout << "hellow, world!" << endl;
}

int main()
{
	sayHello(); // fuction is stored in the text segment

	return 0;
}
