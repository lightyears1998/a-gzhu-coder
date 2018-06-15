#include <bits/stdc++.h>
using namespace std;

const int maxN = 8;
const int maxM = 1010101;

int num[maxN][maxN][maxM];
int len[maxN][maxN];

bool check(int i, int j, int pos)
{
	if (num[i][j][pos] == 1 && num[i][j][pos-1] == 1) return true;
	return false;
}

int main()
{	
	for (int i=0; i<maxN; ++i)
	{
		for (int j=0; j<maxN; ++j)
		{
			num[i][j][0] = 1, num[i][j][1] = 1; 
			for (int k = 2; k<maxM; ++k)
			{
				num[i][j][k] = (i*num[i][j][k-1] + j*num[i][j][k-2])%7;
				if (check(i, j, k)) {
					len[i][j] = k-1;
					break;
				}
			}
		}
	}
	
	for (int i=0; i<maxN; ++i)
		for (int j=0; j<maxN; ++j)
			if (len[i][j] == 0) cout << i << ' ' << j << ' ' << len[i][j] << endl;
	
	int x, y, m;
	while (scanf("%d%d%d", &x, &y, &m) == 3 && (x||y||m))
	{
		x %= 7, y %= 7;
		if (x == 0 && y == 0) printf("%d\n", 0);
		else printf("%d\n", num[x][y][(m-1)%len[x][y]]);
	}
	
}
