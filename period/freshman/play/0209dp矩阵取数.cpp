#include <bits/stdc++.h>
using namespace std;

int num[550][550];

int main()
{
	int n; cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			cin >> num[i][j]; 
			num[i][j] += max(num[i-1][j], num[i][j-1]);
		}
	}
	cout << num[n][n] << endl;
}

