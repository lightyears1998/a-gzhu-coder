#include <iostream>
using namespace std;

int main()
{
    int n, pos, l, r;
    cin >> n >> pos >> l >> r;

    int tot = 0;
    if (pos < l)
        tot = l - pos + 1 + (r != n ? r - l + 1 : 0);
    else if (pos > r)
        tot = pos - r + 1 + (l != 1 ? r - l + 1 : 0);
    else
    {
        if (r != n)
        {
            tot = r - pos + 1;
            pos = r;
        }
        tot += (l != 1 ? pos - l + 1 : 0);
    }

    cout << tot << endl;
}
