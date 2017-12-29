#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string s; cin >> s;
    int cnt = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]))
        {
            if ((s[i] - '0') % 2) cnt++;
        }
        else
        {
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') cnt++;
        }
    }

    cout << cnt << endl;
}
