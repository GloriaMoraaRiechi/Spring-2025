#include <iostream>

using namespace std;

class Stack
{
	private:
		int arr[5]; //fixed size array 
		int top;    //tracks the top element

	public:
		// constructor to initialize stack
		Stack()
		{
			top = -1; //stack is initially empty
		}

		// Push function (adds an element)
		void push(int value)
		{
			if (top >= 4) //stack overflow condition
			{
				cout << "Stack overflow! cannot push " << value << endl;
				return;
			}
			arr[++top] = value; //increment top and add value
			cout << value << " pushed to stack." << endl;
		}

		// Pop function (removes the top element)
		void pop()
		{
			if (top < 0) //stack underflow condition
			{
				cout << "Stack underflow! No element to pop." << endl;
				return;
			}
			cout << arr[top--] << " popped from the stack." << endl;
		}

		// Peek function (shows the top element)
		void peek()
		{
			if (top < 0)
			{
				cout << "Stack is empty" << endl;
				return;
			}
			cout << "Top element: " << arr[top] << endl;
		}

		// Display function (prints stack contents)
		void display()
		{
			if (top < 0)
			{
				cout << "Stack is empty!" << endl;
				return;
			}
			cout << "Stack: ";
			for (int i = top; i >= 0; i--)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
		}
};

int main()
{
	Stack s;
	s.push(10);
	s.push(20);
	s.push(30);
	s.display();

	s.peek();  //top element

	s.pop();

	s.display();

	return 0;
}
