#include <bits/stdc++.h>
using namespace std;

int main()
{
	#ifdef LOCAL
	freopen("out.txt", "r", stdin);
	freopen("gen.txt", "w", stdout);
	#endif
	
	cout << "ans[maxN] = {" << endl;
	for (int i=0; i<=10000; ++i) 
	{
		int n; scanf("%d", &n);
		if (i % 2 == 0) cout << n << ',' << ' ';
	}
	cout << '}' << endl;
} 
