/* 最小生成树的Prim算法 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
const int INF = 0x3F3F3F3F;

struct target // 暗杀对象
{
    int sn;
    int magic;
} g[MAXN][MAXN];
// g[i] 表示i可以联结的所有对象
// g[i][0] 表示i拥有联结的数量
// g[i][j].sn 表示i可以联结的第j个对象的编号
// g[i][j].magic 此联结消耗的魔力

bool v[MAXN]; // v[i]标记节点是否已经加入最小生成树
int dis[MAXN]; // dis[i]标记未加入的节点i加入最小生成树的最小权值

void init(int n)
{
    memset(g, 0, sizeof(g));
    memset(v, 0, sizeof(v));
    for (int i = 1; i <= n; ++i) dis[i] = INF;
    dis[1] = 0;
}

int prim(int n)
{
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        int mark = -1;
        for (int j = 1; j <= n; ++j) if (!v[j])
            if (mark == -1) mark = j;
            else if (dis[j] < dis[mark]) mark = j;

        if (mark == -1) break;

        v[mark] = true;
        if (dis[mark] == INF) return 0;
        ans += dis[mark];
        for (int j = 1; j <= g[mark][0].sn; ++j) if (!v[g[mark][j].sn])
        {
            int sn = g[mark][j].sn;
            dis[sn] = min(dis[sn], g[mark][j].magic);
        }
    }

    return ans;
}

int main()
{
    int n, m; // 暗杀人数和数量
    while (scanf("%d%d", &n, &m) == 2)
    {
        init(n);

        int u, v, w; // 联结的两个对象及联结消耗的魔力
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            g[u][0].sn++; g[v][0].sn++;
            g[u][g[u][0].sn] = {v, w};
            g[v][g[v][0].sn] = {u, w};
        }

        int ans = prim(n);
        if (ans == 0) printf("Unsuccessful...\n");
        else printf("%d\n", ans);
    }
}
