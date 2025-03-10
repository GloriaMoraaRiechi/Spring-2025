#include <iostream>
#include <thread>

using namespace std;

void print_message(const string& message)
{
	cout << "Thread says: " << message << endl;
}

int main()
{
	thread t1(print_message, "hello from thread one!");
	thread t2(print_message, "hello from thread two!");

	// wait for threads to finish execution
	t1.join();
	t2.join();

	cout << "Threads have finished execution!" << endl;
	return 0;
}
