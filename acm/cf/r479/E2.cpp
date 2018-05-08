#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5+10;

int n, m, ans;
int pre[maxN];
int deg[maxN];
bool notcyc[maxN];

void init()
{
	ans = n;
	iota(pre, pre+maxN, 0);
}

int find(int x)
{
	return pre[x]==x ? pre[x] : pre[x]=find(pre[x]);
}

void merge(int a, int b)
{
	a = find(a), b = find(b);
	if (a == b) return;
	
	pre[b] = a, --ans;
}

void calc()
{
	
}

int main()
{
	cin >> n >> m;
	init();
	
	for (int i=0; i<m; ++i) {
		int u, v; cin >> u >> v;
		merge(u, v); 
		++deg[u], ++deg[v];
	}
	
	for (int i=1; i<=n; ++i) {
		if (notcyc[find(i)]) continue;
		if (deg[i] != 2) {
			--ans;
			notcyc[find(i)] = true;
		}
	}
	cout << ans << endl;
}
