#include <bits/stdc++.h>
using namespace std;

const int maxN = 100100;

int sc[maxN];
int st[maxN];

int main()
{
	int n, k; cin >> n >> k;
	
	for (int i=1; i<=n; ++i)
		cin >> sc[i];
		
	for (int i=1; i<=n; ++i)
		cin >> st[i];
	
	int wake = 0;
	for (int i=1; i<=n; ++i)
	{
		if (st[i]) {
			wake += sc[i];
			sc[i] = 0;
		}
	}
	
	for (int i=1; i<=n; ++i)
	{
		sc[i] += sc[i-1];
	}
	 
	int mx = 0;
	for (int i=1; i<=n-k+1; ++i)
	{
		mx = max(sc[i+k-1]-sc[i-1], mx);
	}
	
	cout << wake + mx << endl;
}
