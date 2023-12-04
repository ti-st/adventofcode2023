#include<iostream>
#include<fstream>
#include<string>
#include<vector>

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

int ReadNumber(const std::string& line, int i, int counter = 0)
{
    int tmp {0};
    if (i>0 && IsNumber(line[i-1]))
    {
        tmp = ReadNumber(line, i-1) * IntPower(10, counter+1);
    }
    return tmp + ConvertToNumber(line[i]) * IntPower(10, counter);
}

std::vector<int> ReadWinningNumbers(const std::string& line)
{
    // Offset at beginning of each line
    int offset {8};
    // Flag indicating end of winning numbers section
    bool flag {false};

    std::vector<int> result;
    for (int i = offset; i < line.size(); i++)
    {
        if (IsNumber(line[i]) && line[i+1]==' ' && !flag)
        {
            result.push_back(ReadNumber(line, i));
        }
        if (line[i+2] == '|') {flag = true;}
    }

    return result;
}

std::vector<int> ReadUserNumbers(const std::string& line)
{
    // Offset at beginning of each line
    int offset {40};

    std::vector<int> result;
    for (int i = offset; i < line.size(); i++)
    {
        if (IsNumber(line[i]) && line[i+1]==' ')
        {
            result.push_back(ReadNumber(line, i));
        }
    }

    return result;
}

int PointsOfTicket (const std::vector<int>& winningNumbers, const std::vector<int>& userNumbers)
{
    int numberOfMatches {0};
    for (auto usrN : userNumbers)
    {
        for (auto winN : winningNumbers)
        {
            if (usrN == winN) {numberOfMatches++;}
        }
    }
    return (numberOfMatches >= 1 ? IntPower(2, numberOfMatches-1) : 0);
}

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_4_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }

    // Read winning numbers
    std::string dummyLine {};
    int counter {0};
    std::vector<std::vector<int>> winningNumbers;
    while (std::getline(inputFile, dummyLine))
    {
        winningNumbers.push_back(ReadWinningNumbers(dummyLine));
        counter++;
    }

    // Go back to beginning of file
    inputFile.clear();
    inputFile.seekg(0);

    // Read user numbers
    dummyLine = "";
    std::string endOfLine {" "};
    counter = 0;
    std::vector<std::vector<int>> userNumbers;
    while (std::getline(inputFile, dummyLine))
    {
        userNumbers.push_back(ReadUserNumbers(dummyLine + endOfLine));
        counter++;
    }

    // Calculate sum of all points
    int result {0};
    for (int i = 0; i < winningNumbers.size(); i++)
    {
        result += PointsOfTicket(winningNumbers[i], userNumbers[i]);
    }

    std::cout << "The result is: " << result << '\n';

    return 0;
}