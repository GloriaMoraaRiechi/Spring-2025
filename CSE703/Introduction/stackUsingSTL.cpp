#include <iostream>
#include <stack>

using namespace std;

int main()
{
	stack<int> s;

	s.push(10);
	s.push(20);
	s.push(30);

	cout << "Top element: " << s.top() << endl;

	s.pop();
	cout << "After popping top element: " << s.top() << endl;

	cout << "Stack size: " << s.size() << endl;

	return 0;
}
