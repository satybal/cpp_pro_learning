#include "matrix.hpp"

int main()
{
    Matrix<int, 0> matrix;

    for (auto i = 0; i < 10; ++i)
        matrix[i][i] = i;

    for (auto i = 0; i < 10; ++i)
        matrix[i][9 - i] = 9 - i;

    for (auto i = 1; i < 9; ++i)
    {
        for (auto j = 1; j < 9; ++j)
        {
            cout << matrix[j][i] << " ";
        }
        cout << endl;
    }

    cout << "Size: " << matrix.size() << endl;
    matrix.print();

    return 0;
}