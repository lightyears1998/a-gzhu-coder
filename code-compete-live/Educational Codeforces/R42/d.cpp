#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int maxN = 150150;

LL num[maxN];
map<LL, int> pos;

int main()
{
	int n; cin >> n;
	for (int i=1; i<=n; ++i) {
		LL cur; cin >> cur;
		
		while (pos[cur]) {
			num[pos[cur]] = 0, pos[cur] = 0;
			cur *= 2;
		}
		num[i] = cur, pos[cur] = i;
	}
	
	vector<LL> ans;
	for (int i=1; i<=n; ++i) {
		if (num[i]) ans.push_back(num[i]);
	}
	
	cout << ans.size() << endl;
	for (unsigned i=0; i<ans.size(); ++i) {
		if (i) cout << ' ';
		cout << ans[i];
	}
	cout << endl;
}
