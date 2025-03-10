class Rectangle
{
	private:
		float length;
		float width;
	public:
		Rectangle(){} //default constructor

		Rectangle(float length, float width) //constructor
		{
			this->length = length;
			this->width = width;
		}

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
			return 2 * (length + width);
		}
};
