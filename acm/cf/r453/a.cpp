#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int cnt, dst;
    cin >> cnt >> dst;

    int pos = 0; bool ok;
    while (cnt--)
    {
        int nxt, dis; cin >> nxt >> dis;
        if (nxt <= pos) pos = max(dis, pos);
        else break;
    }
    if (pos >= dst) ok = true;
    else ok = false;

    if (ok) cout << "YES" << endl;
    else cout << "NO" << endl;
}
