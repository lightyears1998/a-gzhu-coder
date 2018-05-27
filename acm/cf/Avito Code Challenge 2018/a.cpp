#include <bits/stdc++.h>
using namespace std;

bool pal(string str)
{
	string str1 = str;
	reverse(str.begin(), str.end());
	return str1 != str;
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
	string str; cin >> str;
	
	int ans = str.size();
	while (ans) {
		bool flag = false;
		for (int i=0; i+ans-1<int(str.size()); ++i)
		{
			if (pal(str.substr(i, ans))) flag = true;
			if (flag) break;
		}
		if (flag) break;
		--ans;
	}
	cout << ans << endl;
}

