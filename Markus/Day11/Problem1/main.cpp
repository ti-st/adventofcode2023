#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <numbers>
#include <numeric>

// Function that returns vector of vectors containing indices of rows and columns that do not contain a galaxy
// first vector of output contains indices of empty rows
// second vector of output contains indices of empty columns
std::vector<std::vector<int>> findEmptyRowsAndColumns(const std::vector<std::string>& galaxyMap)
{
    std::vector<std::vector<int>> emptyRowsAndColumns;
    std::vector<int> emptyRows;
    std::vector<int> emptyColumns;

    // Check rows
    for (int i = 0; i < galaxyMap.size(); i++)
    {
        bool emptyRow {true};
        for (int j = 0; j < galaxyMap[i].size(); j++)
        {
            if (galaxyMap[i][j] == '#')
            {
                emptyRow = false;
                break;
            }
        }
        if (emptyRow)
        {
            emptyRows.push_back(i);
        }
    }

    // Check columns
    for (int i = 0; i < galaxyMap[0].size(); i++)
    {
        bool emptyColumn = true;
        for (int j = 0; j < galaxyMap.size(); j++)
        {
            if (galaxyMap[j][i] == '#')
            {
                emptyColumn = false;
                break;
            }
        }
        if (emptyColumn)
        {
            emptyColumns.push_back(i);
        }
    }

    emptyRowsAndColumns.push_back(emptyRows);
    emptyRowsAndColumns.push_back(emptyColumns);

    return emptyRowsAndColumns;
}

// Function that returns coordinates of galaxies in the galaxy map
std::vector<std::pair<int,int>> findGalaxies(const std::vector<std::string>& galaxyMap)
{
    std::vector<std::pair<int,int>> galaxyCoordinates;

    for (int i = 0; i < galaxyMap.size(); i++)
    {
        for (int j = 0; j < galaxyMap[i].size(); j++)
        {
            if (galaxyMap[i][j] == '#')
            {
                galaxyCoordinates.push_back(std::make_pair(i,j));
            }
        }
    }

    return galaxyCoordinates;
}

// Function that expands universe:
// For all empty columns, shift all galaxies to the right of this column to the right by one step
// For all empty rows, shift all galaxies below this row down by one step
std::vector<std::pair<int,int>> expandUniverse(const std::vector<std::pair<int,int>>& galaxyCoordinates, const std::vector<std::vector<int>>& emptyRowsAndColumns)
{
    // Initialize output vector
    std::vector<std::pair<int,int>> expandedGalaxyCoordinates {galaxyCoordinates};

    // Shift galaxies to the right
    for (int i = 0; i < emptyRowsAndColumns[1].size(); i++)
    {
        for (int j = 0; j < galaxyCoordinates.size(); j++)
        {
            if (galaxyCoordinates[j].second > emptyRowsAndColumns[1][i])
            {
                expandedGalaxyCoordinates[j].second++;
            }
        }
    }

    // Shift galaxies down
    for (int i = 0; i < emptyRowsAndColumns[0].size(); i++)
    {
        for (int j = 0; j < galaxyCoordinates.size(); j++)
        {
            if (galaxyCoordinates[j].first > emptyRowsAndColumns[0][i])
            {
                expandedGalaxyCoordinates[j].first++;
            }
        }
    }

    return expandedGalaxyCoordinates;
}

// Function that returns Manhattan distance between two points
int manhattanDistance(const std::pair<int,int>& point1, const std::pair<int,int>& point2)
{
    return std::abs(point1.first - point2.first) + std::abs(point1.second - point2.second);
}

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_11_input.txt",std::ios_base::in);
    //inputFile.open("test_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }

    // Read input file into vector of strings
    std::vector<std::string> galaxyMap;
    std::string line;
    while (std::getline(inputFile, line))
    {
        galaxyMap.push_back(line);
    }

    // Find empty rows and columns
    std::vector<std::vector<int>> emptyRowsAndColumns {findEmptyRowsAndColumns(galaxyMap)};
    // Find coordinates of galaxies
    std::vector<std::pair<int,int>> galaxyCoordinates {findGalaxies(galaxyMap)};

    // Expand universe
    std::vector<std::pair<int,int>> expandedGalaxyCoordinates {expandUniverse(galaxyCoordinates, emptyRowsAndColumns)};

    // Initialize total distance
    int totalDistance {0};

    // Find distances between all pairs of galaxies
    for (int i = 0; i < expandedGalaxyCoordinates.size(); i++)
    {
        for (int j = i+1; j < expandedGalaxyCoordinates.size(); j++)
        {
            totalDistance += manhattanDistance(expandedGalaxyCoordinates[i], expandedGalaxyCoordinates[j]);
        }
    }

    // Print sum of distances
    std::cout << "Sum of distances: " << totalDistance << "\n";

    // Close input file
    inputFile.close();

    return 0;
}
