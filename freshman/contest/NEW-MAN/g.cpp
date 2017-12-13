/*
* this code is made by 1706300001
* Problem: 1462
* Verdict: Accepted
* Submission Date: 2017-12-10 16:19:15
* Time: 244 MS
* Memory: 2088 KB
*/
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>
#include <queue>
using namespace std;

char map[110][110];
int idx[110][110];
int tot;

struct point
{
    int x, y;
};

queue<point> que;

void merge()
{
    point cur = que.front();
    que.pop();
    int i = cur.x, j = cur.y;

    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {
            if (map[i + x][j + y] == '1')
            {
                if (idx[i + x][j + y] == 0)
                {
                    idx[i + x][j + y] = idx[i][j];
                    point tmp = {i + x, j + y};
                    que.push(tmp);
                }
            }
        }
    }

}


int main()
{
    // freopen("in.txt", "r", stdin);

    int n, m;
    while (scanf("%d%d", &n, &m) == 2)
    {
        memset(map, '0', sizeof(map));
        memset(idx, 0, sizeof(idx));
        tot = 1;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                scanf(" %c", &map[i][j]);
            }
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (map[i][j] == '1')
                {
                    if (idx[i][j] == 0)
                    {
                        idx[i][j] = tot++;
                        point tmp = {i, j};
                        que.push(tmp);
                        while (!que.empty())
                        {
                            merge();
                        }
                    }
                }
            }
        }

        printf("%d\n", tot - 1);
    }
}
