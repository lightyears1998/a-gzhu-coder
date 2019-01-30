#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, k; cin >> n >> k;
	string s, ans; cin >> s; ans = s; 
	sort(s.begin(), s.end());
	s.resize(unique(s.begin(), s.end()) - s.begin());
	
	if (n < k)
	{
		int t = k-n;
		while (t--) ans += s[0];
	}
	else
	{
		ans.resize(k);
		for (unsigned i = k-1; i>=0; --i)
		{
			if (ans[i] == s.back()) ans[i] = s[0];
			else {
				ans[i] = s[s.find(ans[i]) + 1];
				break;
			}
		}
	}
	cout << ans << endl;
}
