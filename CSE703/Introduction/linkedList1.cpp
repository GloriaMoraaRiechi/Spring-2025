#include <iostream>

using namespace std;

// Node structure
class Node
{
	public:
		int data;  //data in the node
		Node* next;  //Pointer to the next node

		// Constructor to initialize a new node
		Node(int value)
		{
			data = value;
			next = nullptr;
		}
};

// Linked list class
class LinkedList
{
	private:
		Node* head;  //Pointer to the first node

	public:
		// constructor to initialize an empty list
		LinkedList()
		{
			head = nullptr;
		}

		// Function to add a node at the end
		void insert(int value)
		{
			Node* newNode = new Node(value); // create a new node
			if (head == nullptr) //if list is empty
			{
				head = newNode;
			}
			else
			{
				Node* temp = head;
				while (temp->next != nullptr)
				{
					temp = temp->next;
				}
				temp->next = newNode;  //link the new node at the end
			}
		}

		// Function to delete a node by a value
		void remove(int value)
		{
			if (head == nullptr)
			{
				cout << "List is empty" << endl;
				return;
			}

			if (head->data == value) // if the head is to be deleted
			{
				Node* temp = head;
				head = head->next;
				delete temp;
				return;
			}

			Node* temp = head;
			Node* prev = nullptr;
			while (temp != nullptr && temp->data != value) // search for the node
			{
				prev = temp;
				temp = temp->next;
			}

			if (temp == nullptr)
			{
				cout << "Value not found in the list!" << endl;
				return;
			}

			prev->next = temp->next; // unlink the node
			delete temp; //free memory
		}

		void display()
		{
			Node* temp = head;
			while (temp != nullptr)
			{
				cout << temp->data << " -> ";
				temp = temp->next;
			}
			cout << "NULL" << endl;
		}
};

int main()
{
	LinkedList list;

	// insert some values
	list.insert(10);
	list.insert(20);
	list.insert(30);

	// display the list
	cout << "Linked list: ";
	list.display();

	// delete a node
	list.remove(20);
	cout << "After deleting 20: ";
	list.display();

	return 0;
}
