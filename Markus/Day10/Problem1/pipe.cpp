#include "pipe.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

// Valid directions for each pipe type
std::vector<std::pair<Tile,std::pair<Direction,Direction>>> Pipe::validDirections {
    {VERTICAL, {NORTH, SOUTH}},
    {HORIZONTAL, {EAST, WEST}},
    {BEND_NE, {NORTH, EAST}},
    {BEND_NW, {NORTH, WEST}},
    {BEND_SW, {SOUTH, WEST}},
    {BEND_SE, {SOUTH, EAST}}
};

// Opposite directions for each pipe type
std::vector<std::pair<Direction,Direction>> Pipe::oppositeDirections {
    {NORTH, SOUTH},
    {EAST, WEST},
    {SOUTH, NORTH},
    {WEST, EAST}
};

// Get valid directions for this pipe
std::pair<Direction,Direction> Pipe::GetValidDirections()
{
    for (auto validDirection : validDirections)
    {
        if (validDirection.first == pipeType)
        {
            return validDirection.second;
        }
    }
    std::cout << "Invalid pipe type: " << pipeType << "\n";
    exit(1);
}

// Get next direction
Direction Pipe::GetNextDirection(Direction currentDirection)
{
    // If opposite direction of current direction is a valid direction for this pipe type, return the other valid direction
    for (auto oppositeDirection : oppositeDirections)
    {
        if (oppositeDirection.first == currentDirection)
        {
            for (auto validDirection : validDirections)
            {
                if (validDirection.first == pipeType)
                {
                    if (validDirection.second.first == oppositeDirection.second)
                    {
                        return validDirection.second.second;
                    }
                    else if (validDirection.second.second == oppositeDirection.second)
                    {
                        return validDirection.second.first;
                    }
                }
            }
        }
    }
    std::cout << "Invalid current direction (GetNextDirection): " << currentDirection << "\n";
    exit(1);
}