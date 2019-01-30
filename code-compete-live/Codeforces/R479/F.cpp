#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5+10;

int n;
int num[maxN];
map<int, int> dp;
map<int, int> pos;

int main()
{
	cin >> n;
	for (int i=1; i<=n; ++i) {
		cin >> num[i];
	}
	
	for (int i=1; i<=n; ++i) {
		dp[num[i]] = dp[num[i]-1]+1;
		
		pos[num[i]] = i;
	}
	
	int mx = -1, lst = -1;
	for (auto it=dp.begin(); it!=dp.end(); ++it) {
		if (it->second > mx) {
			mx = it->second;
			lst = it->first;
		}
	}
	
	cout << mx << endl;
	vector<int> vec;
	int head = n;
	while (mx--) {
		while (num[head] != lst) --head;
		vec.push_back(head); --lst;
	}
	reverse(vec.begin(), vec.end());
	for (unsigned i=0; i<vec.size(); ++i) {
		if (i) cout << ' ';
		cout << vec[i];
	}
	cout << endl;
}
