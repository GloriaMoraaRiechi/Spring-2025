#include <iostream>
#include <stack>
using namespace std;

// Function to evaluate a postfix expression
int evaluatePostfix(string postfix) {
    stack<int> s;

    for (char ch : postfix) {
        // If operand, push to stack
        if (isdigit(ch)) {
            s.push(ch - '0'); // Convert char to int
        }
        // If operator, pop two elements and apply operation
        else {
            int val2 = s.top(); s.pop();
            int val1 = s.top(); s.pop();

            switch (ch) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
            }
        }
    }

    return s.top(); // Final result
}

int main() {
    string postfix;
    cout << "Enter postfix expression: ";
    cin >> postfix;

    cout << "Result: " << evaluatePostfix(postfix) << endl;

    return 0;
}
