#include <iostream>

using namespace std;

class Rectangle
{
	public:
		float length;
		float width;
		float area()
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
	Rectangle rect1;         // a variable
	Rectangle *r = &rect1;   // a pointer in the stack
	r->length = 10.5;
	r->width = 7.2;

	float area = r->area();
	float perimeter = r->perimeter();

	cout << "Area: " << area << endl;
	cout << "Perimeter: " << perimeter << endl;

	return 0;
}
