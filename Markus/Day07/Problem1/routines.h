
#ifndef ROUTINES_H
#define ROUTINES_H

#include "camelcards.h"
#include <string>

inline bool IsNumber(char ch) {return (ch>47)&&(ch<58);}
inline int ConvertToNumber(char ch) {return ch-48;}

int IntPower(int x, unsigned int p);
int ReadNumber(const std::string& line, int i, int counter = 0);

Cards TranslateCharToCard(char ch);
Hand ReadInHand(const std::string& line);

#endif // ROUTINES_H
