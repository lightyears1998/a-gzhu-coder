#include <bits/stdc++.h>
using namespace std;
using LL = long long;
 
// 张昆玮线段树的差分变种
// RMQ适用
 
struct ZKWSegmentTree
{
    int levl;
    long long bgn, end;
    long long *node, *head;
     
    ZKWSegmentTree(int n)
    {
        levl = n;
        bgn = 1 << (levl-1), end = 1 << levl;
        node = new long long[end], head = node + bgn;
    }
     
    void clear()
    {
        memset(node, 0, end * sizeof(long long));
    }
     
    void build()
    {
        for (int i = bgn-1; i; --i)
            node[i] = max(node[2*i], node[2*i+1]);
        for (int i = end-1; i; --i)
            node[i] -= node[i>>1];
    }
  
    void update(int x, int v)
    {
        node[x+=bgn] += v;
        while (x>>=1)
        {
            long long tmp = max(node[2*x], node[2*x+1]);
            node[2*x] -= tmp, node[2*x+1] -= tmp, node[x] += tmp;
        }
    }
     
    // 查询[l, r]上的最大值
    long long query(int l, int r)
    {
        long long ans = 0;
        if (l!=r) {
            long long Lans = 0, Rans = 0;
            for (l+=bgn, r+=bgn; l^r^1; l>>=1, r>>=1)
            {
                Lans += node[l], Rans += node[r];
                if (~l&1) Lans = max(Lans, node[l^1]);
                if (r&1) Rans = max(Rans, node[r^1]);
            }
            Lans += node[l], Rans += node[r];
            ans = max(Lans, Rans);
        }
        else ans = node[l+=bgn];
        while (l>>=1) ans += node[l];
        return ans;
    }
         
} tree(17);
 
int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif
      
    int t, kase = 0; scanf("%d", &t);
    while (t--)
    {
        printf("Case %d:\n", ++kase);
          
        tree.clear();
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld", &tree.head[i]);
        }
        tree.build();
        
        char cmd[10];
        while (scanf("%s", cmd) == 1)
        {
            if (cmd[0] == 'Q')
            {
                int a, b; scanf("%d%d", &a, &b);
                printf("%lld\n", tree.query(a, b));
            }
            if (cmd[0] == 'A')
            {
                int n, v; scanf("%d%d", &n, &v);
                tree.update(n, v);
            }
            if (cmd[0] == 'S')
            {
                int n, v; scanf("%d%d", &n, &v);
                tree.update(n, -v);
            }
            if (cmd[0] == 'E') break;
        }
    }
}
