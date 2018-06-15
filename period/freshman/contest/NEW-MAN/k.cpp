/*
* this code is made by 1706300001
* Problem: 1466
* Verdict: Accepted
* Submission Date: 2017-12-10 14:21:47
* Time: 44 MS
* Memory: 2800 KB
*/
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

long long ans[100010];

void build()
{
    ans[1] = 1;
    ans[2] = 1;
    ans[3] = 1;
    ans[4] = 1;
    ans[5] = 2;
    for (int i = 6; i < 100010; i++)
    {
        ans[i] = (ans[i - 1] + ans[i - 5]) % 1000000007;
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    build();

    int n;
    while (scanf("%d", &n) == 1)
    {
        printf("%lld\n", ans[n]);
    }
}
