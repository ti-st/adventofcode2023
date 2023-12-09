#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

enum InstructionType {RIGHT, LEFT};

// Function that reads in vector of navigation instructions from string
std::vector<InstructionType> ReadInstructions(const std::string& line)
{
    std::vector<InstructionType> instructions;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == 'R') {instructions.push_back(RIGHT);}
        else if (line[i] == 'L') {instructions.push_back(LEFT);}
    }
    return instructions;
}

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_8_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }
    std::cout << "File opened successfully!\n";

    // Read in instruction vector from first line of input file
    std::string line;
    std::getline(inputFile, line);
    std::vector<InstructionType> instructions {ReadInstructions(line)};

    // Map that contians key = node and value = pair of nodes
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodeTripleMap;
    // Vector that contains string triples from input line
    std::vector<std::string> nodeVec;
    while (std::getline(inputFile, line))
    {
        if (line.size() == 0) {continue;}
        nodeVec.push_back(line.substr(0, 3));
        nodeVec.push_back(line.substr(7, 3));
        nodeVec.push_back(line.substr(12, 3));
 
        nodeTripleMap[nodeVec[0]] = std::make_pair(nodeVec[1], nodeVec[2]);

        nodeVec.clear();
    }

    // Start at node AAA
    std::string startingNode {"AAA"};
    std::string currentNode {startingNode};

    // loop counter
    int counter {0};
    // index for instructions vector
    int i {0};

    // Repeatedly loop over instructions
    while (true)
    {
        if (instructions[i] == RIGHT)
        {
            currentNode = nodeTripleMap[currentNode].second;
        }
        else if (instructions[i] == LEFT)
        {
            currentNode = nodeTripleMap[currentNode].first;
        }

        if (i == instructions.size()-1) {i = 0;}
        else {i++;}
        
        counter++;

        if (currentNode == "ZZZ") {break;}
    }
    
    // Print currentNode and counter
    std::cout << "Current node (safety check): " << currentNode << "\n";
    std::cout << "Counter: " << counter << "\n";

    // Close input file
    inputFile.close();

    return 0;
}
