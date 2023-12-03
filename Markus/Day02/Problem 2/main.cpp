#include<iostream>
#include<fstream>
#include<string>

struct GameData
{
    int nRed {};
    int nGreen {};
    int nBlue {};
    int power() {return nRed*nGreen*nBlue;}
};

inline bool IsNumber(char ch) {return (ch>47)&&(ch<58);}
inline int ConvertToNumber(char ch) {return ch-48;}

int RecordMinimumGamePower(const std::string& line)
{
    GameData minimumGame {0,0,0};

    for (std::string::size_type i = 0; i < line.size(); i++)
    {
        if (IsNumber(line[i]) && line[i+2] == 'r')
        {
            int temp {(IsNumber(line[i-1]) ? ConvertToNumber(line[i-1]) : 0 )*10 + ConvertToNumber(line[i])};
            if (temp > minimumGame.nRed) {minimumGame.nRed = temp;}
        }
        else if (IsNumber(line[i]) && line[i+2] == 'g')
        {
            int temp {(IsNumber(line[i-1]) ? ConvertToNumber(line[i-1]) : 0 )*10 + ConvertToNumber(line[i])};
            if (temp > minimumGame.nGreen) {minimumGame.nGreen = temp;}
        }
        else if (IsNumber(line[i]) && line[i+2] == 'b')
        {
            int temp {(IsNumber(line[i-1]) ? ConvertToNumber(line[i-1]) : 0 )*10 + ConvertToNumber(line[i])};
            if (temp > minimumGame.nBlue) {minimumGame.nBlue = temp;}
        }
    }

    return minimumGame.power();
}

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_2_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }

    int buffer {0};
    std::string dummyLine {};
    while (std::getline(inputFile, dummyLine))
    {
        buffer += RecordMinimumGamePower(dummyLine);
    }

    std::cout << "The result is: " << buffer << '\n';

    return 0;
}