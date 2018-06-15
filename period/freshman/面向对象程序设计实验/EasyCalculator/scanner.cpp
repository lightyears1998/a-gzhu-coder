#include "scanner.h"
using namespace std;

void eatline()
{
    cin.clear();
    while (!cin.eof() && cin.get() != '\n') continue;
}

template <>
bool input(string &val, const string &comment)
{
    cout << comment << ">> "; getline(cin, val);
    return !cin.eof();
}
