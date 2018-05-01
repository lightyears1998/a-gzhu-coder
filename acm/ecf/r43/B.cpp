#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main()
{
	LL n, m, k; cin >> n >> m >> k;
	if (k < n) {
		cout << 1+k << ' ' << 1 << endl;
	}
	else {
		k -= n;
		int row = k/((m-1)*2);
		int col = k%((m-1)*2);
		
		int arow = n-row*2, acol = 0;
		if (col >= m-1) {
			--arow;
			acol = m-(col-m+1);
		} else acol = 2+col;
		
		cout << arow << ' ' << acol << endl;
	}
}
