#include <iostream>
#include <stdexcept>  // For exception handling

using namespace std;

int main(int argc, char *argv[])
{
    // Ensure the user provides exactly 2 arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer1> <integer2>" << endl;
        return 1;
    }

    try {
        // Convert arguments to integers
        int x = stoi(argv[1]);  // Throws exception if invalid
        int y = stoi(argv[2]);

        // Perform multiplication and display result
        cout << "Result: " << x * y << endl;
    } 
    catch (const invalid_argument &e) {
        cerr << "Error: Both inputs must be valid integers." << endl;
        return 1;
    } 
    catch (const out_of_range &e) {
        cerr << "Error: Input is out of range for an integer." << endl;
        return 1;
    }

    return 0;
}

