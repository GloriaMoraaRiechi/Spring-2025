#include <iostream>
#include <stack>
using namespace std;

// Function to check if parentheses are balanced
bool isBalanced(string expr) {
    stack<char> s;

    for (char ch : expr) {
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch); // Push opening brackets
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.empty()) return false; // More closing brackets than opening
            
            char top = s.top();
            s.pop();

            // Check if the popped bracket matches the current closing bracket
            if ((ch == ')' && top != '(') || 
                (ch == '}' && top != '{') || 
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }

    return s.empty(); // Stack should be empty if brackets are balanced
}

int main() {
    string expr;
    cout << "Enter an expression: ";
    cin >> expr;

    if (isBalanced(expr))
        cout << "Balanced parentheses ✅" << endl;
    else
        cout << "Unbalanced parentheses ❌" << endl;

    return 0;
}

