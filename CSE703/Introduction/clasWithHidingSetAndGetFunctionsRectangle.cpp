#include <iostream>

using namespace std;

class Rectangle
{
	private:
		float length;
		float width;
	
	public:
		void setLength(float length)
		{
			this->length = length;
		}

		void setWidth(float width)
		{
			this->width = width;
		}

		float getLength()
		{
			return length;
		}
		float getWidth()
		{
			return width;
		}

		float area()
		{
			return length * width;
		}
		float perimeter()
		{
			return 2*(length + width);
		}
};

int main()
{
	Rectangle rect1;
	rect1.setLength(10.5);
	rect1.setWidth(5.7);
	float area = rect1.area();
	float perimeter = rect1.perimeter();

	cout << "Area: " << area << endl;
	cout << "Perimeter: " << perimeter << endl;

	return 0;
}
