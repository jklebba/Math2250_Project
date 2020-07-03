#include <vector>
using namespace std;

void sayHello();
bool add(vector<vector<double>> matrixA, vector<vector<double>> matrixB, vector<vector<double>> &result);
bool subtract(vector<vector<double>> matrixA, vector<vector<double>> matrixB, vector<vector<double>> &result);
bool multiply(vector<vector<double>> matrixA, vector<vector<double>> matrixB, vector<vector<double>> &result);
bool transpose(vector<vector<double>> matrixA, vector<vector<double>> &result);
bool rref(vector<vector<double>> matrixA, vector<vector<double>> &result);
bool determinant(vector<vector<double>> matrix, double &result);
vector<vector<double>> cofactor(vector<vector<double>> matrix, int cofRow, int cofCol);
bool adjoint(vector<vector<double>> matrix, vector<vector<double>>& result);
bool inverse(vector<vector<double>> matrix, vector<vector<double>>& result);