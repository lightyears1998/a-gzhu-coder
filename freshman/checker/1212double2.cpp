#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

const long long m = 1000000007;
long long ff(long long a, long long b)
{
    long long c = 1;
    while (b)
    {
        if (b & 1)
        {
            c = c * a % m;
        }
        b >>= 1;
        a *= a;
        a %= m;
//!     a *=a % m;
    }
    return c;
}

int main()
{
    long long a, b;
    while (scanf("%lld%lld",&a,&b) == 2)
    {
        long long s = a;
        long long ans = ff(a, b) - a;
        if (ans < 0) ans += m;
        printf("%lld\n", ans);
    }
}
