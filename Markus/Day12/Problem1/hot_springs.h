#ifndef HOT_SPRINGS_H
#define HOT_SPRINGS_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <numbers>
#include <numeric>

// Include function declarations of functions before main
int IntPower(int x, unsigned int p);
int ReadNumber(const std::string& line, int i);

enum SpringState {OPERATIONAL, DAMAGED, UNKNOWN};

struct SpringRow
{
    std::vector<SpringState> row;
    std::vector<int> groupsOfDamagedSprings;

    // Standard constructor
    SpringRow(std::vector<SpringState> row, std::vector<int> groupsOfDamagedSprings) : row(row), groupsOfDamagedSprings(groupsOfDamagedSprings) {}

    // Constructor, taking string as input
    SpringRow(const std::string& line);

    // Method that checks whether row is valid
    bool IsValid() const;

    // Method that yields positions of UNKNOWN springs
    std::vector<int> GetUnknownSpringPositions() const;

    // Method that calculates number of valid spring configurations
    int NumberOfValidSpringConfigurations() const;

};

#endif // HOT_SPRINGS_H
