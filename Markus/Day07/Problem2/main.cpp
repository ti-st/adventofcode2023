#include"routines.h"
#include"camelcards.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>

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

    /* Read in the hands and bids
    NOTE: std::map already sorts the hands w.r.t. the < operator, i.e., first pair in map corresponds to lowest rank hand */
    std::string line;
    std::map<Hand, int> handAndBids;
    Hand tmpHand {NOT_A_CARD, NOT_A_CARD, NOT_A_CARD, NOT_A_CARD, NOT_A_CARD};
    int tmpBid {};
    while (std::getline(inputFile, line))
    {
        // Read in the hands
        Hand tmpHand = ReadInHand(line);
        // Read in the bids
        int tmpBid = ReadNumber(line, line.size()-1);
        // Add the hand and bid to the map
        handAndBids[tmpHand] = tmpBid;
    }

    // Calculate the total winnings, i.e., add up all the bids * rank of the hand
    int totalWinnings {};
    int rankCounter {1};
    for (const auto& pair : handAndBids)
    {
        totalWinnings += pair.second * rankCounter;
        rankCounter++;
    }

    // Print the total winnings
    std::cout << "Total winnings: " << totalWinnings << '\n';

    return 0;
}
