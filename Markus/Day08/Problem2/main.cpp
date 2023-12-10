#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

// enum Instruction {LEFT = -1, STANDBY = 0, RIGHT = 1};

struct Cycle
{
    std::string startingNode;
    unsigned int period;
    int instructionIndex;
};

// Function that determines period of a cycle
unsigned int determinePeriod(const std::string& startingNode, const std::unordered_map<std::string, std::pair<std::string, std::string>>& nodeTripleMap, const std::string& instructions, int instructionIndex = 0)
{
    unsigned int period {0};
    std::string currentNode {startingNode};
    int i {instructionIndex};

    while (true)
    {
        if (instructions[i] == 'R')
        {
            auto it = nodeTripleMap.find(currentNode);
            // std::unordered_map::find will return std::unordered_map::end if the specified key is not found in the container
            if (it != nodeTripleMap.end()) {
                currentNode = it->second.second;
            }
        }
        else if (instructions[i] == 'L')
        {
            auto it = nodeTripleMap.find(currentNode);
            if (it != nodeTripleMap.end()) {
                currentNode = it->second.first;
            }
        }

        if (i == instructions.size()-1) {i = 0;}
        else {i++;}

        period++;

        if (currentNode == startingNode && i == 0) {break;}
    }

    return period;
}

Cycle FindCycle(const std::string& startingNode, const std::unordered_map<std::string, std::pair<std::string, std::string>>& nodeTripleMap, const std::string& instructions)
{
    // If currentNode is not in nodeTripleMap then exit with error
    if (nodeTripleMap.find(startingNode) == nodeTripleMap.end())
    {
        std::cout << "Error: currentNode not in nodeInstructionIndexMap\n";
        exit(1);
    }

    std::string currentNode {startingNode};
    int instructionIndex {0};

    // unsorted_map that contains key = node and value = index of instruction
    std::unordered_map<std::string, int> nodeInstructionIndexMap;

    // Loop through nodeTripleMap and initialize nodeInstructionIndexMap
    for (const auto& node : nodeTripleMap)
    {
        nodeInstructionIndexMap[node.first] = -1;
    }

    // while loop that loops over instructions
    while (true)
    {
        // If currentNode is in nodeInstructionIndexMap and instructionIndex is equal to the value of currentNode in nodeInstructionIndexMap then break
        if (nodeInstructionIndexMap[currentNode] == instructionIndex) {break;}

        // If currentNode is in nodeInstructionIndexMap and instructionIndex is not equal to the value of currentNode in nodeInstructionIndexMap then update nodeInstructionIndexMap
        nodeInstructionIndexMap[currentNode] = instructionIndex;

        // Update currentNode
        if (instructions[instructionIndex] == 'R')
        {
            auto it = nodeTripleMap.find(currentNode);
            if (it != nodeTripleMap.end()) {currentNode = it->second.second;}
        }
        else if (instructions[instructionIndex] == 'L')
        {
            auto it = nodeTripleMap.find(currentNode);
            if (it != nodeTripleMap.end()) {currentNode = it->second.first;}
        }

        // Update instructionIndex
        if (instructionIndex == instructions.size()-1) {instructionIndex = 0;}
        else {instructionIndex++;}
    }

    // Calculate period of cycle
    unsigned int period {determinePeriod(currentNode, nodeTripleMap, instructions, instructionIndex)};

    // Create Cycle object
    Cycle cycle {startingNode, period, instructionIndex};

    return cycle;
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

    // Create vector starting nodes, i.e., all nodes that end with 'A'
    std::vector<std::string> startingNodes;
    for (const auto& node : nodeTripleMap)
    {
        if (node.first[2] == 'A')
        {
            startingNodes.push_back(node.first);
        }
    }
    std::vector<std::string> currentNodes {startingNodes};

    // Calculate and print cycles
    std::vector<Cycle> cycleVector;
    for (const auto& startingNode : startingNodes)
    {
        cycleVector.push_back(FindCycle(startingNode, nodeTripleMap, instructions));
        std::cout << "Cycle starting at node " << startingNode << ": Starts at " << cycleVector.back().startingNode << ", has period " << cycleVector.back().period << " and instruction index " << cycleVector.back().instructionIndex << '\n';
    }

    /* std::vector<Cycle> cycleVector;
    for (const auto& startingNode : startingNodes)
    {
        cycleVector.push_back(FindCycle(startingNode, nodeTripleMap, instructions));
        std::cout << "Cycle of starting node " << startingNode << ": " << cycleVector.back().startingNode << " " << cycleVector.back().period << "\n";
    } */

    // Calculate how many times each cycle hits a node that ends with 'Z'
    /* std::unordered_map<Cycle, int> cycleCountMap;
    for (const auto& cycle : cycleVector)
    {
        int count {0};
        std::string currentNode {cycle.startingNode};
        for (unsigned int i {0}; i < cycle.period; i++)
        {
            if (currentNode[2] == 'Z') {count++;}
            auto it = nodeTripleMap.find(currentNode);
            if (it != nodeTripleMap.end()) {currentNode = it->second.second;}
        }
        cycleCountMap[cycle] = count;
    } */

    // Calculate least common multiple of all periods
    unsigned long long lcm {cycleVector[0].period};
    for (int i = 1; i < cycleVector.size(); i++)
    {
        unsigned long long a {lcm};
        unsigned long long b {cycleVector[i].period};
        while (a != b)
        {
            if (a < b) {a += lcm;}
            else {b += cycleVector[i].period;}
        }
        lcm = a;
    }
    std::cout << "Least common multiple of all periods: " << lcm << '\n';

    // Close input file
    inputFile.close();

    return 0;
}
