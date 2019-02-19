#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using pi = pair<int, int>;

const int maxN = 2e5+10;

map<pi, bool> mp;

LL ans;
vector<int> edge[maxN];
int vis[maxN];

void tag(int u, int v) {
	if (u>v) swap(u, v);
	mp[{u, v}] = true;
}

bool check(int u, int v) {
	if (u>v) swap(u, v);
	return mp[{u, v}];
}

void search(int head, int cur)
{
	if (head != 0 && vis[cur]) {
		if (vis[cur] == 1) {
			++ans; ++vis[cur];
			return;
		}
		if (vis[cur] == 2) {
			--ans; ++vis[cur];
			return;
		}
	}
	else vis[cur] = 1;
	
	for (int x : edge[cur]) {
		if (x != head && !check(cur, x)) {
			search(cur, x); tag(cur, x);
		}
	}
}

int main()
{
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
	
	int n, m; cin >> n >> m;
	for (int i=0; i<m; ++i) {
		int u, v; cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u); 
	}
	
	for (int i=1; i<=n; ++i) {
		search(0, i);
	}
	cout << ans << endl;
}
