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

// Function that replaces a card in the hand
Hand ReplaceCard(const Hand& hand, int cardNumber, Cards replacementCard)
{
    Hand newHand {hand};
    switch (cardNumber)
    {
        case 1:
            newHand.firstCard = replacementCard;
            break;
        case 2:
            newHand.secondCard = replacementCard;
            break;
        case 3:
            newHand.thirdCard = replacementCard;
            break;
        case 4:
            newHand.fourthCard = replacementCard;
            break;
        case 5:
            newHand.fifthCard = replacementCard;
            break;
    }
    return newHand;
}

// Method that returns a vector containing the hand position of a card
std::vector<int> Hand::GetCardPosition(Cards card) const
{
    std::vector<int> cardPosition;
    if (firstCard == card) {cardPosition.push_back(1);}
    if (secondCard == card) {cardPosition.push_back(2);}
    if (thirdCard == card) {cardPosition.push_back(3);}
    if (fourthCard == card) {cardPosition.push_back(4);}
    if (fifthCard == card) {cardPosition.push_back(5);}
    return cardPosition;
}

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

    // Take care of hands with many Jokers immediately (for performance reasons)
    switch (numberOfCards[JOKER])
    {
        case 5:
            return FIVE_OF_A_KIND;
        case 4:
            return FIVE_OF_A_KIND;
        case 3:
            if (secondLargestValue == 2)
            {
                return FIVE_OF_A_KIND;
            }
            else
            {
                return FOUR_OF_A_KIND;
            }
        default:
            break;
    }

    // Get hand positions of Jokers
    std::vector<int> jokerPositions = GetCardPosition(JOKER);

    // Loop through all replacements of the joker and determine the rank of the hand
    // The highest rank is stored in highestRank
    HandRank highestRank {HIGH_CARD};

    if (jokerPositions.size() != 0)
    {
        Hand tmpHand {NOT_A_CARD, NOT_A_CARD, NOT_A_CARD, NOT_A_CARD, NOT_A_CARD};
        for (Cards replacementCard : {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, QUEEN, KING, ACE})
        {
            Hand tmpHand = ReplaceCard(*this, jokerPositions[0], replacementCard);
            HandRank tmpRank {tmpHand.GetRank()};
            if (tmpRank > highestRank)
            {
                highestRank = tmpRank;
            }
        }
    }

    HandRank tmpHighestRank {HIGH_CARD};
    switch (largestValue)
    {
        case 5:
            tmpHighestRank = FIVE_OF_A_KIND;
            break;
        case 4:
            tmpHighestRank = FOUR_OF_A_KIND;
            break;
        case 3:
            if (secondLargestValue == 2)
            {
                tmpHighestRank = FULL_HOUSE;
            }
            else
            {
                tmpHighestRank = THREE_OF_A_KIND;
            }
            break;
        case 2:
            if (secondLargestValue == 2)
            {
                tmpHighestRank = TWO_PAIR;
            }
            else
            {
                tmpHighestRank = PAIR;
            }
            break;
        case 1:
            tmpHighestRank = HIGH_CARD;
            break;
    }

    return highestRank > tmpHighestRank ? highestRank : tmpHighestRank;
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