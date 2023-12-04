#include<iostream>
#include<fstream>
#include<string>
#include<vector>

inline bool IsNumber(char ch) {return (ch>47)&&(ch<58);}
inline int ConvertToNumber(char ch) {return ch-48;}
int ConvertSeqToNumber(const std::string& input, int i)
{
    return (i-2 >= 0 && IsNumber(input[i-2]) && IsNumber(input[i-1]) ? ConvertToNumber(input[i-2]) : 0)*100 +
           (i-1 >= 0 && IsNumber(input[i-1]) ? ConvertToNumber(input[i-1]) : 0)*10  +
           ConvertToNumber(input[i]);
}

int CheckSurroundings(const std::string& input, int i, int lineLength, int numberRows)
{
    int columnIndex     {i % lineLength};
    bool notFirstColumn {columnIndex > 0};
    bool notLastColumn  {columnIndex < lineLength-1};
    bool notFirstLine   {i-lineLength >= 0};
    bool notLastLine    {i+lineLength < lineLength*numberRows};

    bool left {notFirstColumn && IsNumber(input[i-1])};
    bool topLeft {notFirstLine && notFirstColumn && IsNumber(input[i-1-lineLength])};
    bool top {notFirstLine && IsNumber(input[i-lineLength])};
    bool topRight {notFirstLine && notLastColumn && IsNumber(input[i+1-lineLength])};
    bool right {notLastColumn && IsNumber(input[i+1])};
    bool bottomRight {notLastColumn && notLastLine && IsNumber(input[i+1+lineLength])};
    bool bottom {notLastLine && IsNumber(input[i+lineLength])};
    bool bottomLeft {notLastLine  && notFirstColumn && IsNumber(input[i-1+lineLength])};

    int leftN {ConvertSeqToNumber(input, i-1)};
    int topLeftN {ConvertSeqToNumber(input, i-1-lineLength)};
    int topN {ConvertSeqToNumber(input, i-lineLength)};
    int topRightN {ConvertSeqToNumber(input, i+1-lineLength)};
    int rightN {ConvertSeqToNumber(input, i+1)};
    int bottomRightN {ConvertSeqToNumber(input, i+1+lineLength)};
    int bottomN {ConvertSeqToNumber(input, i+lineLength)};
    int bottomLeftN {ConvertSeqToNumber(input, i-1+lineLength)};

    int counter {0};

    if (left) {counter++;}
    if (right) {counter++;}
    if (topLeft) {counter++;}
    if (bottomLeft) {counter++;}
    if (top && !topLeft) {counter++;}
    if (bottom && !bottomLeft) {counter++;}
    if (topRight && !top) {counter++;}
    if (bottomRight && !bottom) {counter++;}

    int gearRatio {0};
    if (counter == 2)
    {
        gearRatio = (left ? leftN : 1) *
                    (topLeft ? topLeftN : 1) *
                    (top ? topN : 1) *
                    (topRight ? topRightN : 1) *
                    (right ? rightN : 1) *
                    (bottomRight ? bottomRightN : 1) *
                    (bottom ? bottomN : 1) *
                    (bottomLeft ? bottomLeftN : 1);
    }

    return gearRatio;

}

/* void SetFlags(const std::string& input, std::vector<int>& flags, int lineLength, int numberRows)
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
} */

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
    /* std::vector<int> flagVector(fileString.size());
    SetFlags(fileString, flagVector, lineLength, numberRows); */

    // Do actual task
    int result {0};
    for (std::string::size_type i = 0; i < fileString.size(); i++)
    {
        if (fileString[i] == '*')
        {
            result += CheckSurroundings(fileString, i, lineLength, numberRows);
        }
    }

    std::cout << "The result is: " << result << '\n';

    return 0;
}