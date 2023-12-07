#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

inline bool IsNumber(char ch) {return (ch>47)&&(ch<58);}
inline int ConvertToNumber(char ch) {return ch-48;}

unsigned long long IntPower(int x, unsigned int p)
{
    if (p == 0) {return 1;}
    if (p == 1) {return x;}
    
    unsigned long long tmp = IntPower(x, p/2);
    if (p%2 == 0) {return tmp * tmp;}
    else {return x * tmp * tmp;}
}

unsigned long long ReadNumber(const std::string& line, int i, int counter = 0)
{
    unsigned long long tmp {0};
    if (i>0 && IsNumber(line[i-1]))
    {
        tmp = ReadNumber(line, i-1) * IntPower(10, counter+1);
    }
    return tmp + ConvertToNumber(line[i]) * IntPower(10, counter);
}

inline unsigned long long DistanceTravelled(unsigned long long timePressed, unsigned long long timeRace) {return (timeRace - timePressed) * timePressed;}

unsigned long long NumberOfWaysToBeat(unsigned long long distanceToBeat, unsigned long long timeRace)
{
    unsigned long long counter {0};
    for (unsigned long long timePressed = 1; timePressed < timeRace; timePressed++)
    {
        if (DistanceTravelled(timePressed, timeRace) > distanceToBeat)
        {
            counter++;
        }
    }
    return counter;
}

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_6_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }

    // Read in time and distance data from input file
    std::vector<std::string> inputVec;
    std::string line;
    while (std::getline(inputFile, line))
    {
        inputVec.push_back(line);
    }

    // Remove spaces from strings
    inputVec[0].erase(std::remove(inputVec[0].begin(), inputVec[0].end(), ' '), inputVec[0].end());
    inputVec[1].erase(std::remove(inputVec[1].begin(), inputVec[1].end(), ' '), inputVec[1].end());

    // time of the race and the distance to beat
    unsigned long long timeRace {ReadNumber(inputVec[0], inputVec[0].size()-1)};
    unsigned long long distanceToBeat {ReadNumber(inputVec[1], inputVec[1].size()-1)};

    // Calculate how many combinations there are to beat all records
    unsigned long long totalNumberOfWaysToBeat {NumberOfWaysToBeat(distanceToBeat, timeRace)};

    std::cout << "Total number of ways to beat all records: " << totalNumberOfWaysToBeat << "\n";

    return 0;
}


