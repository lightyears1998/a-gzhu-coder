#include <iostream>
#include <algorithm>
using namespace std;

bool islarger(string a, string b)
{
    if (a.size() != b.size()) return a.size() > b.size();
    for (int i = 0; i < a.size(); ++i)
    {
        if (a[i] != b[i]) return a[i] > b[i];
    }
    return false;
}

string a, b;
string ans;

int main()
{
    string a, b; cin >> a >> b;

    sort(a.begin(), a.end());
    string origin = a;
    while (a[0] == '0')
        next_permutation(a.begin(), a.end());
    ans = a;

    if (a.size() < b.size())
    {
        sort(a.begin(), a.end());
        for (int i = a.size() - 1; i >= 0; --i)
        {
            cout << a[i];
        }
        cout << endl;
    }
    else
    {
        while (islarger(b, a))
        {
            ans = a;
            next_permutation(a.begin(), a.end());
        }
        cout << ans << endl;
    }
}
