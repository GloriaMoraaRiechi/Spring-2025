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

class Queue
{
	private:
		Node* front;
		Node* rear;

	public:
		Queue()
		{
			front = rear = nullptr;
		}

		// Enqueue operation
		void enqueue(int value)
		{
			Node* newNode = new Node(value);
			if  (rear == nullptr)
			{
				front = rear = newNode;
			}
			else
			{
				rear->next = newNode;
				rear = newNode;
			}
			cout << value << " enqueued into queue." << endl;
		}

		// Dequeue operation
		void dequeue()
		{
			if (front == nullptr)
			{
				cout << "Queue underflow! No element to dequeue." << endl;
				return;
			}
			Node* temp = front;
			front = front->next;
			if (front == nullptr) rear = nullptr;
			cout << temp->data << " dequeued from queue." << endl;
			delete temp;
		}

		// peek operation
		void peek()
		{
			if (front == nullptr)
			{
				cout << "Queue is empty!" << endl;
				return;
			}
			cout << "Front elememt: " << front->data << endl;
		}

		// Display queue elements
		void display()
		{
			if (front == nullptr)
			{
				cout << "Queue is empty!" << endl;
				return;
			}
			cout << "Queue: ";
			Node* temp = front;
			while (temp != nullptr)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
			cout << endl;
		}
};

int main() {
    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display(); // 10 20 30

    q.peek(); // Front element: 10

    q.dequeue();
    q.display(); // 20 30

    return 0;
}
