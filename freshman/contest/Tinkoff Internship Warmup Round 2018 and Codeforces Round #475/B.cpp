#include <bits/stdc++.h>
using namespace std;

const int maxN = 1010;

int tme[1010];

int main()
{
	int n, A, B, C, T; cin >> n >> A >> B >> C >> T;
	for (int i=1; i<=n; ++i) {
		cin >> tme[i];
	}
	
	if (B >= C) {
		cout << n*A << endl;
	}
	else {
		long long ans = 0;
		for (int i=1; i<=n; ++i) {
			ans += (T-tme[i])*(C-B)+A;
		}
		cout << ans;
	}
}
