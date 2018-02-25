#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n; cin >> n;
	
	vector<int> num(n);
	for (int i = 0; i < n; ++i) cin >> num[i];
	sort(num.begin(), num.end());
	num.resize(unique(num.begin(), num.end()) - num.begin());
	
	int ans = 0;
	for (int c : num)
	{
		if (c>0) ++ ans;
	}
	cout << ans << endl;
}
