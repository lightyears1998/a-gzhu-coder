#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int maxN = 200200;

int n, q; 
LL str[maxN], sum[maxN];

int main()
{
	cin >> n >> q;
	for (int i=1; i<=n; ++i) {
		cin >> str[i]; 
		sum[i] = str[i]+sum[i-1];
	}
	
	int head = 1, res = sum[1];
	while (q--) {
		LL arr; cin >> arr;
		
		if (arr >= sum[n]-sum[head]+res) {
			head = 1, res = sum[1];
			
			cout << n << endl;
			continue;
		}
		if (arr < res) {
			res -= arr;
			
			cout << (n-head+1) << endl;
			continue;
		}
		LL act = sum[head]+arr-res;
		int pos = upper_bound(sum, sum+n+1, act)-sum;
		head = pos; res = str[pos]-(act-sum[pos-1]);
		
		cout << (n-pos+1) << endl;
	}
} 
