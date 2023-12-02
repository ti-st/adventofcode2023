#include<iostream>
#include<fstream>
#include<string>
#include<vector>

struct GameData
{
    int nRed {};
    int nGreen {};
    int nBlue {};
    bool IsPossible() {return nRed<=12 && nGreen<=13 && nBlue<=14;}
};

inline bool IsNumber(char ch) {return (ch>47)&&(ch<58);}
inline int ConvertToNumber(char ch) {return ch-48;}

bool LineIsPossible(const std::string& line)
{
    bool isPossible {true};
    GameData dummyData {0,0,0};

    for (std::string::size_type i = 0; i < line.size(); i++)
    {
        if (line[i]==';') {dummyData = {0,0,0};} // reset dummyData
        else if (IsNumber(line[i]) && line[i+2] == 'r')
        {
            dummyData.nRed = (IsNumber(line[i-1]) ? ConvertToNumber(line[i-1]) : 0 )*10 + ConvertToNumber(line[i]);
        }
        else if (IsNumber(line[i]) && line[i+2] == 'g')
        {
            dummyData.nGreen = (IsNumber(line[i-1]) ? ConvertToNumber(line[i-1]) : 0 )*10 + ConvertToNumber(line[i]);
        }
        else if (IsNumber(line[i]) && line[i+2] == 'b')
        {
            dummyData.nBlue = (IsNumber(line[i-1]) ? ConvertToNumber(line[i-1]) : 0 )*10 + ConvertToNumber(line[i]);
        }

        if (!dummyData.IsPossible()) {isPossible = false;}
    }

    return isPossible;
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
    int counterId {0};
    std::string dummyLine {};
    while (std::getline(inputFile, dummyLine))
    {
        counterId++;
        if (LineIsPossible(dummyLine)) {buffer += counterId;}
    }

    std::cout << "The result is: " << buffer << '\n';

    return 0;
}