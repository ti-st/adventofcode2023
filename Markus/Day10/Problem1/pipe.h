#ifndef PIPE_H
#define PIPE_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

enum Tile {VERTICAL, HORIZONTAL, BEND_NE, BEND_NW, BEND_SW, BEND_SE, GROUND, START};
enum Direction {NORTH, EAST, SOUTH, WEST};

struct Pipe
{
    static std::vector<std::pair<Tile,std::pair<Direction,Direction>>> validDirections;
    static std::vector<std::pair<Direction,Direction>> oppositeDirections;
    Tile pipeType;

    // Constructor
    Pipe(Tile pipeType) : pipeType{pipeType} {}

    // Get valid directions for this pipe
    std::pair<Direction,Direction> GetValidDirections();

    // Get next direction
    Direction GetNextDirection(Direction currentDirection);
    
};

#endif // PIPE_H
