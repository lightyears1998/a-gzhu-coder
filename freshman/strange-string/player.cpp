#include <cstdio>
#include <iostream>

void play(const char * str, bool endl = false)
{
    std::cout << str;
    if (endl) std::cout << std::endl;
}

void play(char ch, bool endl = false)
{
    printf("%c[%d]", ch, (int)ch);
    if (endl) std::cout << std::endl;
}
