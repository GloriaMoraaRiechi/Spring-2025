// Create a program that takes the radius of a circle as a command line argument and passes it to compute and print the area of the circle

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
	// Handle unexpected errors
	// Check if the user provided exactly one argument
	if (argc != 2)
	{
		cerr << "The format is: " << argv[0] << " <radius>" << endl;
		return 1;
	}

	// Assign radius to the second argument and convert it from string to double
	double radius = std::atof(argv[1]);

	// Validate that the radius is positive
	if (radius <= 0)
	{
		cerr << "Error: Radius must be a positive number." << endl;
		return 1;
	}

	double area = M_PI * pow(radius, 2);

	cout << "The area of the circle with radius " << radius << " is " << area << endl;

	return 0;
}

