#include <bits/stdc++.h>
using namespace std;

void print(int n)
{
	for (int i = 0; i < n; ++i) { 
		cout << "6666666666";
 		cout << ((i + 1 == n) ? "\n" : " ");
	}
	 
	for (int i = 0; i < n; ++i) { 
		cout << "66        ";
 		cout << ((i + 1 == n) ? "\n" : " ");
	}
	
	for (int i = 0; i < n; ++i) { 
		cout << "66        ";
 		cout << ((i + 1 == n) ? "\n" : " ");
	}
	
	for (int i = 0; i < n; ++i) { 
		cout << "6666666666";
 		cout << ((i + 1 == n) ? "\n" : " ");
	}
	
	for (int i = 0; i < n; ++i) { 
		cout << "66      66";
 		cout << ((i + 1 == n) ? "\n" : " ");
	}
	
	for (int i = 0; i < n; ++i) { 
		cout << "66      66";
 		cout << ((i + 1 == n) ? "\n" : " ");
	}
	
	for (int i = 0; i < n; ++i) { 
		cout << "6666666666";
 		cout << ((i + 1 == n) ? "\n" : " ");
	}
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif
	
	int t; cin >> t;
	while(t--)
	{
		int n; cin >> n;
		print(n);
		
		if (t) cout << endl;
	}
}
