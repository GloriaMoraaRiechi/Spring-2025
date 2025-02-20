// Stores dynamically allocated memory. Managed manually. Larger tthan the stack but slower due to manual allocation/deallocation. memory leaks can occur if memory is not freed

#include <iostream>

using namespace std;

int main()
{
	int* ptr = new int(10); //alocated on the heap
	cout << *ptr << endl;
	delete ptr; //free memory to avoid leak
	return 0;
}
