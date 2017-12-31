#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 注意此处的range for以及std::find()

int main()
{
    string s; cin >> s;
    string v = "aeiou13579";
    int res = 0;
    for (auto c : s)
    {
        if (find(v.begin(), v.end(), c) != v.end()) ++res;
    }
    cout << res << endl;
}
