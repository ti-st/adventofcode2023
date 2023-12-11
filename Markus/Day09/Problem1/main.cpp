#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

inline bool IsNumber(char ch) {return (ch>47)&&(ch<58);}
inline int ConvertToNumber(char ch) {return ch-48;}

long IntPower(long x, unsigned int p)
{
    if (p == 0) {return 1;}
    if (p == 1) {return x;}
    
    long tmp = IntPower(x, p/2);
    if (p%2 == 0) {return tmp * tmp;}
    else {return x * tmp * tmp;}
}

long ReadNumber(const std::string& line, int i, int counter = 0)
{
    long tmp {0};
    if (i>0 && IsNumber(line[i-1]))
    {
        tmp = ReadNumber(line, i-1) * IntPower(10, counter+1);
    }
    return tmp + ConvertToNumber(line[i]) * IntPower(10, counter);
}

bool AllElementsZero(const std::vector<long>& inputSequence)
{
    for (int i = 0; i < inputSequence.size(); ++i)
    {
        if (inputSequence[i] != 0) {return false;}
    }
    return true;
}

std::vector<long> DifferenceSequence(const std::vector<long>& inputSequence)
{
    std::vector<long> outputSequence;
    for (int i = 0; i < inputSequence.size()-1; ++i)
    {
        outputSequence.push_back(inputSequence[i+1] - inputSequence[i]);
    }
    return outputSequence;
}

std::vector<long> PredictionVector(std::vector<long> inputSequence)
{
    std::vector<long> predictionVector {inputSequence};
    std::vector<long> differenceSequence {DifferenceSequence(inputSequence)};
    std::vector<long> tmpVec;

    if (AllElementsZero(differenceSequence))
    {
        predictionVector.push_back(predictionVector[0]);
        return predictionVector;
    }

    differenceSequence = PredictionVector(differenceSequence);
    long newElement {predictionVector[predictionVector.size()-1] + differenceSequence[differenceSequence.size()-1]};
    predictionVector.push_back(newElement);

    return predictionVector;
}

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_9_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }
    std::cout << "File opened successfully!\n";

    // Read input file into vector of vectors
    std::vector<std::vector<long>> inputSequences;
    std::string line;
    while (std::getline(inputFile, line))
    {
        long tmp {0};
        std::vector<long> tmpVec;
        for (int i = 0; i < line.size(); ++i)
        {
            if (i == line.size() - 1 || line[i+1] == ' ')
            {
                tmp = ReadNumber(line, i);
                // Some fuckery to allow for negative numbers
                int j {i};
                while (j-1 >= 0 && IsNumber(line[j-1])) {--j;}
                if (j-1 >= 0 && line[j-1] == '-') {tmp *= -1;}
                tmpVec.push_back(tmp);
            }
        }
        inputSequences.push_back(tmpVec);
    }
    
    long result {0};

    for (int i = 0; i < inputSequences.size(); ++i)
    {
        std::vector<long> predictionVector {PredictionVector(inputSequences[i])};
        result += predictionVector[predictionVector.size()-1];
    }

    std::cout << "Result: " << result << "\n";

    // Close input file
    inputFile.close();

    return 0;
}
