/**
 * Implementation of official editorial
 * http://codeforces.com/blog/entry/55841
 *
 * Find out who is alive using minimal position.
**/
#include <cstdio>
#include <algorithm>
using namespace std;

int pos[(int)1e6 + 10];

int main()
{
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &pos[i]);
        pos[i] = i - pos[i];
    }
    int alive = 0, mnpos = n + 1;
    for (int i = n; i > 0; i--)
    {
        if (i < mnpos) alive++;
        mnpos = min(mnpos, pos[i]);
    }
    printf("%d\n", alive);
}
