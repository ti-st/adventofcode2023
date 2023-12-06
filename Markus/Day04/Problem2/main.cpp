#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
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

    std::vector<int> result;
    for (int i = offset; i < line.size(); i++)
    {
        if (IsNumber(line[i]) && line[i+1]==' ')
        {
            result.push_back(ReadNumber(line, i));
        }
        if (line[i+2] == '|')
        {
            break; // No need to continue parsing after encountering '|' character
        }
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
        if (IsNumber(line[i]) && (i+1==line.size() || line[i+1]==' '))
        {
            result.push_back(ReadNumber(line, i));
        }
    }

    return result;
}

int NumberOfMatches(const std::vector<int>& winningNumbers, const std::vector<int>& userNumbers)
{
    int number {0};
    for (auto winN : winningNumbers)
    {
        number += std::count(userNumbers.begin(), userNumbers.end(), winN);
    }
 
    return number;
}

std::vector<int> ScratchcardNumbers(const std::vector<std::vector<int>>& winningNumbers, const std::vector<std::vector<int>>& userNumbers, int totalCards)
{
    // Vector that contains number of each scratchcard (initially all with 1 copy each)
    std::vector<int> scratchcardNumbers(totalCards,1);
    int numberMatchesTicket {};
    for (int i = 0; i < totalCards; i++)
    {
        numberMatchesTicket = NumberOfMatches(winningNumbers[i], userNumbers[i]);
        for (int j = 1; j <= std::min(numberMatchesTicket, totalCards-i-1); j++)
        {
            scratchcardNumbers[i+j] += scratchcardNumbers[i];
        }
    }

    return scratchcardNumbers;
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

    // Read winning and user numbers
    std::string dummyLine {};
    int counter {0};
    std::vector<std::vector<int>> winningNumbers;
    std::vector<std::vector<int>> userNumbers;
    while (std::getline(inputFile, dummyLine))
    {
        winningNumbers.push_back(ReadWinningNumbers(dummyLine));
        userNumbers.push_back(ReadUserNumbers(dummyLine));
        counter++;
    }

    // Total number of scratchcards
    int totalCards {197};
    // Calculate number of each scratchcard
    std::vector<int> resultVec {ScratchcardNumbers(winningNumbers, userNumbers, totalCards)};

    std::cout << "The total number of cards is: " << std::accumulate(resultVec.begin(), resultVec.end(), 0) << std::endl;

    return 0;
}