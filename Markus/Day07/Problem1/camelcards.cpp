#include "camelcards.h"
#include <vector>
#include <algorithm>

HandRank Hand::GetRank() const
{
    std::vector<Cards> cards {firstCard, secondCard, thirdCard, fourthCard, fifthCard};
    
    if (std::equal(cards.begin() + 1, cards.end(), cards.begin()) ) // Check for five of a kind
    {
        return FIVE_OF_A_KIND;
    }

    return HIGH_CARD;
}