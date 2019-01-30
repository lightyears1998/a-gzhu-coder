#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int maxN = 3030;
const LL INF = 0x3F3F3F3F3F3F3F3F;

struct node {
	LL sz, cst;
	int idx, szrank;
} keys[maxN];

bool cmpsz(const node& a, const node& b) {
	return a.sz < b.sz;
}

bool cmpidx(const node& a, const node& b) {
	return a.idx < b.idx;
}

int n;
LL dp[maxN][4];

int main()
{
	for (int i=0; i<4; ++i) {
		for (int j=0; j<maxN; ++j) {
			dp[j][i] = INF;
		}
	}
	
	cin >> n; 
	for (int i=1; i<=n; ++i) {
		cin >> keys[i].sz;
		keys[i].idx = i;
	}
	for (int i=1; i<=n; ++i) {
		cin >> keys[i].cst;
	}
	
	sort(keys+1, keys+1+n, cmpsz);
	for (int i=1; i<=n; ++i) {
		if (keys[i].sz == keys[i-1].sz) 
			keys[i].szrank = keys[i-1].szrank;
		else keys[i].szrank = i;
	}
	sort(keys+1, keys+1+n, cmpidx);
	
	for (int i=1; i<=n; ++i) {
		LL sz = keys[i].szrank; 
		LL cst = keys[i].cst;
		
		for (int i=1; i<sz; ++i) {
			dp[sz][3] = min(dp[sz][3], dp[i][2] + cst);
		}
		for (int i=1; i<sz; ++i) {
			dp[sz][2] = min(dp[sz][2], dp[i][1] + cst);
		}
		for (int i=1; i<=sz; ++i) {
			dp[sz][1] = min(dp[sz][1], cst); 
		}
	}
	
	LL ans = INF;
	for (int i=1; i<maxN; ++i) {
		ans = min(dp[i][3], ans);
	}
	
	if (ans == INF) {
		cout << -1 << endl;
	}
	else cout << ans << endl;
}
