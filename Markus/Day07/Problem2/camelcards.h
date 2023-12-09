
#ifndef CAMELCARDS_H
#define CAMELCARDS_H

#include <vector>
#include <algorithm>
#include <map>

// Enum that represents the different cards
enum Cards {NOT_A_CARD = -1, JOKER = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, QUEEN = 12, KING = 13, ACE = 14};

// Enum that represents the different ranks a hand can have
enum HandRank {HIGH_CARD, PAIR, TWO_PAIR, THREE_OF_A_KIND, FULL_HOUSE, FOUR_OF_A_KIND, FIVE_OF_A_KIND};

// Struct that represents a hand of five cards
struct Hand
{
    Cards firstCard;
    Cards secondCard;
    Cards thirdCard;
    Cards fourthCard;
    Cards fifthCard;

    // Constructor
    Hand(Cards firstCard, Cards secondCard, Cards thirdCard, Cards fourthCard, Cards fifthCard);
    // Method that returns a vector containing the hand position of a card
    std::vector<int> GetCardPosition(Cards card) const;
    // Method that returns the rank of a hand
    HandRank GetRank() const;
    // Less than operator for std::sort (also needed for std::map)
    bool operator<(const Hand& other) const;
};

// Function that returns a map containing pairs of cards and the number of times they appear in the hand
std::map<Cards, int> NumberOfCards (const Hand& hand);

#endif // CAMELCARDS_H
