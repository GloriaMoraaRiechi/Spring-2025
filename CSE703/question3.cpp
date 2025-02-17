//Create a program that prompts the user to enter the radius of a circle and then computes and prints the area of that circle. Use the program to compute the area of a circle with r=12.5

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	double radius, area;
	
	cout << "Enter the radius of the circle: ";
	cin >> radius;

	area = M_PI * pow(radius, 2);

	cout << "Area: " << area << endl;

	return 0;
}
