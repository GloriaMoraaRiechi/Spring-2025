#include <iostream>

using namespace std;

// Creating a namespace called MyNS
namespace MyNS
{
    int x;  // Global variable inside the namespace

    void displayX()
    {
        cout << "x = " << x << endl;
    }

    int mult(int x, int y)  // Correct function signature
    {
        return x * y;  // Using function parameters, not MyNS::x
    }
}

int main()
{
    MyNS::x = 99;  // Using variable inside the namespace
    MyNS::displayX();  // Calling function in namespace

    int a = 10, b = 20, c;
    c = MyNS::mult(a, b);  // Calling function inside namespace

    cout << "Multiplication result: " << c << endl;

    return 0;
}

