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
	Rectangle *rect1;         // a variable
	rect1 = new Rectangle();  // allocate memory in the heap
	rect1->length = 10.5;
	rect1->width = 7.2;

	float area = rect1->area();
	float perimeter = rect1->perimeter();

	cout << "Area: " << area << endl;
	cout << "Perimeter: " << perimeter << endl;

	return 0;
}
