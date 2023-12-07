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

inline int DistanceTravelled(int timePressed, int timeRace) {return (timeRace - timePressed) * timePressed;}

int NumberOfWaysToBeat(int distanceToBeat, int timeRace)
{
    int counter {0};
    for (int timePressed = 1; timePressed < timeRace; timePressed++)
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
    std::cout << "File opened successfully!\n";

    // Vectors containing the time of the race and the distance to beat
    std::vector<int> timeVec;
    std::vector<int> distanceVec;

    // Read in time and distance data from input file
    std::vector<std::string> inputVec;
    std::string line;
    while (std::getline(inputFile, line))
    {
        inputVec.push_back(line);
    }

    for (int i = 0; i < inputVec[0].size(); i++)
    {
        if (IsNumber(inputVec[0][i]) && (i+1 == inputVec[0].size() || !IsNumber(inputVec[0][i+1])))
        {
            timeVec.push_back(ReadNumber(inputVec[0], i));
        }
        if (IsNumber(inputVec[1][i]) && (i+1 == inputVec[1].size() || !IsNumber(inputVec[1][i+1])))
        {
            distanceVec.push_back(ReadNumber(inputVec[1], i));
        }
    }

    // Calculate how many combinations there are to beat all records
    int totalNumberOfWaysToBeat {1};
    for (int i = 0; i < timeVec.size(); i++)
    {
        totalNumberOfWaysToBeat *= NumberOfWaysToBeat(distanceVec[i], timeVec[i]);
    }

    std::cout << "Total number of ways to beat all records: " << totalNumberOfWaysToBeat << "\n";

    return 0;
}


