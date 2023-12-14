#include "hot_springs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <numbers>
#include <numeric>

inline bool IsNumber(char ch) {return (ch>47)&&(ch<58);}
inline int ConvertToNumber(char ch) {return ch-48;}

int IntPower(int x, unsigned int p)
{
    if (p == 0) {return 1;}
    if (p == 1) {return x;}
    
    int tmp = IntPower(x, p/2);
    if (p%2 == 0) {return tmp * tmp;}
    else {return x * tmp * tmp;}
}

int ReadNumberFromRight(const std::string& line, int i, int counter = 0)
{
    int tmp {0};
    if (i>0 && IsNumber(line[i-1]))
    {
        tmp = ReadNumberFromRight(line, i-1, counter+1);
    }
    return tmp + ConvertToNumber(line[i]) * IntPower(10, counter);
}

int ReadNumber(const std::string& line, int i)
{
    if (i < line.size() && IsNumber(line[i+1]))
    {
        return ReadNumber(line, i+1);
    }
    else
    {
        return ReadNumberFromRight(line, i);
    }
}

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_12_input.txt",std::ios_base::in);
    //inputFile.open("test_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }

    // Vector of SpringRows
    std::vector<SpringRow> springRows;

    // Read input file line by line
    std::string line;
    while (std::getline(inputFile, line))
    {
        springRows.push_back(SpringRow(line));
    }

    // Total number of valid spring configurations
    int totalNumberOfValidSpringConfigurations {0};

    // Loop over all spring rows and calculate total number of valid spring configurations
    for (SpringRow springRow : springRows)
    {
        totalNumberOfValidSpringConfigurations += springRow.NumberOfValidSpringConfigurations();
    }

    // Print total number of valid spring configurations
    std::cout << "Total number of valid spring configurations: " << totalNumberOfValidSpringConfigurations << "\n";

    // Close input file
    inputFile.close();

    return 0;
}
