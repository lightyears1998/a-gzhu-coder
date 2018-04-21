#include <bits/stdc++.h>
using namespace std;

int n;

const int maxN = 5000;
char s[maxN];
char buf[maxN][maxN];

int main()
{
	#ifdef LOCAL
	freopen("out.txt", "w", stdout);
	#endif
	
	cin >> n;
	fgets(s, sizeof(s), stdin);
	fgets(s, sizeof(s), stdin);
	
	int pos = 0;
	int mx;
	for (mx = 0; s[pos] != '\n';) {
		for (int i=0; i<n && s[pos] != '\n'; ++i) {
			buf[mx][i] = s[pos++];
		}
		if (s[pos] != '\n') ++mx;
	}
	
//	if (strlen(s)-1 <= (unsigned)n) {
//		for (int i=0; s[i] != '\n'; ++i) {
//			putchar(s[i]); putchar('\n');
//		}
//	}
	else {
		for (int i=0; i<n; ++i) {
			for (int j=mx; j>=0; --j) {
				if (buf[j][i]) printf("%c", buf[j][i]);
				else if (mx!=0) putchar(' ');
			}
			putchar('\n');
		}
	}
}
