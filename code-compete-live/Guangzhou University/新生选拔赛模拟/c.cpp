#include <cstdio>
#include <cmath>
const double PI = acos(-1);

int main()
{
    double n;
    while (scanf("%lf", &n) == 1)
    {
        printf("%.2lf\n", n / 180 * PI);
    }
}
