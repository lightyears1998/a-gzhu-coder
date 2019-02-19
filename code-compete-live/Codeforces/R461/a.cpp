#include <bits/stdc++.h>
using namespace std;

int main()
{
	int x, y; cin >> y >> x;
	int t = x - 1;
	y -= t;
	cout << (x > 0 && y >= 0 && y % 2 == 0 ? "YES" : "NO") << endl;
}

