#include <iostream>

using namespace std;

class Queue
{
	private:
		int arr[5];
		int front, rear; // front and rear pointers

	public:
		Queue()
		{
			front = -1;
			rear = -1;
		}
	// check if the queue is empty
	bool isEmpty()
	{
		return front == -1;
	}

	// Check if the queue is full
	bool isFull()
	{
		return rear == 4;   // array is size 5
	}

	// Enqueue (insert element at the rear)
	void enqueue(int value)
	{
		if (isFull())
		{
			cout << "Queue overflow! Cannot enqueue " << value << endl;
			return;
		}
		if (front == -1) front = 0; //first element
		arr[++rear] = value;
		cout << value << " enqueued into the queue." << endl;
	}

	// Dequeue (remove element from the front)
	void dequeue()
	{
		if (isEmpty())
		{
			cout << "Queue underflow! No element to dequeue." << endl;
			return;
		}
		cout << arr[front] << " dequeued from the queue" << endl;
		if (front >= rear) //reset when queue becomes empty
		{
			front = rear -1;
		}
		else
		{
			front++;
		}
	}

	// peek (view front element)
	void peek()
	{
		if (isEmpty())
		{
			cout << "Queue is empty!" << endl;
			return;
		}
		cout << "Front element: " << arr[front] << endl;
	}

	// Display queue elements
	void display()
	{
		if (isEmpty())
		{
			cout << "Queue is empty!" << endl;
			return;
		}
		cout << "Queue: ";
		for (int i = front; i <= rear; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}
};


int main()
{
	Queue q;

	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);
	q.display();

	q.peek();

	q.dequeue();
	q.display();

	return 0;
}
