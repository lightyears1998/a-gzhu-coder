#include <bits/stdc++.h>
using namespace std;

int m;
map<int, double> to;
map<double, int> cnt;

int main()
{
	cin >> m;
	for (int i=1; i<=m; ++i) {
		int a, b, c; scanf(" (%d+%d)/%d", &a, &b, &c);
		double dst = double(a+b)/c;
		to[i] = dst, cnt[dst]++;
	}
	
	for (int i=1; i<=m; ++i) {
		cout << cnt[to[i]];
		cout << (i == m ? '\n' : ' ');
	}
}
