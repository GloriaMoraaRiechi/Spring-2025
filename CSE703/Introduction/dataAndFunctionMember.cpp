#include <iostream>

using namespace std;

class Rectangle
{
	public:
		float length;  // A data member
		float width;   // A data member
		
		float area()   // Function member
		{
			return length * width;
		}

		float perimeter()
		{
			return 2 * (length + width);
		}
};

int main()
{
	Rectangle rect1;  // Declare a class object
	rect1.length = 10.5;
	rect1.width = 5.7;

	float area = rect1.area();
	float perimeter = rect1.perimeter();

	cout << "Area: " << area << endl;
	cout << "Perimeter: " << perimeter << endl;

	return 0;
}
