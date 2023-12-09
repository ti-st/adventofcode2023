#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

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

    // Read in instructions from first line of input file
    std::string instructions;
    std::getline(inputFile, instructions);

    // Map that contians key = node and value = pair of nodes
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodeTripleMap;
    // Vector that contains string triples from input line
    std::vector<std::string> nodeVec;
    std::string line;
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
        if (instructions[i] == 'R')
        {
            currentNode = nodeTripleMap[currentNode].second;
        }
        else if (instructions[i] == 'L')
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
