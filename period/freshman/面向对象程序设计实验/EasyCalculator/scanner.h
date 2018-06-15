#include <iostream>
#include <string>
using namespace std;

void eatline();

template <typename T>
bool input(T &val, const string &comment = "")
{
    cout << comment << ">> "; cin >> val;
    return eatline();
}

template <>
bool input(string &val, const string &comment);
