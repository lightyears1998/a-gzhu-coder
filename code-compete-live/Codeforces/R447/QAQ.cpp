#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    while (cin >> s)
    {
        long long cnt = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == 'Q')
            {
                for (int j = i; j < s.length(); j++)
                {
                    if (s[j] == 'A')
                    {
                        for (int k = j; k < s.length(); k++)
                        {
                            if (s[k] == 'Q') cnt++;
                        }
                    }
                }
            }
        }
        cout << cnt << endl;
    }
}
