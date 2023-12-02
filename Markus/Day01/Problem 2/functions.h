#include<string>
#include<vector>
#include<iostream>

inline bool IsNumber(char ch) {return (ch>47)&&(ch<58);}

int ConvertToNumber(char ch)
{
    if (!IsNumber(ch)) {return -1;}
    return ch-48;
}

// so unfassbar haesslich ...
void ConvertLine (std::string& line)
{
    for (std::string::size_type i = 0; i < line.size(); i++)
    {
        switch (line[i])
        {
        case 'o':
            if (line.size()-i>=3 && line[i+1]=='n' && line[i+2]=='e') {line[i] = '1';}
            break;
        case 't':
            if (line.size()-i>=3 && line[i+1]=='w' && line[i+2]=='o') {line[i] = '2';}
            if (line.size()-i>=5 && line[i+1]=='h' && line[i+2]=='r' && line[i+3]=='e' && line[i+4]=='e') {line[i] = '3';}
            break;
        case 'f':
            if (line.size()-i>=4 && line[i+1]=='o' && line[i+2]=='u' && line[i+3]=='r') {line[i] = '4';}
            if (line.size()-i>=4 && line[i+1]=='i' && line[i+2]=='v' && line[i+3]=='e') {line[i] = '5';}
            break;
        case 's':
            if (line.size()-i>=3 && line[i+1]=='i' && line[i+2]=='x') {line[i] = '6';}
            if (line.size()-i>=5 && line[i+1]=='e' && line[i+2]=='v' && line[i+3]=='e' && line[i+4]=='n') {line[i] = '7';}
            break;
        case 'e':
            if (line.size()-i>=5 && line[i+1]=='i' && line[i+2]=='g' && line[i+3]=='h' && line[i+4]=='t') {line[i] = '8';}
            break;
        case 'n':
            if (line.size()-i>=4 && line[i+1]=='i' && line[i+2]=='n' && line[i+3]=='e') {line[i] = '9';}
            break;
        default:
            break;
        }
    }
}