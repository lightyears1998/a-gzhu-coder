/*
* this code is made by 1706300001
* Problem: 1459
* Verdict: Accepted
* Submission Date: 2017-12-10 12:57:23
* Time: 0 MS
* Memory: 1116 KB
*/
#include <cstdio>
using namespace std;

long long gcd(long long a, long long b)
{
    return (b== 0) ? a : gcd(b, a % b);
}


int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);


    long long a, b;
    while (scanf("%lld%lld", &a, &b) == 2)
    {
        printf("%lld\n", gcd(a, b));
    }
}
