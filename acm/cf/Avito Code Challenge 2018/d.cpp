#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int maxN = 55;

int n, k;
LL num[maxN], psum[maxN];

vector<int> seg;

int step(int bgn, int tp)
{
	LL privot = (1LL<<tp);
	for (int i=bgn; i<=n; ++i) {
		if ((psum[i]-psum[bgn-1]) & privot) {
			seg.push_back(psum[i]-psum[bgn-1]);
			return i;
		}
	}
	return n+1;
}

LL tri(int tp)
{
	seg.clear(); LL ret = 0;
	
	if (k == 1) {
		return psum[n];
	}
	
	int tail = 0;
	
	cout << tp << endl;
	
	for (int i=0; i<k; ++i) {
		tail = step(tail+1, tp);
		
		cout << tail << ' ';
		
		if (tail > n) break; 
	}
	cout << endl;
	
	if (tail == n) {
		ret = seg[0];
		for (int i=1; i<int(seg.size()); ++i) {
			ret &= seg[i];
		}
	}
	
	return ret;
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
	cin >> n >> k;
	for (int i=1; i<=n; ++i) {
		cin >> num[i]; 
		psum[i] = psum[i-1]+num[i];
 	}
	
	LL ans = 0;
	for (int tp=50; ans==0 && tp; --tp) {
		ans = tri(tp);
	}
	cout << ans << endl;
}

// 59 28 31

