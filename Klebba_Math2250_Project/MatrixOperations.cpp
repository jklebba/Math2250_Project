//Matrix Operation Functions
//Two dimensional vectors of doubles are used to represent matrices in these functions.

#include <vector>
#include "MatrixOperations.h"
#include "CheckMatrices.h"

using namespace std;

//MATRIX ADDITION
//INPUTS: 'matrixA' and 'matrixB' are matrices to be summed. The resulting matrix is written to 'result'
//OUTPUTS: returns 'false' if computation fails, 'true' otherwise
bool add(vector<vector<double>> matrixA, vector<vector<double>> matrixB, vector<vector<double>> &result)
{
    //ensure the two matrices have the same dimensions
    if(!(checkSameDim(matrixA,matrixB)))
        {
            return false;
        }

    //create a matrix to hold the result
    int rows = matrixA.size(); int cols = matrixA[0].size(); vector<vector<double>> holder( rows, vector<double> (cols, 0)); 

    //iterate through both matrices and sum elementwise
    for(int i=0; i<matrixA.size(); i++)
    {
        for(int j=0; j<matrixA[i].size(); j++)
        {
            holder[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    //write to result
    result = holder;
    return true;
}

//MATRIX SUBTRACTION
//INPUTS: 'matrixB' is subtracted from 'matrixA'. The resulting matrix is written to 'result'
//OUTPUTS: returns 'false' if computation fails, 'true' otherwise
bool subtract(vector<vector<double>> matrixA, vector<vector<double>> matrixB, vector<vector<double>> &result)
{
    //ensure the two matrices have the same dimensions
    if(!(checkSameDim(matrixA,matrixB)))
        {
            return false;
        }

    //create a matrix to hold the result    
    int rows = matrixA.size(); int cols = matrixA[0].size(); vector<vector<double>> holder( rows, vector<double> (cols, 0)); 

    //iterate through both matrices and subtract elementwise
    for(int i=0; i<matrixA.size(); i++)
    {
        for(int j=0; j<matrixA[i].size(); j++)
        {
            holder[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
    //write to result
    result = holder;
    return true;
}

//MATRIX MULTIPLICATION
//INPUTS: 'matrixA' and 'matrixB' are multplied. The resulting matrix is written to 'result'
//OUTPUTS: returns 'false' if computation fails, 'true' otherwise
bool multiply(vector<vector<double>> matrixA, vector<vector<double>> matrixB, vector<vector<double>> &result)
{
    //ensure matrix dimensions are compatible with matrix multiplication
    if(!(checkMultiplyDim(matrixA,matrixB)))
        {
            return false;
        }
    
    //init holder
    int rows = matrixA.size(); int cols = matrixB[0].size(); vector<vector<double>> holder( rows, vector<double> (cols, 0)); 

    //length of the dot product
    int dpLength = matrixA[0].size();
    
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            //compute the proper dot product and store in holder
            double dotProd = 0;
            for(int k=0; k<dpLength; k++)
            {
                dotProd = dotProd + (matrixA[i][k]*matrixB[k][j]);
            }
            holder[i][j] = dotProd;
        }
    }
    //write to result
    result = holder;
    return true;
}

//MATRIX TRANSPOSE
//INPUTS: 'matrixA' is the matrix to be transposed. The resulting matrix is written to 'result'
//OUTPUTS: returns 'true'
bool transpose(vector<vector<double>> matrixA, vector<vector<double>> &result)
{
    //init holder
    int rows = matrixA.size(); int cols = matrixA[0].size(); vector<vector<double>> holder( cols, vector<double> (rows, 0));

    //iterate through matrixA and store the values in holder with swapped indices i and j
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
           holder[j][i]= matrixA[i][j]; 
        }
    }
    //write to result
    result = holder;
    return true;
}