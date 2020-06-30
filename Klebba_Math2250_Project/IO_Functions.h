#include <string>
#include <vector>
using namespace std;

void displayInstructions();
void displayHelp();


vector<string> splitString(string str, char delim);
vector<string> getRows(string str);
vector<string> getElements(string str);
bool getMatrix(string str, vector<vector<double>> &matrix, bool file);


void promptUser();
bool processArgs(vector<string> inputArgs, string operation, vector<vector<double>> &matrixA, vector<vector<double>> &matrixB);
void writeFile(vector<vector<double>> matrix);

