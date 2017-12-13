/*
* this code is made by 1706300001
* Problem: 1468
* Verdict: Accepted
* Submission Date: 2017-12-10 14:52:30
* Time: 460 MS
* Memory: 2804 KB
*/
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

struct number
{
    int val, idx;
} num[100010];

bool cmp(number a, number b)
{
    return a.val < b.val;
}

bool search_cmp(number a, number b)
{
    return a.val == b.val;
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int n, q; scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++)
    {
        num[i].idx = i;
        scanf("%d", &num[i].val);
    }

    sort(num, num + n, cmp);

    for (int i = 0; i < q; i++)
    {
        int query; scanf("%d", &query);

        int find = -1;
        for (int j = 0, k = n - 1; j <= k;)
        {
            int mid = (j + k) / 2;
            if (num[mid].val == query)
            {
                find = mid;
                break;
            }
            else if (num[mid].val < query)
            {
                j = mid + 1;
            }
            else
            {
                k = mid - 1;
            }
        }

        if (find != -1) printf("Pos = %d\n", num[find].idx);
        else printf("No response.\n");
    }
}
