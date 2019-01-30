#include <bits/stdc++.h>
using namespace std;

struct ZWKSegmentTree
{
	int levl;
	long long *node, *head;
	long long bgn, end;
	
	ZWKSegmentTree(int n)
	{
		levl = n;
		bgn = 1 << (levl - 1), end = 1 << levl;
		node = new long long[end], head = node + bgn;
	}
	
	void clear()
	{
		memset(node, 0, end * sizeof(long long));
	}
	
	void build()
	{
		for (long long i = bgn; i < end; ++i)
		{
			long long cur = i;
			while (cur >>= 1) node[cur] = max(node[2*cur], node[2*cur+1]);
		}
	}
	
	void update(int n, int v)
	{
		n += bgn, node[n] += v;
		while (n >>= 1) {
			node[n] = max(node[2*n], node[2*n+1]);
		}
	}
	
	long long query(int a, int b)
	{
		long long tot = 0;
		for (a += bgn - 1, b += bgn + 1; a ^ b ^ 1; a >>= 1, b >>= 1)
		{
			if (~a&1) tot = max(tot, node[a^1]);
			if (b&1) tot = max(tot, node[b^1]);
		}
		return tot;
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


