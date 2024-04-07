#include "matrix.hpp"

int main() 
{
    Matrix<int, 2, -1> matrix;
    // number 2 is not defalt value, it's a number or dimensions

    cout << "Adding cells:" << endl;
    matrix.push(10).push(8) = 1;
    matrix.push(5).push(4) = 2;
    matrix.push(3).push(2) = 3;
    cout << matrix[10][8]  << " " 
         << matrix[5][4] << " " 
         << matrix[3][2] << endl;
    cout << "Size (should be 3): " << matrix.size() << endl << endl;

    cout << "Updating existing cells:" << endl;
    matrix.push(10).push(8) = 2;
    matrix.push(5).push(4) = 23;
    matrix.push(3).push(2) = 5;
    cout << matrix[10][8]  << " " 
         << matrix[5][4] << " " 
         << matrix[3][2] << endl;
    cout << "Size (should be 3): " << matrix.size() << endl << endl;

    cout << "trying to read from non-existent node" << endl;
    cout << matrix[3][0] << " " << matrix[6][3] << endl;
    cout << "Size (should be 3): " << matrix.size() << endl;

    return 0;
}
