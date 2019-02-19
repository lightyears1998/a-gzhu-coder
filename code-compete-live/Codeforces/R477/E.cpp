// TLE

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int n;
vector<LL> num;
vector<LL> build;

int main()
{
	for (int i=0; i<n; ++i) {
		LL cur; cin >> cur;
		num.push_back(cur);
	}
	sort(num.begin(), num.end());
	build.resize(n);
	
	do {
		build[0] = num[0];
		for (int i=1; i<n; ++i) {
			build[i] = 
		}
	} while (next_permutation(num.begin(), num.end()));
	
	if (flag)  {
		cout << "Yes" << endl;
		for (int cur : num) {
			cout << cur << ' ';
		}
		cout << endl;
	}
	else cout << "No" << endl;
}
