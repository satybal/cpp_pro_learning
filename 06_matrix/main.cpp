#include <cassert>
#include "matrix.hpp"

int main()
{
    Matrix<int, 2, -1> matrix0;
    assert(matrix0.size() == 0); // все ячейки свободны
    auto a = matrix0[0][0];
    assert(a == -1);
    assert(matrix0.size() == 0);
    matrix0[100][100] = 314;
    assert(matrix0[100][100] == 314);
    assert(matrix0.size() == 1);
    

    Matrix<int, 2, 0> matrix;

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

    return 0;
}