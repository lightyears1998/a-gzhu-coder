#include <bits/stdc++.h>
using namespace std;
 
const int mod = 1e9 + 7;
 
long long fmod(long long a, long long b)
{
    long long ans = 1, base = a % mod;
    while (b)
    {
        if (b&1) {
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
    long long n, k;
    while (scanf("%lld%lld", &n, &k) == 2)
    {
        if (n == 1) printf("1\n");
        else {
            long long ans = fmod(n, k);
            printf("%lld\n", ans);
        }
    }  
}
