#include <vector>
using namespace std;

void sayHello();
bool add(vector<vector<double>> matrixA, vector<vector<double>> matrixB, vector<vector<double>> &result);
bool subtract(vector<vector<double>> matrixA, vector<vector<double>> matrixB, vector<vector<double>> &result);
bool multiply(vector<vector<double>> matrixA, vector<vector<double>> matrixB, vector<vector<double>> &result);
bool transpose(vector<vector<double>> matrixA, vector<vector<double>> &result);