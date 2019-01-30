#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL num[14];

LL take(int pos)
{
	LL nxt[14];
	for (int i=0; i<14; ++i) {
		nxt[i] = num[i];
	}
	
	LL db = nxt[pos];
	if (db == 0) return 0;
	
	nxt[pos] = 0;
	for (int i=1; i<=14; ++i) {
		nxt[(pos+i)%14] += db/14+(db%14-i>=0?1:0);	
	}

	LL ret = 0;
	for (int i=0; i<14; ++i) {
		if (nxt[i] % 2 == 0) 
			ret += nxt[i];
	}
	return ret;
}

int main()
{
	for (int i=0; i<14; ++i) {
		cin >> num[i];
	}
	
	LL ans = 0;
	for (int i=0; i<14; ++i) {
		ans = max(ans, take(i));
	}
	cout << ans << endl;
}
