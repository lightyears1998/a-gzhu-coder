#include <cstdio>
#include <cstring>
#include <iostream>

void record(char &ch)
{
    std::cin >> ch;
}

void record(char * str, int length)
{
    memset(str, '\0', length);
    for (int i = 1; i < length; i++) 
    {
        int ch; ch = getchar();
        if (ch != EOF && ch != '\n') {
            *str++ = ch;
        }
        else {
            str++;
            break;
        }
        
    }
    *str = '\0';
}
