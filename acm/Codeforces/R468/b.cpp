#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, a, b; cin >> n >> a >> b;
	if (a > b) swap(a, b);
	
	int cnt = 1;
	while (b-a != 1 || !((a&1) && !(b&1)))
	{
		a = (a+1)/2, b = (b+1)/2;
		++cnt;
		n /= 2;
	}
	if (n == 2) cout << "Final!" << endl;
	else cout << cnt << endl;
}
