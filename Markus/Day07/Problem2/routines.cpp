
#include"routines.h"
#include"camelcards.h"
#include<string>

int IntPower(int x, unsigned int p)
{
    if (p == 0) {return 1;}
    if (p == 1) {return x;}
    
    int tmp = IntPower(x, p/2);
    if (p%2 == 0) {return tmp * tmp;}
    else {return x * tmp * tmp;}
}

int ReadNumber(const std::string& line, int i, int counter)
{
    int tmp {0};
    if (i>0 && IsNumber(line[i-1]))
    {
        tmp = ReadNumber(line, i-1) * IntPower(10, counter+1);
    }
    return tmp + ConvertToNumber(line[i]) * IntPower(10, counter);
}

Cards TranslateCharToCard(char ch)
{
    switch (ch)
    {
        case '2':
            return TWO;
        case '3':
            return THREE;
        case '4':
            return FOUR;
        case '5':
            return FIVE;
        case '6':
            return SIX;
        case '7':
            return SEVEN;
        case '8':
            return EIGHT;
        case '9':
            return NINE;
        case 'T':
            return TEN;
        case 'J':
            return JOKER;
        case 'Q':
            return QUEEN;
        case 'K':
            return KING;
        case 'A':
            return ACE;
        default:
            return NOT_A_CARD;
    }
}

Hand ReadInHand(const std::string& line)
{
    Hand result {TranslateCharToCard(line[0]), TranslateCharToCard(line[1]), TranslateCharToCard(line[2]), TranslateCharToCard(line[3]), TranslateCharToCard(line[4])};
    return result;
}
