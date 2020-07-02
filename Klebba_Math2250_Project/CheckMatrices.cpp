//Functions to test matrices for compatability before doing computations.
//Functions return true if matrix(s) have the desired attributes, false if not.

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include "IO_Functions.h"
#include "PrintFunctions.h"

using namespace std;

//Return number of rows of matrix
int NumRows(vector<vector<double>> matrix)
{
    return matrix.size();
}

//Return number of columns of a matrix
int NumCols(vector<vector<double>> matrix)
{
    size_t maxCols=0;
    for(int i=0;i<NumRows(matrix);i++)
    {
        if(matrix[i].size() > maxCols)
        {
            maxCols = matrix[i].size();
        }
    }
    return maxCols;
}

//Check if a matrix is square
bool checkSquare(vector<vector<double>> matrixA)
{
    if(NumRows(matrixA) == NumCols(matrixA))
    {
        return true;
    }
    cout << "Error: The matrice must be square." << endl;
    return false;
}

//Check if two matrices have the same dimensions
bool checkSameDim(vector<vector<double>> matrixA, vector<vector<double>> matrixB)
{
    if((NumRows(matrixA) != NumRows(matrixB)) || (NumCols(matrixA) != NumCols(matrixB)))
    {
        cout << "Error: The two matrices must have the same dimensions." << endl;
        return false;
    }
    return true;
}

//Check if the dimesions of two matrices are compatible for matrix Multiplication
bool checkMultiplyDim(vector<vector<double>> matrixA, vector<vector<double>> matrixB)
{
    if(NumCols(matrixA) != NumRows(matrixB))
    {
        cout << "Error: The second matrix must have the same number of rows as the first matrix has columns." << endl;
        return false;
    }
    return true;
}

//Check the dimensions of a matrix to make sure they are consistent
//i.e. make sure each row has the same number of elements
bool checkConsistentDims(vector<vector<double>> matrix)
{
    size_t rowLength=matrix[0].size();
    for(size_t i=0;i<matrix.size();i++)
    {
        if(matrix[i].size() != rowLength)
        {
            print(matrix);
            cout << "Error: The matrix's dimensions are not consistent." << endl;
            return false;
        }
        rowLength = matrix[i].size();
    }
    return true;
}

//Check a matrix of strings to make sure there are no non-numerical values
bool checkNumericalVals(vector<vector<string>> matrix)
{
    vector<char> accept = {'0','1','2','3','4','5','6','7','8','9','.','-'};
    
    for (const auto &inner : matrix)
    {
        for (const auto &element : inner)
        {
            bool fail = true;
            for(char const &c: element)
            {
            for(size_t k=0; k<accept.size();k++)
            {
                
                    if(c == accept[k])
                    {
                    fail = false;
                    }
            }
            
            if(fail)
            {
                print(matrix);
                cout << "Error: The matrice contains a non-numerical value." << endl;
                return false;
            }
            }
        }
        
    }
    return true;
}




