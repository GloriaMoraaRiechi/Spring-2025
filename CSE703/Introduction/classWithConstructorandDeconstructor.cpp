#include <iostream>

using namespace std;

class Person
{
	private:
		string name;
		int age;
	
	public:
	// constructor automaticall called when an object is created
	Person(string n, int a)
	{
		name = n;
		age = a;
		cout << "Constructor called! Object created for " << name << endl;
	}

	// Deconstructor automatically called when an object is destroyed
	~Person()
	{
		cout << "Destructor called! Object for " << name << " is being destroyed." << endl;
	}

	void display()
	{
		cout << "Name: " << name << ", Age: " << endl; 
	}
};

int main()
{
	Person p1("John", 25);

	p1.display();

	    // When main() function ends, p1 goes out of scope, and the destructor is called.
	
	return 0;
}
