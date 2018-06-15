/* Spliting Prefix Zero */
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;

    // 先看下面的这种做法
    while (getline(cin, s))
    {
        bool isprefix = true;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '0' && isprefix) continue;
            else
            {
                cout << s[i];
                isprefix = false;
            }
        }
        cout << endl;
    }

    // 上面那种做法看似很好，但是遇到全部为‘0’的字符串就不灵了
    // 要让它变得灵验，只需要做一点小小的改动
}
