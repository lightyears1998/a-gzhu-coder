#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using pi = pair<LL, int>;

int n, x1, x2;
vector<pi> servers;

bool solve(int x1, int x2, vector<int> &ans1, vector<int> &ans2)
{
	ans1.clear(); ans2.clear();
	
	int tail = 0;
	for (int i=n; i>=1; --i) {
		if (!tail) {
			ans1.push_back(servers[i].second); 
			if (servers[i].first*(n-i+1) >= x1) {
				tail = i;
			}
		}
		else {
			ans2.push_back(servers[i].second);
			if (servers[i].first*(tail-i) >= x2) {
				return true;
			}
		}
	}
	return false;
}

int main()
{
	cin >> n >> x1 >> x2;
	servers.resize(n+1);
	
	for (int i=1; i<=n; ++i) {
		LL cur; cin >> cur;
		servers[i] = make_pair(cur, i);
	}
	sort(servers.begin()+1, servers.end());
	
	vector<int> ans1, ans2;
	if (solve(x1, x2, ans1, ans2) || solve(x2, x1, ans2, ans1)) {
		cout << "Yes" << endl << ans1.size() << ' ' << ans2.size() << endl;
		for (int &cur : ans1) {
			cout << cur << ' ';
		}
		cout << endl;
		for (int &cur : ans2) {
			cout << cur << ' ';
		}
		cout << endl;
	}
	else cout << "No" << endl;
}
