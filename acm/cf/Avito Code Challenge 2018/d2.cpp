#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int maxN = 55;

int n, k;
LL ans;
LL num[maxN], psum[maxN];

void loop(int k, LL rems = 0, int bgn = 1)
{
	if (bgn > n) return;
	if (k == 1) {
		ans = max(ans, psum[n]&rems);
		return;
	}
	for (int i=bgn; i<=n; ++i) {
		loop(k-1, rems&(psum[i]-psum[bgn-1]), i+1);
	}
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
	cin >> n >> k;
	for (int i=1; i<=n; ++i) {
		cin >> num[i]; psum[i] = psum[i-1]+num[i];
	}
	
	if (k == 1) {
		cout << psum[n] << endl;
		return 0;
	}
	
	LL init; memset(&init, -1, sizeof(LL)-1);
	
	loop(k, init, 1);
	cout << ans << endl;
} 
