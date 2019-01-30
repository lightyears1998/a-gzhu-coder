#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using pi = pair<int, int>; 

const int maxN = 1e5+10;
const int maxK = 1e2+10;

int n, m, k, s;
bool vis[maxK][maxN];
queue<pi> stk[maxK];
vector<int> from[maxN];
vector<int> city[maxN];

int main()
{	
	cin >> n >> m >> k >> s;
	for (int i=0; i<n; ++i) {
		int cur; cin >> cur;
		stk[cur].push({i+1, 0});
	}
	for (int i=0; i<m; ++i) {
		int u, v; cin >> u >> v;
		from[u].push_back(v);
		from[v].push_back(u);
	}
	
	for (int i=1; i<=k; ++i) {
		while (!stk[i].empty()) {
			int cit = stk[i].front().first;
			
			if (vis[i][cit]) {
				stk[i].pop(); continue;
			}
 			else vis[i][cit] = true;
			
			city[cit].push_back(stk[i].front().second);
			
			for (unsigned w=0; w<from[cit].size(); ++w) {
				if (vis[i][from[cit][w]]) continue;
 				stk[i].push({from[cit][w], stk[i].front().second+1});
			}
			stk[i].pop();
		}
	}
	
	for (int i=1; i<=n; ++i) {
		sort(city[i].begin(), city[i].end());
		
		LL ans = 0;
		for (int j=0; j<s; ++j) {
			ans += city[i][j];
		}
		cout << ans << ' ';
	}
	cout << endl;
}
