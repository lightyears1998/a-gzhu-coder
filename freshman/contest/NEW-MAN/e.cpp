/*
* this code is made by 1706300001
* Problem: 1460
* Verdict: Accepted
* Submission Date: 2017-12-10 13:19:46
* Time: 0 MS
* Memory: 1120 KB
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct animal
{
    int ability, weight, cute;
} ani[150];

bool cmp(animal a, animal b)
{
    if (a.ability != b.ability) return a.ability < b.ability;
    if (a.weight != b.weight) return a.weight > b.weight;
    return a.cute < b.cute;
}


int main()
{

    int n;
    while (scanf("%d", &n) == 1)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d%d", &ani[i].ability, &ani[i].weight, &ani[i].cute);
        }

        sort(ani, ani + n, cmp);

        for (int i = 0; i < n; i++)
        {
            printf("%d %d %d\n", ani[i].ability, ani[i].weight, ani[i].cute);
        }
    }
}
