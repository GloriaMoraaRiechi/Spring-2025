#include <iostream>
#include "rectangle.h"

using namespace std;

int main()
{
	//Rectangle rect1;
	//rect1.setLength(10.5);
	//rect1.setWidth(5.7);
	Rectangle rect1(10.5, 5.7);
	float area = rect1.area();
	float perimeter = rect1.perimeter();

	cout << "Area: " << area << endl;

	return 0; 
}
