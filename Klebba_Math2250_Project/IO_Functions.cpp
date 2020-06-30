//Functions that define the I/O loop and serve as the driver/engine for the program.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "IO_Functions.h"
#include "MatrixOperations.h"
#include "CheckMatrices.h"
#include "PrintFunctions.h"

using namespace std;

//counter for filenames
int resultCount = 0;


//Get input from user, process input, and compute
void promptUser()
{
    string input;

    cout << endl << "Enter command: " << endl;
    getline(cin, input);
    cout << endl;

    if (input == "")
    {
        return;
    }
    if (input == "exit" || input == "Exit")
    {
        exit(0);
    }
    if (input == "help")
    {
        displayHelp();
        return;
    }

    vector<string> inputArgs;
    inputArgs = splitString(input, ' ');

    vector<vector<double>> matrixA;
    vector<vector<double>> matrixB;
    string operation;
    operation = inputArgs[0];

    //Process input arguments and populate matrices A and B if needed
    if (!processArgs(inputArgs, operation, matrixA, matrixB))
    {
        return;
    }
    
    vector<vector<double>> result;
    //Switch on operation type and perform the correct computation
    if (operation == "mult" || operation == "multiply" || operation == "multiplication" || operation == "Multiply")
    {
        print(matrixA, matrixB, "x");
        if (!multiply(matrixA, matrixB, result))
        {
            return;
        }
    }
    else if (operation == "transpose" || operation == "Transpose" || operation == "trans")
    {
        print(matrixA, "Transpose");
        transpose(matrixA, result);
    }
    else if (operation == "addition" || operation == "add" || operation == "Add")
    {
        print(matrixA, matrixB, "+");
        if (!add(matrixA, matrixB, result))
        {
            return;
        }
    }
    else if (operation == "subtraction" || operation == "subtract" || operation == "Subtract")
    {
        print(matrixA, matrixB, "-");
        if (!subtract(matrixA, matrixB, result))
        {
            return;
        }
    }
    else
    {
        cout << "Error: Unrecognized matrix operation.";
        return;
    }

    //print result and write to file if requested
    print(result);
    if(inputArgs[inputArgs.size()-1] == "file")
    {
        writeFile(result);
    }
    return;

}

//Process the input arguments and build the matrices
//Returns false if an error is encountered, true otherwise.
bool processArgs(vector<string> inputArgs, string operation, vector<vector<double>> &matrixA, vector<vector<double>> &matrixB)
{
    //Detemine if the operation takes two matrices or not
    vector<string> list = {"mult", "Mult", "multiply", "Multiply", "Add", "add", "subtract", "Subtract"};
    bool Op2 = false;
    for (int i = 0; i < list.size(); i++)
    {
        if (operation == list[i])
        {
            Op2 = true;
        }
    }
    
    //Determine which args to get matrices from, and if files are used
    int numArgs;
    bool file = false;
    if (inputArgs[inputArgs.size() - 1] == "file")
    {
        numArgs = inputArgs.size() - 1;
        file = true;
    }
    else
    {
        numArgs = inputArgs.size();
    }

    if ((Op2 && numArgs < 3) || numArgs < 2)
    {
        cout << "Error, not enough input arguments." << endl;
        return false;
    }

    //get matrices from the arguments and check for consistent matrix dimensions
    if (numArgs == 2)
    {
        if (!getMatrix(inputArgs[1], matrixA, file) || !checkConsistentDims(matrixA))
        {
            return false;
        }
    }
    else
    {
        if (!getMatrix(inputArgs[1], matrixA, file) || !checkConsistentDims(matrixA))
        {
            return false;
        }
        if (!getMatrix(inputArgs[2], matrixB, file) || !checkConsistentDims(matrixB))
        {
            return false;
        }
    }
    return true;
}

//Extracts matrices from user input or from the text file(s)
//Returns false if there is an error, true otherwise
bool getMatrix(string str, vector<vector<double>> &matrix, bool file)
{
    vector<vector<string>> elementsStr;

    //Put matrix elements into a 2d string vector
    if (!file)
    {
        vector<string> rows;
        rows = getRows(str);
        for (int i = 0; i < rows.size(); ++i)
        {
            elementsStr.push_back(getElements(rows[i]));
        }
    }
    else
    {
        ifstream infile(str);
        if (!infile.is_open())
        {
            cout << "An error occurred while opening the file" << endl;
            return false;
        }

        string line;
        vector<string> row;
        while (infile >> line)
        {
            elementsStr.push_back(getElements(line));
        }
        infile.close();
    }

    //Check for non numerical matrix elements
    if (!checkNumericalVals(elementsStr))
    {
        return false;
    }
    
    //Convert string matrix to doubles
    for (int i = 0; i < elementsStr.size(); i++)
    {
        vector<double> row;
        for (int j = 0; j < elementsStr[i].size(); j++)
        {
            row.push_back(stod(elementsStr[i][j]));
        }
        matrix.push_back(row);
    }
    return true;
}

//extract matrix row string from a user input string
vector<string> getRows(string str)
{
    vector<string> rows;
    rows = splitString(str, ';');
    return rows;
}

//extract matrix elements from a row string
vector<string> getElements(string str)
{
    vector<string> elements;
    elements = splitString(str, ',');
    return elements;
}

//split a string based on a delimiter parameter, ignore tabs
vector<string> splitString(string str, char delim)
{
    vector<string> strList;
    string word = "";
    for (auto x : str)
    {
        if (x == delim || x == '\t')
        {
            //cout << word << endl;
            if (word != "" && word != "\t")
            {
                strList.push_back(word);
                word = "";
            }
        }
        else
        {
            if (word != "\t")
            {
                word = word + x;
            }
        }
    }

    if (word != "" && word != "\t")
    {
        strList.push_back(word);
    }
    return strList;
}

//Write computation results to a file called result.txt
void writeFile(vector<vector<double>> matrix)
{
    resultCount++;
    string filename = "result";
    filename += to_string(resultCount);
    filename += ".txt";

    ofstream outfile(filename);
        if (!outfile.is_open())
        {
            cout << "An error occurred while writing the file" << endl;
        }
        
        for (const auto &inner : matrix)
    {
        for (const auto &element : inner)
        {
           outfile << element;
           outfile << ","; 
        }
        outfile << "\n";
    }
    outfile.close();
    cout << "Result written to file " << filename << endl;
}

void displayInstructions()
{
    cout << endl
         << "Enter commands in the form:" << endl;
    cout << "       <matrix operation> <matrix1> [matrix2] [file]" << endl
         << endl;
    cout << "Enter whitespace only between arguments, not within arguments. The arguments in square brackets are optional." << endl;
    cout << "Operations include 'tranpose', 'multiply', 'add', 'subtract'" << endl
         << endl;
    cout << "Enter matrices with commas separarting row elements and semicolons separating rows." << endl
         << endl;
    cout << "                        [1  2]" << endl;
    cout << "        1,2;3,4;   =    [3  4]" << endl
         << endl;
    cout << "Typing the word 'file' as the last argument lets you read and write matrices to files instead." << endl;
    cout << "Enter command 'help' to see more examples. 'exit' to exit" << endl
         << endl;
    cout << "Example input:" << endl;
    cout << "                         add 1,2;3,4; 1,1;1,1;" << endl;
    cout << "Results in the output:" << endl;
    cout << "                         [    1     2 ]     [    1     1 ]" << endl;
    cout << "                         [    3     4 ]  +  [    1     1 ]  =" << endl
         << endl;
    cout << "                          [    2     3 ] " << endl;
    cout << "                          [    4     5 ] " << endl
         << endl;
}

void displayHelp()
{
    cout << "READING FROM FILES" << endl;
    cout << "Input:" << endl;
    cout << "                         multiply pathtofile1 pathtofile2 file" << endl
         << endl;
    cout << "Will multiply the matrices found in the text files and write the result to a file. See the included example txt file for format." << endl;
    cout << "The paths can be replaced with file names if the files are in the same folder as the program's .exe file" << endl
         << endl
         << endl;
    

    cout << "SINGLE MATRIX OPERATION EXAMPLE" << endl;
    cout << "Example input:" << endl;
    cout << "                         transpose 1,2,3,4;5,6,7,8;" << endl;
    cout << "Results in the output:" << endl;
    cout << "                         [    1     2     3     4 ]" << endl;
    cout << "                         [    5     6     7     8 ]  Transpose  =" << endl
         << endl;
    cout << "                          [    1     5 ]" << endl;
    cout << "                          [    2     6 ]" << endl;
    cout << "                          [    3     7 ]" << endl;
    cout << "                          [    4     8 ]" << endl << endl;
}

