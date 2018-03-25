#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;
using ll = long long;
using ld = long double;

// 使用Lambda表达式可以简化代码

const int MX = 2018;
ld x[MX], y[MX];

int main()
{
#ifdef LOCAL
    assert(freopen("test.in", "r", stdin));
#endif
    cout << fixed;
    cout.precision(10);

    int n; cin >> n;
    ld r; cin >> r;
    for (int i = 0; i < n; ++i)
    {
        cin >> x[i];
        ld my = r;
        for (int j = 0; j < i; ++j)
        {
            if (2 * r < abs(x[i] - x[j])) continue;
            auto sqr = [](ld x) {return x * x; };
            ld cy = y[j] + sqrt(sqr(2 * r) - sqr(x[i] - x[j]));
            my = max(my, cy);
        }
        y[i] = my;
    }

    for (int i = 0; i < n; ++i)
    {
        if (i) cout << " ";
        cout << y[i];
    }
}
