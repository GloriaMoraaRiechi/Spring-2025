// Read a text file using the file streaming

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream inFile("example1.txt", ios::in);
	string line;
	while (getline(inFile, line))
	{
		cout << line << endl;
	}
	inFile.close();
	return 0;
}
