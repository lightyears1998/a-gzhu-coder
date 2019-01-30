#include <bits/stdc++.h>
using namespace std;

const int maxN = 1010;

int n; 
int conn[maxN];

int main()
{	
	cin >> n;
	for (int i=0; i<n-1; ++i) {
		int u, v; cin >> u >> v;
		conn[u]++, conn[v]++;
	}
	
	int ans = 0;
	for (int i=1; i<=n; ++i) {
		if (conn[i] == 1) ++ans;
	}
	cout << ans << endl;
} 
