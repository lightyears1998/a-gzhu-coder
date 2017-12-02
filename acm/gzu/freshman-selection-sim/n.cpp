/* Unfinished - Wrong Thought */
#include <cstdio>

const int mod = 998244353;

long long fn[100010];
long long ffn[100010];


int main()
{
    fn[0] = 1; ffn[0] = 1;
    for (int i = 1; i <= 100000; i++)
    {
        fn[i] = fn[i - 1] * i % mod;
        ffn[i] = ffn[i - 1] * fn[i] % mod;
    }

    int n;
    while (scanf("%d", &n) == 1)
    {
        printf("%lld\n", ffn[n]);
    }
}
