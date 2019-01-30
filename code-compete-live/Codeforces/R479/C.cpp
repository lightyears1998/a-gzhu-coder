#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5+10;

int num[maxN];

int main()
{
	int n, k; cin >> n >> k;
	for (int i=0; i<n; ++i) {
		cin >> num[i];
	}
	
	if (k == 0) {
		sort(num, num+n);
		if (num[0] == 1) cout << -1 << endl;
		else cout << num[0]-1 << endl;
	}
	else if (k == n) {
		sort(num, num+n);
		cout << num[n-1] << endl; 
	}
	else {
		nth_element(num, num+k-1, num+n);
		int priv = num[k-1];
		
		sort(num, num+n);
		int cnt = upper_bound(num, num+n, priv)-num;
		if (cnt == k) {
			cout << priv << endl;
		}
		else cout << -1 << endl;
	}
}
