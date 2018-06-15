#include <bits/stdc++.h>
using namespace std;

const int maxN = 1008611;

int key; string tar, ans;
int cipher[maxN], plain[maxN];

int main()
{
	while (scanf("%d", &key) == 1 && key) 
	{
		memset(cipher, 0, sizeof(cipher));
		memset(plain, 0, sizeof(plain));
		
		cin >> tar; int n = tar.size();
		for (int i=0; i<n; ++i) {
			if (tar[i] == '_') cipher[i] = 0;
			else if (tar[i] == '.') cipher[i] = 27;
			else cipher[i] = tar[i]-'a'+1;
		}
	
		for (int i=0; i<n; ++i) {
			plain[key*i%n] = (cipher[i]+i) % 28;
		}
		
		ans.resize(n);
		for (int i=0; i<n; ++i) {
			if (plain[i] == 0) ans[i] = '_';
			else if (plain[i] == 27) ans[i] = '.';
			else ans[i] = plain[i]+'a'-1;
		}
		cout << ans << endl;
	}
} 
