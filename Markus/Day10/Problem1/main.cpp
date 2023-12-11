#include "pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

Tile AsciiToTile(char ch)
{
    switch (ch)
    {
        case '|':
            return VERTICAL;
        case '-':
            return HORIZONTAL;
        case 'L':
            return BEND_NE;
        case 'J':
            return BEND_NW;
        case '7':
            return BEND_SW;
        case 'F':
            return BEND_SE;
        case '.':
            return GROUND;
        case 'S':
            return START;
        default:
            std::cout << "Invalid ascii character: " << ch << "\n";
            exit(1);
    }
}

Pipe TurnTileToPipe (Tile tile)
{
    switch (tile)
    {
        case VERTICAL:
            return Pipe(VERTICAL);
        case HORIZONTAL:
            return Pipe(HORIZONTAL);
        case BEND_NE:
            return Pipe(BEND_NE);
        case BEND_NW:
            return Pipe(BEND_NW);
        case BEND_SW:
            return Pipe(BEND_SW);
        case BEND_SE:
            return Pipe(BEND_SE);
        case GROUND:
            return Pipe(GROUND);
        case START:
            return Pipe(START);
        default:
            std::cout << "Invalid tile type: " << tile << "\n";
            exit(1);
    }
}

std::pair<int,int> GetNextCoord (std::pair<int,int> currentCoord, Direction currentDirection)
{
    switch (currentDirection)
    {
        case NORTH:
            return {currentCoord.first-1,currentCoord.second};
        case EAST:
            return {currentCoord.first,currentCoord.second+1};
        case SOUTH:
            return {currentCoord.first+1,currentCoord.second};
        case WEST:
            return {currentCoord.first,currentCoord.second-1};
        default:
            std::cout << "Invalid current direction (GetNextCoord): " << currentDirection << "\n";
            exit(1);
    }
}

long RunLoop (std::vector<std::vector<Tile>> matrix, std::pair<int,int> startCoord, Direction startDirection)
{
    // Coordinates of current position
    std::pair<int,int> currentCoord {startCoord};

    // Direction of current position
    Direction currentDirection {startDirection};

    // Number of steps taken
    long steps {0};

    // Loop until we reach the end
    while (true)
    {
        // Check if we have reached the end (start tile) at next tile
        if (GetNextCoord(currentCoord,currentDirection) == startCoord && steps != 0)
        {
            return steps + 1;
        }

        // Move to next tile
        currentCoord = GetNextCoord(currentCoord,currentDirection);
        // Feed current direction into GetNextDirection of next tile
        currentDirection = TurnTileToPipe(matrix[currentCoord.first][currentCoord.second]).GetNextDirection(currentDirection);
        // Increment steps
        ++steps;
    }
}

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_10_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }

    // Coordinates (row,column) of Start
    std::pair<int,int> startCoord;

    // Read input file into matrix (vector of vectors)
    std::vector<std::vector<Tile>> matrix;
    std::string line;
    int rowCounter {0};
    while (std::getline(inputFile,line))
    {
        std::vector<Tile> row;
        for (int i = 0; i < line.size(); ++i)
        {
            row.push_back(AsciiToTile(line[i]));
            if (line[i] == 'S')
            {
                startCoord.first = rowCounter;
                startCoord.second = i;
            }
        }
        matrix.push_back(row);
        ++rowCounter;
    }

    // Print coordinates of Start
    std::cout << "Start coordinates: (" << startCoord.first << "," << startCoord.second << ")\n";

    // Run loop from startCoord
    /* COMMENT: By inspecting the input file, we see that only NORTH and SOUTH are valid directions for the start tile.
                Since there are no pipes that connect more than two tiles, we can assume that the NORTH and SOUTH pipes
                are end and start pipes of the one loop that contains the start tile. So just take any one of them and
                you get the result. */
    std::cout << "Number of steps: " << RunLoop(matrix,startCoord,NORTH) / 2 << "\n";
    //std::cout << "Number of steps: " << RunLoop(matrix,startCoord,SOUTH) / 2 << "\n";
    //std::cout << "Number of steps: " << RunLoop(matrix,startCoord,EAST) / 2 << "\n";
    //std::cout << "Number of steps: " << RunLoop(matrix,startCoord,WEST) / 2 << "\n";

    // Close input file
    inputFile.close();

    return 0;
}
