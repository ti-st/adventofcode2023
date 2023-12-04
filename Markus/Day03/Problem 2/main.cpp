#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<numeric>

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

struct VicinityFlags
{
    bool left {false};
    bool topLeft {false};
    bool top {false};
    bool topRight {false};
    bool right {false};
    bool bottomRight {false};
    bool bottom {false};
    bool bottomLeft {false};
};

VicinityFlags SetVicinityFlags(const std::string& input, int i, int lineLength, int numberRows)
{
    int columnIndex {i % lineLength};
    VicinityFlags flags;

    if (columnIndex > 0 && IsNumber(input[i-1])) {flags.left = true;}
    if (i-lineLength >= 0 && columnIndex > 0 && IsNumber(input[i-1-lineLength])) {flags.topLeft = true;}
    if (i-lineLength >= 0 && IsNumber(input[i-lineLength])) {flags.top = true;}
    if (i-lineLength >= 0 && columnIndex < lineLength-1 && IsNumber(input[i+1-lineLength])) {flags.topRight = true;}
    if (columnIndex < lineLength-1 && IsNumber(input[i+1])) {flags.right = true;}
    if (columnIndex < lineLength-1 && i+lineLength < lineLength*numberRows && IsNumber(input[i+1+lineLength])) {flags.bottomRight = true;}
    if (i+lineLength < lineLength*numberRows && IsNumber(input[i+lineLength])) {flags.bottom = true;}
    if (i+lineLength < lineLength*numberRows  && columnIndex > 0 && IsNumber(input[i-1+lineLength])) {flags.bottomLeft = true;}

    return flags;
}

int NumberOfAdjacentNumbers(const std::string& input, int i, int lineLength, int numberRows)
{
    VicinityFlags flags {SetVicinityFlags(input, i, lineLength, numberRows)};

    int counter {0};
    if (flags.left) {counter++;}
    if (flags.right) {counter++;}
    if (flags.topLeft) {counter++;}
    if (flags.bottomLeft) {counter++;}
    if (flags.top && !flags.topLeft) {counter++;}
    if (flags.bottom && !flags.bottomLeft) {counter++;}
    if (flags.topRight && !flags.top) {counter++;}
    if (flags.bottomRight && !flags.bottom) {counter++;}

    return counter;
}

std::vector<int> GearRatio(const std::string& input, int i, int lineLength, int numberRows)
{
    VicinityFlags flags {SetVicinityFlags(input, i, lineLength, numberRows)};
    std::vector<int> partNumbers;

    if (flags.left) {partNumbers.push_back(ReadNumber(input, i-1));}
    if (flags.right) {partNumbers.push_back(ReadNumber(input, i+1));}
    if (flags.topLeft) {partNumbers.push_back(ReadNumber(input, i-1-lineLength));}
    if (flags.bottomLeft) {partNumbers.push_back(ReadNumber(input, i-1+lineLength));}
    if (flags.top && !flags.topLeft) {partNumbers.push_back(ReadNumber(input, i-lineLength));}
    if (flags.bottom && !flags.bottomLeft) {partNumbers.push_back(ReadNumber(input, i+lineLength));}
    if (flags.topRight && !flags.top) {partNumbers.push_back(ReadNumber(input, i+1-lineLength));}
    if (flags.bottomRight && !flags.bottom) {partNumbers.push_back(ReadNumber(input, i+1+lineLength));}

    return partNumbers;
}

void SetFlags(const std::string& input, std::vector<int>& flags, int lineLength, int numberRows)
{
    if (input.size() != flags.size())
    {
        std::cout << "Error: input and flags have different sizes!\n";
        exit(1);
    }

    for (std::string::size_type i = 0; i < input.size(); i++)
    {
        if (input[i]=='*' && NumberOfAdjacentNumbers(input, i, lineLength, numberRows)==2)
        {
            flags[i] = 1;
        }
    }
}

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_3_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }

    // length of line in input file
    int lineLength {140};
    int numberRows {140};

    // Write input file into a SINGLE string
    std::string dummyLine {};
    //std::string endOfLine {"."};
    std::string fileString;
    while (std::getline(inputFile, dummyLine))
    {
        fileString += dummyLine;
    }

    // Initialize and set flag vector
    std::vector<int> flagVector(fileString.size());
    SetFlags(fileString, flagVector, lineLength, numberRows);

    // Do actual task
    std::vector<int> resultVector;
    for (std::string::size_type i = 0; i < fileString.size(); i++)
    {
        if (flagVector[i]==1)
        {
            std::vector<int> tmp = GearRatio(fileString, i, lineLength, numberRows);
            if (tmp.size() == 2)
            {
                resultVector.push_back(tmp[0]*tmp[1]);
            }
            else
            {
                std::cout << "Error: tmp.size() != 2\n";
                exit(1);
            }
        }
    }
    
    // Calculate the sum over resultVector
    int sum = std::accumulate(resultVector.begin(), resultVector.end(), 0);

    // Print the sum
    std::cout << "The sum is: " << sum << '\n';

    return 0;
}
