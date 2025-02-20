// Write to a text file using the file streaming
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream outFile;
	outFile.open("example1.txt", ios::out);
	outFile << "Name\t\tAge" << endl;
	outFile << "James\t\t21" << endl;
	outFile << "Agee\t\t18" << endl;
	outFile << "Paula\t\t25" << endl;
	outFile << "Ali\t\t37" << endl;
	outFile.close();

	cout << "File written succesfully" << endl;

	return 0;
}
