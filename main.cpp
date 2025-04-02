#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int MATRIX_SIZE = 4; // fixed matrix size

class Matrix
{
private:
    int elements[MATRIX_SIZE][MATRIX_SIZE]; // 2d array to store matrix

public:
    // load matrix data from a file stream
    void loadFromFile(ifstream &fileStream)
    {
        for (int row = 0; row < MATRIX_SIZE; row++)
        {
            for (int col = 0; col < MATRIX_SIZE; col++)
            {
                if (!(fileStream >> elements[row][col]))
                {
                    cerr << "error: not enough or invalid data in file" << endl;
                    return;
                }
            }
        }
    }

    // display the matrix in aligned format
    void display() const
    {
        for (int row = 0; row < MATRIX_SIZE; row++)
        {
            for (int col = 0; col < MATRIX_SIZE; col++)
            {
                cout << setw(4) << elements[row][col]; // align columns
            }
            cout << endl;
        }
        cout << endl;
    }

    // add two matrices
    Matrix operator+(const Matrix &other) const
    {
        Matrix result;
        for (int row = 0; row < MATRIX_SIZE; row++)
        {
            for (int col = 0; col < MATRIX_SIZE; col++)
            {
                result.elements[row][col] = elements[row][col] + other.elements[row][col];
            }
        }
        return result;
    }

    // multiply two matrices
    Matrix operator*(const Matrix &other) const
    {
        Matrix result;
        for (int row = 0; row < MATRIX_SIZE; row++)
        {
            for (int col = 0; col < MATRIX_SIZE; col++)
            {
                result.elements[row][col] = 0;
                for (int k = 0; k < MATRIX_SIZE; k++)
                {
                    result.elements[row][col] += elements[row][k] * other.elements[k][col];
                }
            }
        }
        return result;
    }

    // calculate the sum of main and secondary diagonals
    int calculateDiagonalSum() const
    {
        int diagonalSum = 0;
        for (int i = 0; i < MATRIX_SIZE; i++)
        {
            diagonalSum += elements[i][i]; // main diagonal
            if (i != MATRIX_SIZE - 1 - i)
            {
                diagonalSum += elements[i][MATRIX_SIZE - 1 - i]; // secondary diagonal
            }
        }
        return diagonalSum;
    }

    // swap two rows
    void swapRows(int firstRow, int secondRow)
    {
        if (firstRow >= 0 && firstRow < MATRIX_SIZE && secondRow >= 0 && secondRow < MATRIX_SIZE)
        {
            for (int col = 0; col < MATRIX_SIZE; col++)
            {
                int temp = elements[firstRow][col];
                elements[firstRow][col] = elements[secondRow][col];
                elements[secondRow][col] = temp;
            }
        }
        else
        {
            cout << "error: invalid row indices for swapping" << endl;
        }
    }

    // swap two columns
    void swapColumns(int firstCol, int secondCol)
    {
        if (firstCol >= 0 && firstCol < MATRIX_SIZE && secondCol >= 0 && secondCol < MATRIX_SIZE)
        {
            for (int row = 0; row < MATRIX_SIZE; row++)
            {
                int temp = elements[row][firstCol];
                elements[row][firstCol] = elements[row][secondCol];
                elements[row][secondCol] = temp;
            }
        }
        else
        {
            cout << "error: invalid column indices for swapping" << endl;
        }
    }

    // update one element in the matrix
    void updateElement(int row, int col, int newValue)
    {
        if (row >= 0 && row < MATRIX_SIZE && col >= 0 && col < MATRIX_SIZE)
        {
            elements[row][col] = newValue; // change value
        }
        else
        {
            cout << "error: invalid indices for update" << endl;
        }
    }
};

int main()
{
    ifstream inputFile("matrix-data.txt"); // open file
    if (!inputFile)
    {
        cerr << "error: unable to open matrix-data.txt" << endl;
        return 1;
    }

    Matrix matrix1, matrix2;

    matrix1.loadFromFile(inputFile); // read first matrix
    cout << "matrix 1:" << endl;
    matrix1.display();

    matrix2.loadFromFile(inputFile); // read second matrix
    cout << "matrix 2:" << endl;
    matrix2.display();

    Matrix sumMatrix = matrix1 + matrix2; // add matrices
    cout << "sum of matrix 1 and matrix 2:" << endl;
    sumMatrix.display();

    Matrix productMatrix = matrix1 * matrix2; // multiply matrices
    cout << "product of matrix 1 and matrix 2:" << endl;
    productMatrix.display();

    cout << "diagonal sum of matrix 1: " << matrix1.calculateDiagonalSum() << endl;

    matrix1.swapRows(0, 2); // swap rows
    cout << "matrix 1 after swapping row 0 with row 2:" << endl;
    matrix1.display();

    matrix1.swapColumns(1, 3); // swap columns
    cout << "matrix 1 after swapping column 1 with column 3:" << endl;
    matrix1.display();

    matrix1.updateElement(2, 2, 99); // update element
    cout << "matrix 1 after updating element at row 2, col 2 to 99:" << endl;
    matrix1.display();

    return 0;
}
