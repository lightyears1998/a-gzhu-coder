#include <bits/stdc++.h>
using namespace std;

map<string, int> mp;

int main()
{
	int n; cin >> n;
	string str; cin >> str;
	
	for (unsigned i=0; i<unsigned(n-1); ++i) {
		string sub = str.substr(i, 2);
		mp[sub]++;
	} 
	
	string mx; int cnt = -1; 
	for (auto it=mp.begin(); it!=mp.end(); ++it)
	{
		if (it->second > cnt) {
			cnt = it->second;
			mx = it->first;
		}
	}
	cout << mx << endl;
}
