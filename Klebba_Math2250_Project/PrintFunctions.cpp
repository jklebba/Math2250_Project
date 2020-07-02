//Various print functions for  prining matrices with different formatting
//Code could use re-factoring/modularizing.

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "IO_Functions.h"
#include "PrintFunctions.h"
#include "CheckMatrices.h"
#include "algorithm"

//Print a singel matrix
void print(vector<vector<double>> matrix)
{
    //cout settings to ensure nice formatting
    int coutWidth = 5;
    int largeNumWidth = 11;
    cout << setprecision(4);

    //set appropriate cout display width
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] / 9999 > 1.0)
            {
                coutWidth = largeNumWidth;
                break;
            }
        }
        if (coutWidth == largeNumWidth)
        {
            break;
        }
    }

    //print matrix elements
    cout << " [";
    for (size_t i = 0; i < matrix.size(); i++)
    {
        if (i != 0)
        {
            cout << "]" << endl
                 << " [";
        }
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            cout.width(coutWidth);
            cout << matrix[i][j] << " ";
        }
    }
    cout << "]" << endl << endl;;


    return;
}

//Print a single matrix and its operator
void print(vector<vector<double>> matrix, string op)
{
    //cout settings to ensure nice formatting
    int coutWidth = 5;
    int largeNumWidth = 11;
    cout << setprecision(4);

    //set appropriate cout display width
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] / 9999 > 1.0)
            {
                coutWidth = largeNumWidth;
                break;
            }
        }
        if (coutWidth == largeNumWidth)
        {
            break;
        }
    }

    //print matrix elements
    bool beenDone = false;
    for (size_t i = 0; i < matrix.size(); i++)
    {
        cout << "[";
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            cout.width(coutWidth);
            cout << matrix[i][j] << " ";
        }
        cout << "]";
        if ((i == (unsigned)NumRows(matrix) / 2) && !beenDone)
        {
            cout << "  " << op << "  =";
            beenDone = true;
        }
        cout << endl;
    }
    cout << endl;
    return;
}

//print a single matrix
void print(vector<vector<string>> matrix)
{
    //cout settings to ensure nice formatting
    int coutWidth = 5;
    int largeNumWidth = 11;
    cout << setprecision(4);

    //set appropriate cout display width
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j].size() > 4)
            {
                coutWidth = matrix[i][j].size();
                break;
            }
        }
        if (coutWidth == largeNumWidth)
        {
            break;
        }
    }

    //print matrix elements
    cout << " [";
    for (size_t i = 0; i < matrix.size(); i++)
    {
        if (i != 0)
        {
            cout << "]" << endl
                 << " [";
        }
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            cout.width(coutWidth);
            cout << matrix[i][j] << " ";
        }
    }
    cout << "]" << endl;

    return;
}

//print two matrices
void print(vector<vector<double>> matrixA, vector<vector<double>> matrixB)
{
    //cout settings to ensure nice formatting
    int coutWidth = 5;
    int largeNumWidth = 10;
    cout << setprecision(4);

    //set appropriate cout display width
    for (size_t i = 0; i < matrixA.size(); i++)
    {
        for (size_t j = 0; j < matrixA[i].size(); j++)
        {
            if (matrixA[i][j] / 9999 > 1.0)
            {
                coutWidth = largeNumWidth;
                break;
            }
        }
        if (coutWidth == largeNumWidth)
        {
            break;
        }
    }

    for (size_t i = 0; i < matrixB.size(); i++)
    {
        for (size_t j = 0; j < matrixB[i].size(); j++)
        {
            if (matrixB[i][j] / 9999 > 1.0)
            {
                coutWidth = largeNumWidth;
                break;
            }
        }
        if (coutWidth == largeNumWidth)
        {
            break;
        }
    }

    //print matrix elements
    int rowsA = NumRows(matrixA);
    int rowsB = NumRows(matrixB);
    int colsA = NumCols(matrixA);
    int colsB = NumCols(matrixB);

    for (int i = 0; i < max(rowsA, rowsB); i++)
    {
        cout << "[";

        int currColsA = matrixA[i].size();
        for (int j = 0; j < min(currColsA, colsA); j++)
        {
            if (i < rowsA && j < colsA)
            {
                cout.width(coutWidth);
                cout << matrixA[i][j] << " ";
            }
        }
        cout << "]    [";

        int currColsB = matrixB[i].size();
        for (int j = 0; j < min(currColsB, colsB); j++)
        {
            if (i < rowsB && j < colsB)
            {
                cout.width(coutWidth);
                cout << matrixB[i][j] << " ";
            }
        }
        cout << "]" << endl;
    }
    cout << endl;

    return;
}

//Print two matrices and their operator
void print(vector<vector<double>> matrixA, vector<vector<double>> matrixB, string op)
{

    //cout settings to ensure nice formatting
    int coutWidth = 5;
    int largeNumWidth = 11;
    cout << setprecision(4);

    //set appropriate cout display width
    for (size_t i = 0; i < matrixA.size(); i++)
    {
        for (size_t j = 0; j < matrixA[i].size(); j++)
        {
            if (matrixA[i][j] / 9999 > 1.0)
            {
                coutWidth = largeNumWidth;
                break;
            }
        }
        if (coutWidth == largeNumWidth)
        {
            break;
        }
    }

    for (size_t i = 0; i < matrixB.size(); i++)
    {
        for (size_t j = 0; j < matrixB[i].size(); j++)
        {
            if (matrixB[i][j] / 9999 > 1.0)
            {
                coutWidth = largeNumWidth;
                break;
            }
        }
        if (coutWidth == largeNumWidth)
        {
            break;
        }
    }

    //print matrix elements
    int rowsA = NumRows(matrixA);
    int rowsB = NumRows(matrixB);
    int colsA = NumCols(matrixA);
    int colsB = NumCols(matrixB);

    bool beenDone = false;
    for (int i = 0; i < max(rowsA, rowsB); i++)
    {
        int currColsA = matrixA[i].size();

        if (i < rowsA)
        {
            cout << "[";
        }
        else
        {
            cout << " ";
        }

        for (int j = 0; j < colsA; j++)
        {
            if (i >= rowsA)
            {
                cout.width(coutWidth);
                cout << ""
                     << " ";
            }
            else if (j < currColsA)
            {
                cout.width(coutWidth);
                cout << matrixA[i][j] << " ";
            }
            else
            {
                cout.width(coutWidth);
                cout << ""
                     << " ";
            }
        }
        if (i < rowsA)
        {
            cout << "]";
        }
        else
        {
            cout << " ";
        }

        if (i == (min(rowsA, rowsB) / 2) && !beenDone)
        {
            cout << "  " << op << "  ";
        }
        else
        {
            cout << "     ";
        }

        int currColsB = matrixB[i].size();
        if (i < rowsB)
        {
            cout << "[";
        }
        else
        {
            cout << " ";
        }

        for (int j = 0; j < colsB; j++)
        {
            if (i >= rowsB)
            {
                cout.width(coutWidth);
                cout << ""
                     << " ";
            }
            else if (j < currColsB)
            {
                cout.width(coutWidth);
                cout << matrixB[i][j] << " ";
            }
            else
            {
                cout.width(coutWidth);
                cout << ""
                     << " ";
            }
        }
        if (i < rowsB)
        {
            cout << "]";
        }
        else
        {
            cout << " ";
        }

        if (i == (min(rowsA, rowsB) / 2) && !beenDone)
        {
            cout << "  =" << endl;
            beenDone = true;
        }
        else
        {
            cout << endl;
        }
    }
    cout << endl;

    return;
}