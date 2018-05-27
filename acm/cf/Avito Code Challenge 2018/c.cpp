#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5+10; 

int n, mx; 
int deg[maxN];
vector<int> ans, cnn[maxN];

void dfs(int id, int from = 0)
{
	for (int v : cnn[id]) {
		if (deg[v] == 1) ans.push_back(v);
		else {
			if (v == from) continue;
			dfs(v, id);
		}		
	}
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
	cin >> n;
	for (int i=0; i<n-1; ++i)
	{
		int a, b; cin >> a >> b;
		deg[a]++, deg[b]++;
		cnn[a].push_back(b), cnn[b].push_back(a);
	}
	
	bool flag = true; int ovecnt = 0;
	for (int i=1; i<=n; ++i)
	{
		if (deg[i] >= 3) {
			++ovecnt;
		}
		if (ovecnt > 1) {
			flag = false;
			break;
		}
	}
	if (flag) {
		cout << "Yes" << endl;
		mx = max_element(deg+1, deg+1+n)-deg;
		dfs(mx);
		
		cout << ans.size() << endl;
		for (int i : ans) {
			cout << mx << ' ' << i << endl;
		}
		cout << endl;
	}
	else cout << "No" << endl;
}

