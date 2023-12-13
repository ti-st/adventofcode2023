#include "pipe.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <numbers>

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

// Function that runs the loop and returns vector of coordinates of visited tiles in order
std::vector<std::pair<int,int>> GetLoop (const std::vector<std::vector<Tile>>& matrix, std::pair<int,int> startCoord, Direction startDirection)
{
    // Initialize return vector of coordinates of visited tiles in order
    std::vector<std::pair<int,int>> returnVector;
    
    // Coordinates of current position
    std::pair<int,int> currentCoord {startCoord};

    // Direction of current position
    Direction currentDirection {startDirection};

    // Add start to return vector
    returnVector.push_back(currentCoord);

    // Loop until we reach the end
    while (true)
    {
        // Check if we have reached the end (start tile) at next tile
        if (GetNextCoord(currentCoord,currentDirection) == startCoord)
        {
            // Append start of loop to return vector to close the loop
            returnVector.push_back(startCoord);
            return returnVector;
        }

        // Move to next tile
        currentCoord = GetNextCoord(currentCoord,currentDirection);
        // Feed current direction into GetNextDirection of next tile
        currentDirection = TurnTileToPipe(matrix[currentCoord.first][currentCoord.second]).GetNextDirection(currentDirection);
        // Add current tile to return vector
        returnVector.push_back(currentCoord);
    }
}

// Function that takes output of GetLoop and returns matrix of loop
std::vector<std::vector<int>> GetLoopMatrix (const std::vector<std::vector<Tile>>& matrix, const std::vector<std::pair<int,int>>& loop)
{
    // Initialize return matrix
    std::vector<std::vector<int>> returnMatrix(matrix.size(),std::vector<int>(matrix[0].size(),0));

    // Fill return matrix with loop
    for (auto coord : loop)
    {
        returnMatrix[coord.first][coord.second] = 1;
    }

    return returnMatrix;
}

// Function that calculates coordinates of coord relative to given origin
std::pair<int,int> GetRelativeCoord (std::pair<int,int> origin, std::pair<int,int> coord)
{
    return {coord.first-origin.first,coord.second-origin.second};
}

// Function that calculates signed angle difference between two angles
double signedAngle(double phi1, double phi2)
{
    // Calculate signed angle difference (add 2*pi if negative)
    // The number std::numbers::pi needs C++20, compile with -std=c++20
    double phiDiff {phi2-phi1};
    if (phiDiff < -std::numbers::pi)
    {
        phiDiff += 2*std::numbers::pi;
    }
    else if (phiDiff > std::numbers::pi)
    {
        phiDiff -= 2*std::numbers::pi;
    }
    return phiDiff;
}

// Function that, given an input coordinate, returns the winding number with respect to a loop
int GetWindingNumber (const std::vector<std::pair<int,int>>& loop, std::pair<int,int> inputCoord)
{
    // Get coordinates of start of loop
    std::pair<int,int> startCoord {loop[0]};

    // Initialize relative coordinates
    std::pair<int,int> coordRelative1 {0,0};
    std::pair<int,int> coordRelative2 {GetRelativeCoord(inputCoord,startCoord)};

    // Calculate relative angle between input coordinate and start coordinate using atan2
    double startPhi {atan2(coordRelative2.first,coordRelative2.second)};

    // Initialize angle variables
    double phi1 {0};
    double phi2 {startPhi};

    // initialize variable holding angle as a function of loop step
    double runningPhi {0};

    // Loop through loop (hehe)
    for (int i = 1; i < loop.size(); ++i)
    {
        // Update relative coordinates
        coordRelative1 = coordRelative2;
        coordRelative2 = GetRelativeCoord(inputCoord,loop[i]);
        // Update angles
        phi1 = phi2;
        phi2 = atan2(coordRelative2.first,coordRelative2.second);

        // Update running angle
        runningPhi += signedAngle(phi1,phi2);
    }

    // Calculate winding number (I really hope there are no finite-precision shenanigans here)
    // dont forget to round!!!
    int windingNumber {static_cast<int>(round(runningPhi/(2*std::numbers::pi)))};

    return windingNumber;
}

// Function that prints matrix to file
void PrintMatrixToFile (std::vector<std::vector<int>> matrix, std::string fileName)
{
    std::ofstream outputFile;
    outputFile.open(fileName,std::ios_base::out);
    if (!outputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[0].size(); ++j)
        {
            outputFile << matrix[i][j];
        }
        outputFile << "\n";
    }
    outputFile.close();
}

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_10_input.txt",std::ios_base::in);
    //inputFile.open("test_input.txt",std::ios_base::in);
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

    // Build Loop
    std::vector<std::pair<int,int>> loop = GetLoop(matrix,startCoord,SOUTH);

    // Create loop matrix
    std::vector<std::vector<int>> loopMatrix = GetLoopMatrix(matrix,loop);

    // For visualizing loop matrix, write it to file "loop_matrix.txt"
    PrintMatrixToFile(loopMatrix,"loop_matrix.txt");
    
    // Number of tiles with nonzero winding number
    int numberOfTilesWithNonzeroWindingNumber {0};

    // Loop over all tiles not visited by the loop (marked with zero in loop matrix)
    for (int i = 0; i < loopMatrix.size(); ++i)
    {
        for (int j = 0; j < loopMatrix[0].size(); ++j)
        {
            if (loopMatrix[i][j] == 0)
            {
                // Get winding number of tile
                int windingNumber {GetWindingNumber(loop,{i,j})};
                // If winding number is nonzero, increment counter
                if (windingNumber != 0) {++numberOfTilesWithNonzeroWindingNumber;}
            }
        }
    }

    // Print number of tiles with nonzero winding number
    std::cout << "Number of tiles with nonzero winding number: " << numberOfTilesWithNonzeroWindingNumber << "\n";

    // Close input file
    inputFile.close();

    return 0;
}
