#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int x, y, z;
int dr[6][3] = { 1,0,0,-1,0,0,0,-1,0,0,1,0,0,0,1,0,0,-1 };
char map[35][35][35];

struct node
{
	int x, y, z;
	int sum;
} ss;

queue<node> q;

int bf()
{
	while (!q.empty())
	{
		ss = q.front();
		q.pop();
		//! q.pop;
		if (map[ss.x][ss.y][ss.z] == 'E') return ss.sum;
		for (int i = 0; i < 6; i++)
		{
			node tt = { ss.x + dr[i][0], ss.y + dr[i][1], ss.z + dr[i][2], ss.sum + 1 };
			//!	if (ss.x >= 1 && ss.x <= x && ss.y >= y && ss.y <= y && ss.z >= 1 && ss.z <= z)
			if (tt.x >= 1 && tt.x <= x && tt.y >= 1 && tt.y <= y && tt.z >= 1 && tt.z <= z)
				if (map[tt.x][tt.y][tt.z] != '#')
					q.push(tt);
		}
		map[ss.x][ss.y][ss.z] = '#';
	}
	return 0;
}

int main()
{
	while (cin >> x >> y >> z)
	{
		if (x == 0 && y == 0 && z == 0) return 0;
		while (!q.empty()) q.pop();
		memset(map, '#', sizeof(map));
		for (int i = 1; i <= x; i++)
		{
			for (int j = 1; j <= y; j++)
			{
				for (int k = 1; k <= z; k++)
				{
					cin >> map[i][j][k];
					if (map[i][j][k] == 'S')
					{
						node s = { i, j, k, 0 };
						q.push(s);
						map[i][j][k] = '#';
					}
				}
			}
		}
		int ans = bf();
		if (ans) cout << "Escaped in " << ans << " minute(s)." << endl;
		else cout << "Trapped!" << endl;
	}
}
