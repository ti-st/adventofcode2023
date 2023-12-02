#include"functions.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>


int main(int argc, char const *argv[])
{
    // Read input file
    std::ifstream inputFile;
    inputFile.open("day_1_input.txt",std::ios_base::in);
    if (!inputFile.is_open())
    {
        std::cout << "File could not be opened :C\n";
        exit(1);
    }
    std::cout << "Successfully opened file!\n";

    // iterate over imput file
    int counter {0};
    int firstDigit {};
    int lastDigit {};
    bool isFirstNumber {};
    std::string dummyLine {};
    while (std::getline(inputFile, dummyLine))
    {
        // Convert line
        ConvertLine(dummyLine);

        firstDigit = 0;
        lastDigit = 0;
        isFirstNumber = true;
        for (char ch : dummyLine)
        {
            if (IsNumber(ch))
            {
                lastDigit = ConvertToNumber(ch);
                if (isFirstNumber)
                {
                    firstDigit = ConvertToNumber(ch);
                    isFirstNumber = false;
                }
                
            }
        }
        counter += firstDigit*10 + lastDigit;
    }

    // print result
    std::cout << "The result of the task is: " << counter << '\n';
    
    inputFile.close();

    return 0;
}