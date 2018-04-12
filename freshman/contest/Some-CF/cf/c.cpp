<<<<<<< HEAD
#include <bits/stdc++.h>
using namespace std;

const int INF  = 0x3F3F3F3F;
const int maxN = 110;

int n, best = INF;
int cnt[4][2];
char pieces[4][maxN][maxN];

int getcd(int idx, int first)
{
	if (cnt[idx][first]) return cnt[idx][first];
	
	int pos = first;
	for (int i=0; i<n; ++i)
	{
		for (int j=0; j<n; ++j)
		{
			if (pieces[idx][i][j] == pos%2+'0');
			else ++cnt[idx][first];
			
			++pos;
		}
	}
	return cnt[idx][first];
}

void search()
{
	int vis[4] = {0, 1, 2, 3};
	do {
		best = min(best, getcd(vis[0], 0)+getcd(vis[1], 1)+getcd(vis[2], 1)+getcd(vis[3], 0));
		best = min(best, getcd(vis[0], 1)+getcd(vis[1], 0)+getcd(vis[2], 0)+getcd(vis[3], 1));
	} while (next_permutation(vis, vis+4));
}

int main()
{
	scanf("%d", &n);
	for (int i=0; i<4; ++i)
		for (int j=0; j<n; ++j)
			for (int k=0; k<n; ++k)
				scanf(" %c", &pieces[i][j][k]);
	
	search();
	printf("%d\n", best);
}
=======
#include <bits/stdc++.h>
using namespace std;

const int INF  = 0x3F3F3F3F;
const int maxN = 110;

int n, best = INF;
int sc[4][2];
char pieces[4][maxN][maxN];

int getcd(int idx, int first)
{
	if (sc[idx][first]) return sc[idx][first];
	
	int pos = first;
	for (int i=0; i<n; ++i)
	{
		for (int j=0; j<n; ++j)
		{
			if (pieces[idx][i][j] == pos%2+'0');
			else ++sc[idx][first];
			
			++pos;
		}
	}
	return sc[idx][first];
}

void search()
{
	int vis[4] = {0, 1, 2, 3};
	do {
		best = min(best, getcd(vis[0], 1)+getcd(vis[1], 0)+getcd(vis[2], 0)+getcd(vis[3], 1));
		best = min(best, getcd(vis[0], 0)+getcd(vis[1], 1)+getcd(vis[2], 1)+getcd(vis[3], 0));
	} while (next_permutation(vis, vis+4));
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif 
	
	scanf("%d", &n);
	for (int i=0; i<4; ++i)
		for (int j=0; j<n; ++j)
			for (int k=0; k<n; ++k)
				scanf(" %c", &pieces[i][j][k]);
	
	search();
	printf("%d\n", best);
}
>>>>>>> 420134ab86db6d30b7838f7aedc3373784224837
