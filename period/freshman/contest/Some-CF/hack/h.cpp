#include <bits/stdc++.h>
using namespace std;

const int maxN = 105;

int hdu[maxN], jap[maxN];

int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n)
	{
		for (int i=0; i<n; ++i) scanf("%d", &hdu[i]);
		for (int i=0; i<n; ++i) scanf("%d", &jap[i]);
		
		sort(hdu, hdu+n);
		sort(jap, jap+n);
		
		int j = 0, h = 0;
		for (int i=0; i<n; ++i) {
			if (hdu[i] == jap[i]) ++j, ++h;
			else if (hdu[i] < jap[i]) j += 2;
			else h += 2;
		}
		printf("%d vs %d\n", h, j);
		
	}
}
