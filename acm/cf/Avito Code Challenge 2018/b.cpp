#include <bits/stdc++.h>
using namespace std;
using LL = long long;

map<int, LL> mp;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
	int n; cin >> n;
	while (n--)
	{
		int key; LL val; cin >> key >> val;
		mp[key] = max(mp[key], val);
	}
	int m; cin >> m;
	while (m--)
	{
		int key; LL val; cin >> key >> val;
		mp[key] = max(mp[key], val);
	}
	
	map<int, LL>::iterator it; LL ans = 0;
	for (it = mp.begin(); it!=mp.end(); ++it)
	{
		ans += it->second; 
	}
	cout << ans << endl;
}
