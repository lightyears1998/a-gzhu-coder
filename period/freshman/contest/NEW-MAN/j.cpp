/*
* this code is made by 1706300001
* Problem: 1465
* Verdict: Accepted
* Submission Date: 2017-12-10 14:12:33
* Time: 8 MS
* Memory: 2020 KB
*/
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;


int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int n;
    while (scanf("%d", &n) == 1)
    {
        int tot = 2 * n;
        for (int i = 1; i <= tot; i++)
        {
            for (int j = 1; j <= tot; j++)
            {
                if (i <= n)
                {
                    if (j > n - (i - 1) && j <= n + (i - 1)) printf(" ");
                    else printf("*");
                }
                else
                {
                    if (j > n - (n - (i - n)) && j <= n + (n - (i - n))) printf(" ");
                    else printf("*");
                }
            }
            printf("\n");
        }
    }
}
