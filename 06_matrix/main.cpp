#include "matrix.hpp"

int main() 
{
    Matrix<int, 2> matrix;
    // number 2 is not defalt value, it's a number or dimensions

    matrix[1][5] = 1;
    matrix[10][3] = 2;
    matrix[8][1] = 3;
    cout << matrix[1][5]  << " "<< matrix[10][3] << " " << matrix[8][1] << endl;
    cout << "Size (should be 3): " << matrix.size() << endl;

    cout << "trying to read from non-existent node" << endl;
    cout << matrix[1][4] << endl;
    cout << "Size (should be 3): " << matrix.size() << endl;

    return 0;
}
