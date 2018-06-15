/*
* this code is made by 1706300001
* Problem: 1463
* Verdict: Accepted
* Submission Date: 2017-12-10 13:10:31
* Time: 8 MS
* Memory: 1116 KB
*/
#include <cstdio>
#include <cstring>
using namespace std;

char num[50];

int main()
{

    while (scanf("%s", num) == 1)
    {
        int p = strlen(num);

        long long ans = 0, base = 1;
        for (int i = p - 1; i >= 0; i--)
        {
            if (i)
            {
                ans += (num[i] - '0') * base;
            }
            else
            {
                if (num[i] == '-') ans = -ans;
                else ans += (num[i] - '0') * base;
            }
            base *= 2;
        }

        printf("%lld\n", ans);
    }
}
