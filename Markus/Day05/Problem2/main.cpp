#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<numeric>

inline bool IsNumber(char ch) {return (ch>47)&&(ch<58);}
inline int ConvertToNumber(char ch) {return ch-48;}

unsigned long long IntPower(int x, unsigned int p)
{
    if (p == 0) {return 1;}
    if (p == 1) {return x;}
    
    int tmp = IntPower(x, p/2);
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

struct MapTriple
{
    unsigned long long destinationRangeStart {0};
    unsigned long long sourceRangeStart {0};
    unsigned long long rangeLength {0};
};

// Bijection between source and destination
/* unsigned long long MapSourceToDestination(unsigned long long sourceID, const std::vector<MapTriple>& mapVec)
{
    if (mapVec.size() != 0)
    {
        for (auto map : mapVec)
        {
            if (sourceID >= map.sourceRangeStart && sourceID < map.sourceRangeStart + map.rangeLength)
            {
                return sourceID - map.sourceRangeStart + map.destinationRangeStart;
            }
        }
    }

    return sourceID;
} */

// Inverse of MapSourceToDestination
unsigned long long MapDestinationToSource(unsigned long long destinationID, const std::vector<MapTriple>& mapVec)
{
    if (mapVec.size() != 0)
    {
        for (auto map : mapVec)
        {
            if (destinationID >= map.destinationRangeStart && destinationID < map.destinationRangeStart + map.rangeLength)
            {
                return destinationID - map.destinationRangeStart + map.sourceRangeStart;
            }
        }
    }

    return destinationID;
}

unsigned long long FindLowestLocationNumber(const std::vector<unsigned long long>& seedIDRange, const std::vector<std::string>& inputLines, unsigned long long lowestLocationStart = 0)
{
    // Create a vector to store mapping information
    std::vector<MapTriple> mapVec;

    // Create a temporary vector to store values read from each line
    std::vector<unsigned long long> tmpVec;

    // Create a temporary MapTriple object to store the mapping information for each line
    MapTriple tmpMap;

    // Flag to indicate if we have passed the block of mapping information
    bool pastBlockFlag {false};

    // Variable to store the lowest location number
    unsigned long long lowestLocation {lowestLocationStart};
    unsigned long long lowestLocationMapped {lowestLocationStart};

    // Vector that contains all distinct maps
    std::vector<std::vector<MapTriple>> mapVecVec;

    // Read each line from the input file but in reverse order
    for (int i = inputLines.size()-1; i >= 0; i--)
    {
        // Check if the line starts with a number
        if (IsNumber(inputLines[i][0]))
        {
            pastBlockFlag = false;
            tmpVec.clear();

            // Extract numbers from the line and store them in tmpVec
            for (int j = 0; j < inputLines[i].size(); j++)
            {
                if (IsNumber(inputLines[i][j]) && (j+1 == inputLines[i].size() || !IsNumber(inputLines[i][j+1])))
                {
                        tmpVec.push_back(ReadNumber(inputLines[i], j));
                }
            }

            // Check if the size of tmpVec is not equal to 3
            if (tmpVec.size() != 3)
            {
                std::cout << "Error: tmpVec.size() != 3\n";
                exit(1);
            }

            // Assign values from tmpVec to tmpMap
            tmpMap.destinationRangeStart = tmpVec[0];
            tmpMap.sourceRangeStart = tmpVec[1];
            tmpMap.rangeLength = tmpVec[2];

            // Add tmpMap to the mapVec
            mapVec.push_back(tmpMap);
        }
        else if (!pastBlockFlag)
        {
            mapVecVec.push_back(mapVec);
            mapVec.clear();
            pastBlockFlag = true;
        }
    }

    if (mapVecVec.size() != 7)
    {
        std::cout << "Error: mapVecVec.size() != 7\n";
        exit(1);
    }

    // Loop diagnostics
    unsigned long long loopCounter {0};
    double percent {0.0};

    while (true)
    {
        loopCounter++;

        // Apply mappings
        for (auto& mapVec : mapVecVec)
        {
            lowestLocationMapped = MapDestinationToSource(lowestLocationMapped, mapVec);
        }
        
        // Check if we hit a seed
        for (int j = 0; j < seedIDRange.size(); j+=2)
        {
            if (lowestLocationMapped >= seedIDRange[j] && lowestLocationMapped <= seedIDRange[j] + seedIDRange[j+1])
            {
                return lowestLocation;
            }
        }

        // Print percentage until definite hit every 10000000 iterations (825516882 is known result from part 1)
        percent = (double)loopCounter / (double)825516882ULL * 100.0;
        if (loopCounter % 10000000 == 0) {
            std::cout << "Percent until definite hit: " << percent << std::endl;
        }

        // If we didn't hit a seed, increment lowestLocation
        lowestLocation++;
        lowestLocationMapped = lowestLocation;
    }

    return lowestLocation;
}   

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_5_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }

    // Read in seed ID ranges
    std::vector<unsigned long long> seedIDRange;
    std::string line;
    std::getline(inputFile, line);
    for (int i = 0; i < line.size(); i++)
    {
        if (IsNumber(line[i]) && (i+1 == line.size() || !IsNumber(line[i+1])))
        {
            seedIDRange.push_back(ReadNumber(line, i));
        }
    }
    // Check whether seedIDRange has an even number of elements
    if (seedIDRange.size() % 2 != 0)
    {
        std::cout << "Error: seedIDRange.size() is not even\n";
        exit(1);
    }

    // Read file into vector of strings
    std::vector<std::string> inputLines;
    while (std::getline(inputFile, line))
    {
        inputLines.push_back(line);
    }

    // Find the lowest location number
    unsigned long long lowestLocation {FindLowestLocationNumber(seedIDRange, inputLines)};

    std::cout << "The lowest location number is: " << lowestLocation << std::endl;

    inputFile.close();
    
    return 0;
}


