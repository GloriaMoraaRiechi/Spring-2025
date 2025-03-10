#include <iostream>

using namespace std;

int main()
{
    int row = 5, col = 4;
    int result[row] = {0};  // Correct size for row vector
    int m[row][col] = {
        {1, 0, 2, 0},
        {0, 3, 0, 4},
        {0, 0, 5, 0},
        {6, 0, 0, 7},
        {1, 2, 3, 4} 
    };

    int v[col] = {2, 5, 1, 8};

    // Matrix-vector multiplication
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            result[i] += m[i][j] * v[j];
        }
    }

    // Print result as a column vector
    cout << "Result of matrix-vector multiplication: " << endl;
    for (int i = 0; i < row; i++)
    {
        cout << result[i] << endl;  // Print each element in a new line
    }

    return 0;
}

