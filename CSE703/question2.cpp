// The area of the circle is given by (A=Π^2), where Π = 3.14159265359 and r is the radius of the circle. Create a program that computes and prints the area of the circle that its radius is 12.5 cm.

#include <iostream>
#include <cmath>

using namespace std;

const double pi=3.14159265359;
double r=12.5;

int main()
{
	double area;
	area = pi * pow(r, 2);
	cout << "Area: " << area << endl;

	return 0;
}
