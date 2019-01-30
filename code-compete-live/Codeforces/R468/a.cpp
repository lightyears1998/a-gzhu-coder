#include <bits/stdc++.h>
using namespace std;

int main()
{
	int a, b; cin >> a >> b;
	if (a > b) swap(a, b);
	
	int sa = (b-a)/2, sb = sa+(b-a)%2;
	int ans = (1+sa)*sa/2 + (1+sb)*sb/2;	
	cout << ans << endl;
} 
