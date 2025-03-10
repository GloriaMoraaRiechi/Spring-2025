#include <iostream>

using namespace std;

class Node
{
	public:
		int data;
		Node* next;

		Node(int value)
		{
			data = value;
			next = nullptr;
		}
};

class Stack
{
	private:
		Node* top;  //Pointer to the top node

	public:
		Stack()
		{
			top = nullptr;
		}

	// Push operation
	void push(int value)
	{
		Node* newNode = new Node(value);
		newNode->next = top;
		top = newNode;
		cout << value << " pushed to the stack" << endl;
	}

	// Pop operation
	void pop()
	{
		if (top == nullptr)
		{
			cout << "Stack Underflow! No element to pop" << endl;
			return;
		}
		Node* temp = top;
		top = top->next;
		cout << temp->data << " popped from stack." << endl;
		delete temp;
	}

	// Peek operation
	void peek()
	{
		if (top == nullptr)
		{
			cout << "Stack is empty!" << endl;
			return;
		}
		cout << "Top element: " << top->data << endl;
	}

	// Display stack
	void display()
	{
		if (top == nullptr)
		{
			cout << "Stack is empty!" << endl;
		}
		cout << "Stack: ";
		Node* temp = top;
		while (temp != nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
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

	s.peek();

	s.pop();
	s.display();

	return 0;
}
