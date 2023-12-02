#include<iostream>
#include<fstream>
#include<string>

inline bool IsNumber(char ch) {return (ch>47)&&(ch<58);}
int ConvertToNumber(char ch)
{
    if (!IsNumber(ch)) {return -1;}
    return ch-48;
}

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
        //std::cout << firstDigit*10 + lastDigit << '\n';
    }

    // print result
    std::cout << "The result of the task is: " << counter << '\n';

    inputFile.close();

    return 0;
}