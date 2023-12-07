
#ifndef CAMELCARDS_H
#define CAMELCARDS_H

enum Cards {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

enum HandRank {HIGH_CARD, PAIR, TWO_PAIR, THREE_OF_A_KIND, FULL_HOUSE, FOUR_OF_A_KIND, FIVE_OF_A_KIND};

struct Hand
{
    Cards firstCard;
    Cards secondCard;
    Cards thirdCard;
    Cards fourthCard;
    Cards fifthCard;

    HandRank GetRank() const;
};

#endif // CAMELCARDS_H
