#include <iostream>

using namespace std;

class Person
{
	private: // Private data members (hidden from outside)
		string name;
		int age;

	public:
		void setName(string n) //setter fuctions to modify private members
		{
			name = n;			
		}
		
		void setAge(int a)
		{
			if (a > 0)
				age = a;
			else 
				cout << "Age must be positive!" << endl;
		}

		// getter functions to access private members
		string getName()
		{
			return name;
		}

		int getAge()
		{
			return age;
		}
};

int main()
{
	Person p1;

	// setting values using setters
	p1.setName("John");
	p1.setAge(25);

	// getting values using getters
	cout << "Name: " << p1.getName() << endl;
	cout << "Age: " << p1.getAge() << endl;

	return 0;
}
