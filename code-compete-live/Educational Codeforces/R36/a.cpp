#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, k; cin >> n >> k;

    vector<int> b(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> b[i];
    sort(b.begin(), b.end());

    int mx = 0;
    for (int i = n; i >= 1; --i)
    {
        if (k % b[i] == 0) {
            mx = b[i]; break;
        }
    }

    cout << k / mx << endl;
}
