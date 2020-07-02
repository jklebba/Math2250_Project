#include <vector>
#include <string>
using namespace std;

int NumCols(vector<vector<double>> matrix);
int NumRows(vector<vector<double>> matrix);
bool checkSameDim(vector<vector<double>> matrixA, vector<vector<double>> matrixB);
bool checkSquare(vector<vector<double>> matrixA);
bool checkMultiplyDim(vector<vector<double>> matrixA, vector<vector<double>> matrixB);
bool checkConsistentDims(vector<vector<double>> matrix);
bool checkNumericalVals(vector<vector<string>> matrix);
