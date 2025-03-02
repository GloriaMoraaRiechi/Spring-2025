/*
Create a user-defined class-based data type that incudes:
Length and width as public member variable
A public member function to compute the area
In the main function, create an object for this data type and then use that to print the length, the width and the area of the rectangle with length of 23.7 and width of 12.5
*/

#include <iostream>

using namespace std;

class Rectangle
{
public:
	// Public member variables
	double length;
	double width;

	// Public member function to compute area
	double computeArea()
	{
		return length * width;
	}
};

int main()
{
	// Create an object of the class
	Rectangle rect;

	// Assign values to length and width
	rect.length = 23.7;
	rect.width = 12.5;

	// Compute the area and print using the object
	cout << "Area of the rectangle: " << rect.computeArea() << endl;

	return 0;
}
