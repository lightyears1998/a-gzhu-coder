#include <cstdio>

int main()
{
    long long m, n;
    while (scanf("%lld%lld", &m, &n) == 2)
    {
        if (m == n) printf("No\n");
        else printf("Yes\n");
    }
}
