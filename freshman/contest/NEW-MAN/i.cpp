/*
* this code is made by 1706300001
* Problem: 1464
* Verdict: Accepted
* Submission Date: 2017-12-10 16:42:37
* Time: 124 MS
* Memory: 2020 KB
*/
#include <iostream>
#include <cstdio>
using namespace std;

const int mod = 1000000007;

long long fpow(long long a, long long b)
{
    long long base = a % mod, ans = 1;
    while (b)
    {
        if (b&1)
        {
            ans *= base;
            ans %= mod;
        }
        base *= base;
        base %= mod;
        b >>= 1;
    }
    return ans;
}

int main()
{
    int n, k;
    while (scanf("%d%d", &n, &k) == 2)
    {
        long long ans = fpow(n, k) - n;
        if (ans < 0) ans += mod;
        printf("%lld\n", ans);
    }
}
