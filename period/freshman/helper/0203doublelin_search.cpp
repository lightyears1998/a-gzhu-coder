#include <bits/stdc++.h>
using namespace std;

const int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};

int n, m;
int best;
char pic[55][55];

bool check(int x, int y)
{
	return !(x < 0 || x >= n || y < 0 || y >= m); 
}

void search(int x, int y, int step)
{
	if (step >= best - 1) return;
	
	for (int i = 0; i < 4; ++i)
	{
		int cx = x, cy = y;
		bool first = true;
		 
		while (true)
		{
			int nx = cx + dir[i][0], ny = cy + dir[i][1];
			if (check(nx, ny)) 
			{
				if (pic[nx][ny] == 'E') {
					best = step + 1;
					break;
				}
				else if (pic[nx][ny] == '#') {
					if (first) break;
					pic[nx][ny] = '*';
					search(cx, cy, step+1);
					pic[nx][ny] = '#';
					break;
				}
				else {
					cx = nx, cy = ny;
					first = false;
					continue;
				}
			}
			else break;
		}
	}
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
	while (scanf("%d%d", &m, &n) == 2)
	{
		best = 16;
		int si, sj;
		
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				scanf(" %c", &pic[i][j]);
				if (pic[i][j] == 'S') {
					si = i, sj = j;
				}
			} 
		}
		
		search(si, sj, 0);
		printf("%d\n", (best > 15 ? -1 : best));
	}
} 
