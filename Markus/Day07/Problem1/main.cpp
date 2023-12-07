#include"routines.h"
#include"camelcards.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_7_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }
    std::cout << "File opened successfully!\n";

    // Test
    Hand hand1 {TWO, TWO, TWO, TWO, TWO};
    // Print its rank
    std::cout << "Hand rank: " << hand1.GetRank() << "\n";

    return 0;
}


