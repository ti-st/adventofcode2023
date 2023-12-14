#include "hot_springs.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <numbers>
#include <numeric>

// Function that reads in block of damaged springs from right
int ReadNumberofDamagedSprings(const std::vector<SpringState>& line, int i, int counter = 0)
{
    int number {0};
    if (i > 0 && line[i-1] == DAMAGED)
    {
        number = ReadNumberofDamagedSprings(line, i-1, counter+1);
    }
    return number + 1;
}

// Constructor, taking string as input
SpringRow::SpringRow(const std::string& line)
{
    // Read in SpringStates
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == '.') {row.push_back(OPERATIONAL);}
        else if (line[i] == '#') {row.push_back(DAMAGED);}
        else if (line[i] == '?') {row.push_back(UNKNOWN);}
    }

    // Read in number of elements in contiguous groups of damaged springs
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ' ' || line[i] == ',')
        {
            groupsOfDamagedSprings.push_back(ReadNumber(line, i));
        }
    }
}

// Method that checks whether row is valid
bool SpringRow::IsValid() const
{
    // Check whether number of damaged springs is correct
    int numberOfDamagedSprings {0};
    for (auto state : row)
    {
        if (state == DAMAGED) {numberOfDamagedSprings++;}
    }
    if (numberOfDamagedSprings != std::accumulate(groupsOfDamagedSprings.begin(), groupsOfDamagedSprings.end(), 0))
    {
        return false;
    }

    // Iterate over row and check whether groups of damaged springs are correct
    int counter {0};
    for (int i = 0; i < row.size(); i++)
    {
        if (counter == groupsOfDamagedSprings.size() && row[i] == DAMAGED)
        {
            return false;
        }
        else if ( row[i] == DAMAGED && (i+1 == row.size() || row[i+1] != DAMAGED))
        {
            int numberOfDamagedSpringsInGroup {ReadNumberofDamagedSprings(row, i)};
            if (numberOfDamagedSpringsInGroup != groupsOfDamagedSprings[counter])
            {
                return false;
            }
            counter++;
        }
    }

    return true;
};

// Method that yields positions of UNKNOWN springs
std::vector<int> SpringRow::GetUnknownSpringPositions() const
{
    std::vector<int> unknownSpringPositions;
    for (int i = 0; i < row.size(); i++)
    {
        if (row[i] == UNKNOWN) {unknownSpringPositions.push_back(i);}
    }
    return unknownSpringPositions;
}

// Method that calculates number of valid spring configurations
int SpringRow::NumberOfValidSpringConfigurations() const
{
    // Get positions of unknown springs
    std::vector<int> unknownSpringPositions {GetUnknownSpringPositions()};

    // Calculate number of valid spring configurations
    int numberOfValidSpringConfigurations {0};
    for (int i = 0; i < IntPower(2, unknownSpringPositions.size()); i++)
    {
        // Convert i to binary
        std::vector<int> binary;
        int tmp {i};
        while (tmp > 0)
        {
            binary.push_back(tmp%2);
            tmp /= 2;
        }
        while (binary.size() < unknownSpringPositions.size())
        {
            binary.push_back(0);
        }

        // Create new row
        std::vector<SpringState> newRow {row};
        for (int j = 0; j < unknownSpringPositions.size(); j++)
        {
            if (binary[j] == 0) {newRow[unknownSpringPositions[j]] = OPERATIONAL;}
            else {newRow[unknownSpringPositions[j]] = DAMAGED;}
        }

        // Check whether new row is valid
        SpringRow newSpringRow = {newRow, groupsOfDamagedSprings};
        if (newSpringRow.IsValid()) {numberOfValidSpringConfigurations++;}
    }

    return numberOfValidSpringConfigurations;
}