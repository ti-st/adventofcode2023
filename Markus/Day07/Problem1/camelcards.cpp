#include "camelcards.h"
#include <vector>
#include <algorithm>
#include <map>

// Function that returns a map containing pairs of cards and the number of times they appear in the hand
std::map<Cards, int> NumberOfCards (const Hand& hand)
{
    std::map<Cards, int> numberOfCards;
    numberOfCards[hand.firstCard] += 1;
    numberOfCards[hand.secondCard] += 1;
    numberOfCards[hand.thirdCard] += 1;
    numberOfCards[hand.fourthCard] += 1;
    numberOfCards[hand.fifthCard] += 1;
    return numberOfCards;
}

// Constructor
Hand::Hand(Cards firstCard, Cards secondCard, Cards thirdCard, Cards fourthCard, Cards fifthCard)
    : firstCard{firstCard}, secondCard{secondCard}, thirdCard{thirdCard}, fourthCard{fourthCard}, fifthCard{fifthCard} {}

// Method that returns the rank of a hand
HandRank Hand::GetRank() const
{
    // Create a vector containing the cards of the hand
    std::vector<Cards> cards {firstCard, secondCard, thirdCard, fourthCard, fifthCard};
    // Map that contains the number of times each card appears in the hand
    std::map<Cards, int> numberOfCards = NumberOfCards(*this);
    
    // Determine largest and second largest value in numberOfCards, representing the number of times a card appears in the hand
    int largestValue {};
    int secondLargestValue {};
    for (const auto& pair : numberOfCards)
    {
        if (pair.second > largestValue)
        {
            secondLargestValue = largestValue;
            largestValue = pair.second;
        }
        else if (pair.second > secondLargestValue)
        {
            secondLargestValue = pair.second;
        }
    }

    // Determine the rank of the hand
    switch (largestValue)
    {
        case 5:
            return FIVE_OF_A_KIND;
        case 4:
            return FOUR_OF_A_KIND;
        case 3:
            if (secondLargestValue == 2)
            {
                return FULL_HOUSE;
            }
            else
            {
                return THREE_OF_A_KIND;
            }
        case 2:
            if (secondLargestValue == 2)
            {
                return TWO_PAIR;
            }
            else
            {
                return PAIR;
            }
    }

    return HIGH_CARD;
}

// Method that returns high card
Cards Hand::GetHighCard() const
{
    Cards highCard {firstCard};
    for (const auto& card : {secondCard, thirdCard, fourthCard, fifthCard})
    {
        if (card > highCard)
        {
            highCard = card;
        }
    }

    return highCard;
}

// Less than operator for std::sort (also needed for std::map)
bool Hand::operator<(const Hand& other) const
{
    // Determine the rank of the hands
    HandRank thisRank {this->GetRank()};
    HandRank otherRank {other.GetRank()};

    // If the ranks are different, return the result of comparing the ranks
    if (thisRank != otherRank)
    {
        return thisRank < otherRank;
    }

    // If the ranks are the same, compare first card, maybe second card, then third card ...
    std::vector<Cards> thisCards {this->firstCard, this->secondCard, this->thirdCard, this->fourthCard, this->fifthCard};
    std::vector<Cards> otherCards {other.firstCard, other.secondCard, other.thirdCard, other.fourthCard, other.fifthCard};
    for (int i = 0; i < 5; i++)
    {
        if (thisCards[i] != otherCards[i])
        {
            return thisCards[i] < otherCards[i];
        }
    }
    
    // Makes warning go away :)
    return false;
}