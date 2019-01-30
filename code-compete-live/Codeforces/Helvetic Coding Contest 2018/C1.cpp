#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int maxN = 100100;

int n, p;
LL psum[maxN];

int main()
{
	cin >> n >> p;
	for (int i=1; i<=n; ++i) {
		cin >> psum[i];
		psum[i] += psum[i-1];
	}
	
	LL mx = 0;
	for (int i=1; i<n; ++i) {
		LL a = psum[i] % p;
		LL b = (psum[n]-psum[i]) % p;
		mx = max(mx, a+b);
	}
	cout << mx << endl;
}
