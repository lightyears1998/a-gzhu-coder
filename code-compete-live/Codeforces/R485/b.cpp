#include <bits/stdc++.h>
using namespace std;

int main()
{
	int x, y; cin >> x >> y;
	
	if (x == y) {
		cout << '=' << endl;
		return 0;
	}
	
	double lhs = y*log(x), rhs = x*log(y); 
	if (lhs > rhs) {
		cout << '>' << endl;
	}
	else if (lhs < rhs) cout << '<' << endl;
	else cout << '=' << endl;
}
