#include <iostream>
#include <stack>

using namespace std;

int main()
{
	stack<int> st;

	// Pushing elememts onto the stack
	st.push(1);
	st.push(2);
	st.push(3);

	while(!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	return 0;
}
