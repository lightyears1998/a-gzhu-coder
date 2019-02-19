#include <cstdio>

int main()
{
    long long a, b, c;
    while (scanf("%lld%lld%lld", &a, &b, &c) == 3)
    {
        printf("%lld\n", a * b * c);
    }
}
