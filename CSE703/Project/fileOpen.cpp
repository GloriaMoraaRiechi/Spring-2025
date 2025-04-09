#include <fstream>
#include <iostream>
using namespace std;

int main() {
    string file_path = "/mnt/c/Users/glori/Desktop/Program for Scalable Computing/updated_CKD_data1.csv";

	ifstream file(file_path);

    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;  // Exit with error code
    }

    // Proceed with file reading...
    file.close();
    return 0;
}

