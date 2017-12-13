/*
* this code is made by 1706300001
* Problem: 1461
* Verdict: Accepted
* Submission Date: 2017-12-10 13:02:22
* Time: 132 MS
* Memory: 1508 KB
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int num[100010];

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }

    sort(num, num + n);
    for (int i = 0; i < n; i++)
    {
        if (i) printf(" ");
        printf("%d", num[i]);
    }
    printf("\n");
}
