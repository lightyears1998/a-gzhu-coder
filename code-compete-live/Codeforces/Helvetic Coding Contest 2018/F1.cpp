#include <bits/stdc++.h>
using namespace std;

int knights[105];
int k[105];

int main()
{
	int n, m; cin >> n >> m;
	for (int i=0; i<n; ++i) {
		cin >> knights[i];
	}
	
	int sum = 0;
	for (int i=0; i<m; ++i) {
		cin >> k[i];
		sum += k[i];
	}
	
	bool flag = false;
	for (int i=0; !flag && i+sum<=n; ++i) {
		int cur[105] {};
		for (int j=0; j<sum; ++j) {
			cur[knights[i+j]-1]++;
		}
		
		bool ok = true;
		for (int j=0; ok && j<m; ++j) {
			if (k[j] != cur[j]) ok = false;
		}
		flag = ok;
	}
	cout << (flag ? "YES" : "NO") << endl;
}
