#include <cstdio>

long long gcd(long long a, long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b)
{
    return a * b / gcd(a, b);
}

int main()
{
    int a, b;
    while (scanf("%d%d", &a, &b) == 2)
    {
        printf("%lld\n", lcm(a, b) * lcm(a, b));
    }
}
