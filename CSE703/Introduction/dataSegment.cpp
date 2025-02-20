// Stores global and static variables that are not initialized (default initialized to 0). exists throughout the program's lifetime

#include <iostream>

using namespace std;

int uninitGlobal; // stored in the BBS segment (default initialized to 0)

static int uninitStatic;

int main()
{
	cout << uninitGlobal << " " << uninitStatic << edl1;

	return 0;
}
