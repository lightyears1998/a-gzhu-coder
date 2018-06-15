#include <bits/stdc++.h>
using namespace std;

const int maxN = 10086;

int sqr[maxN], tot;

int main()
{
	for (int i=0; i*i<maxN; ++i)
		sqr[i] = i*i, ++tot;
	
	int n;
	while (scanf("%d", &n) == 1)
	{
		for (int i=1; i<tot; ++i)
			for (int j=i; j<tot; ++j)
			{
				int res = n - sqr[i] - sqr[j];
				int pos = lower_bound(sqr, sqr+tot, res)-sqr;
				if (sqr[pos] == res && pos>=j) {
					printf("%d %d %d\n", i, j, pos);
					goto done;
				}
			}
		
		done: continue;
	}

}
