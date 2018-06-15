#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, m; 
	while (cin >> n >> m, ~m && ~n) {
		m %= n;
		cout << (n%m==0 ? "POOR Haha" : "YES") << endl;
	}
}
