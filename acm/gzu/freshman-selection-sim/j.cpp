#include <cstdio>
using namespace std;

const int mod = 1000000007;

long long fpow(long long a, long long b)
{
    long long base = a % mod, ans = 1;
    while (b)
    {
        if (b & 1)
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
    long long n, m, k;
    while (scanf("%lld%lld%lld", &n, &m, &k) == 3)
    {
        printf("%lld\n", fpow(fpow(k, n), m));
    }
}
