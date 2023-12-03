#include<iostream>
#include<fstream>
#include<string>
#include<vector>

inline bool IsNumber(char ch) {return (ch>47)&&(ch<58);}
inline int ConvertToNumber(char ch) {return ch-48;}
inline bool IsSymbol(char ch) {return !IsNumber(ch) && ch!='.';}

bool CheckSurroundings(const std::string& input, int i, int lineLength, int numberRows)
{
    int columnIndex     {i % lineLength};
    bool notFirstColumn {columnIndex > 0};
    bool notLastColumn  {columnIndex < lineLength-1};
    bool notFirstLine   {i-lineLength >= 0};
    bool notLastLine    {i+lineLength < lineLength*numberRows};
    return IsSymbol((notFirstColumn ? input[i-1] : '.')) || //previous
           IsSymbol((notLastColumn  ? input[i+1] : '.')) || //next
           IsSymbol((notFirstLine   ? input[i-lineLength] : '.')) || //above
           IsSymbol((notLastLine    ? input[i+lineLength] : '.')) || //below
           IsSymbol((notFirstLine && notFirstColumn ? input[i-1-lineLength] : '.')) || //previous+above
           IsSymbol((notLastLine  && notFirstColumn ? input[i-1+lineLength] : '.')) || //previous+below
           IsSymbol((notFirstLine && notLastColumn ? input[i+1-lineLength] : '.'))  || //next+above
           IsSymbol((notLastLine  && notLastColumn ? input[i+1+lineLength] : '.'));    //next+below
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
        if (IsNumber(input[i]) && CheckSurroundings(input, i, lineLength, numberRows))
        {
            flags[i] = 1;
            if (i-1 >= 0 && IsNumber(input[i-1])) {flags[i-1] = 1;}
            if (i-2 >= 0 && IsNumber(input[i-1]) && IsNumber(input[i-2])) {flags[i-2] = 1;}
            if (i+1 < lineLength*numberRows && IsNumber(input[i+1])) {flags[i+1] = 1;}
            if (i+2 < lineLength*numberRows && IsNumber(input[i+1]) && IsNumber(input[i+2])) {flags[i+2] = 1;}
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
    int lineLength {141};
    int numberRows {140};

    // Write input file into a SINGLE string
    std::string dummyLine {};
    std::string endOfLine {"."};
    std::string fileString;
    while (std::getline(inputFile, dummyLine))
    {
        fileString += dummyLine + endOfLine;
    }

    // Initialize and set flag vector
    std::vector<int> flagVector(fileString.size());
    SetFlags(fileString, flagVector, lineLength, numberRows);

    // Do actual task
    int result {0};
    for (std::string::size_type i = 0; i < fileString.size(); i++)
    {
        if (flagVector[i]==1 && !IsNumber(fileString[i+1]))
        {
            result += (IsNumber(fileString[i-2]) && IsNumber(fileString[i-1]) ? ConvertToNumber(fileString[i-2]) : 0)*100 +
                      (IsNumber(fileString[i-1]) ? ConvertToNumber(fileString[i-1]) : 0)*10  +
                      ConvertToNumber(fileString[i]);
        }
    }

    std::cout << "The result is: " << result << '\n';

    return 0;
}