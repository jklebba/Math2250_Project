//Matrix Operation Functions
//Two dimensional vectors of doubles are used to represent matrices in these functions.

#include "iostream"
#include <cmath>
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
//INPUTS: 'matrix' is the matrix to be transposed. The resulting matrix is written to 'result'
//OUTPUTS: returns 'true'
bool transpose(vector<vector<double>> matrix, vector<vector<double>> &result)
{
    //init holder
    int rows = matrix.size(); int cols = matrix[0].size(); vector<vector<double>> holder( cols, vector<double> (rows, 0));

    //iterate through matrix and store the values in holder with swapped indices i and j
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
           holder[j][i]= matrix[i][j]; 
        }
    }
    //write to result
    result = holder;
    return true;
}


//MATRIX RREF (Reduced Row Echelon Form)
//INPUTS: 'matrix' is the matrix to find RREF of. The resulting matrix is written to 'result'
//OUTPUTS: returns 'true'
bool rref(vector<vector<double>> matrix, vector<vector<double>> &result)
{
    int rowCount = matrix.size(); int colCount = matrix[0].size();

    //init variable for column of leading term
    int leading = 0;

    //process each row from top to bottom of the matrix
    for (int row =0; row < rowCount; row++)
    {
        //dont let leading go out of index bounds
        if (colCount <= leading)
        {
            break;
        }   

        //variable for current row to consider
        int currRow = row;
    
        //search for next nonzero leading term
        while(matrix[currRow][leading] == 0)
        {
            //look down the current column
            currRow = currRow +1;

            //switch to next column over if needed
            if (rowCount == currRow)
            {
                currRow = row;
                leading = leading +1;
                if(colCount == leading)
                {
                    break;
                }
            }  
        }

        //swap the row containing possible nonzero leading term with the row we are processing
        vector<double> temp = matrix[currRow];
        matrix[currRow] = matrix[row];
        matrix[row] = temp;
        
        //if the leading term is nonzero then normalize it to 1 using row division
        if(matrix[row][leading] != 0)
        {
            double denom = matrix[row][leading];
            for(int k=0;k<colCount;k++)
            {
                matrix[row][k] = matrix[row][k]/denom;
            }
        }

        //zero all other entries in the column of the leading term using an appropriate row subtraction
        for(int i =0; i<rowCount; i++)
        {
            if(i != row)
            {
                double factor = matrix[i][leading];
                for (int col=0; col < colCount; col++)
                {
                matrix[i][col] = matrix[i][col] - (factor*matrix[row][col]);
                }
            }
        }
        //increment leading column
        leading = leading +1;
    }

    //Sometimes 0's are output as -0. change these -0's to 0's so output looks cleaner
    for(auto &row : matrix)
    {
        for ( auto &el : row)
        if(std::signbit(el) && el == 0)
        {
            el = el*-1;
        }
    }
    //write to result
    result = matrix;
    return true;
}
//got help from here https://rosettacode.org/wiki/Reduced_row_echelon_form


//MATRIX COFACTOR (used in determinant and adjoint functions below)
//INPUTS: 'matrix'= base matrix, 'cofRow'= row to take cofactor, 'cofCol'= column to take cofactor
//OUTPUTS: returns CoFactor matrix 'result'
vector<vector<double>> cofactor(vector<vector<double>> matrix, int cofRow, int cofCol)
{
    int dim = matrix.size();

    //Index variables for the CoFactor matrix
    int cofRowInd = 0;
    int cofColInd = 0; 

    //init result vector
    vector<vector<double>> result( dim-1, vector<double> (dim-1, 0));

    //Iterate through each element in matrix
    for(int i=0; i<dim;i++)
    {
        for(int j=0; j<dim; j++)
        {
            //add the eligible elements to the CoFactor matrix
            if(i != cofRow && j != cofCol)
            {
                result[cofRowInd][cofColInd] = matrix[i][j];

                //adjust CoFactor indices
                cofColInd = cofColInd+1;
                if(cofColInd == (dim-1))
                {
                    cofColInd=0;
                    cofRowInd = cofRowInd + 1;
                }
            }

        }
    }
    return result;
}
//Got help from here: https://www.geeksforgeeks.org/determinant-of-a-matrix/

//MATRIX DETERMINANT
//INPUTS: 'matrix' is the matrix to find the determinant of. The resulting matrix is written to 'result'
//OUTPUTS: returns 'false' if computation fails, 'true' otherwise
bool determinant(vector<vector<double>> matrix, double &result)
{
    //make sure matrix is square
    if(!checkSquare(matrix))
    {
        return false;
    }
    int dim = matrix.size();
    
    //init determinant variable
    double det = 0;

    //base case for recursion (1x1 matrix)
    if(dim < 2)
    {
        result =  matrix[0][0];
        return true;
    }

    //init matrix to hold cofactor
    vector<vector<double> > cofact( dim-1 , vector<double> (dim-1, 0)); 

    //init sign term in the determinant equation
    int signTerm = 1;

    //iterate through the first row of matrix
    int row = 0;
    for(int col=0; col<dim; col++)
    {
        //init variable for the determinant of the cofactors
        double cofactDet;
        //get the determinant of each cofactor
        cofact = cofactor(matrix,row,col);
        determinant(cofact,cofactDet);

        //sum the terms for each cofactor
        det = det + (signTerm*matrix[row][col]*cofactDet);

        //flip sign term each iteration
        signTerm = -1*signTerm;
    }
    //write answer to result
    result = det;
    return true;
}
//Got help from here: https://www.geeksforgeeks.org/determinant-of-a-matrix/


//MATRIX  ADJOINT
//INPUTS: 'matrix' is the matrix to find Adjoint of. The resulting matrix is written to 'result'
//OUTPUTS: returns 'false' if computation fails, 'true' otherwise.
bool adjoint(vector<vector<double>> matrix, vector<vector<double>>& result)
{
    //make sure matrix is square
    if (!checkSquare(matrix))
    {
        return false;
    }
    int dim = matrix.size();

    //init adjoint matrix to fill in
    vector<vector<double>> adjMatrix(dim, vector<double>(dim, 0));

    //adjoint of 1x1 matrix is always the Identity matrix
    if (dim == 1)
    {
        adjMatrix[0][0] = 1;
        result = adjMatrix;
        return true;
    }

    //iterate through the matrix elements
    for (int row=0; row < dim; row++)
    {
        for (int col = 0; col < dim; col++)
        {
            //get cofactor matrix for this element
            vector<vector<double>> cofact = cofactor(matrix, row, col);
         
            //compute sign of cofactor term
            int sign;
            if((row+col)%2 == 0)
            {
                sign = 1;
            }
            else
            {
                sign = -1;
            }

            //get determinant of cofactor matrix for this element
            double det;
            determinant(cofact, det);

            //populate the adjoint matrix as the tranpose of the cofactor matrix
            adjMatrix[col][row] = sign*det;
        }
    }
    //write to result
    result = adjMatrix;
    return true;
}
//got help from here: https://www.geeksforgeeks.org/adjoint-inverse-matrix/


//MATRIX  INVERSE
//INPUTS: 'matrix' is the matrix to find the inverse of. The resulting matrix is written to 'result'
//OUTPUTS: returns 'false' if the computation fails, 'true' otherwise.
bool inverse(vector<vector<double>> matrix, vector<vector<double>>& result)
{
    //make sure matrix is square
    if (!checkSquare(matrix))
    {
        return false;
    }
    int dim = matrix.size();

    //Check if the matrix is not invertible by checking if determinant = 0
    double det;
    determinant(matrix, det);
    if (det == 0)
    {
        cout << "Error: the matrix is not invertible." << endl;
        return false;
    }

    //get adjoint of matrix
    vector<vector<double>> adj;
    adjoint(matrix, adj);

    //init vector to build inverse matrix
    vector<vector<double>> inv(dim, vector<double>(dim, 0));

    //Use terms of adjoint matrix to calculate terms of inverse matrix
    for (int row = 0; row < dim; row++)
    {
        for (int col = 0; col < dim; col++)
        {
            inv[row][col] = adj[row][col] / det;
        }
    }
    //write to result
    result = inv;
    return true;
}
//got help from here: https://www.geeksforgeeks.org/adjoint-inverse-matrix/