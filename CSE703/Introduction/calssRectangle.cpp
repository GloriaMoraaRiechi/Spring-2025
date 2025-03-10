#include <iostream>

using namespace std;

class Rectangle
{
	public:
		int length;
		int width;
		
		int area()
		{
			return length * width;
		}

		int perimeter()
		{
			return 2 * (length + width);
		}
};

int main()
{
	Rectangle rect1;
		rect1.length = 10;
		rect1.width = 5;
		int area = rect1.area();
		int perimeter = rect1.perimeter();
	
		cout << "Area: " << area << endl;
		cout << "Perimeter: " << perimeter << endl;

	return 0;
}
