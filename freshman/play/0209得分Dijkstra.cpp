#include <bits/stdc++.h>
using namespace std;

const int maxN = 550;
const int INF  = 0x3F3F3F3F;

int n, m;
bool vis[maxN];
int got[maxN];
int dis[maxN];
int point[maxN];
int path[maxN][maxN];
int front[maxN];

void dijkstra(int start, int end)
{
	dis[start] = 0;
	while (!vis[end])
	{
		int marker = start, amin = INF, agot = 0;
		for (int j = 0; j < n; ++j) if (!vis[j])
		{
			if (dis[j] < amin || (dis[j] == amin && got[front[j]] + point[j] > agot)) {
				marker = j; amin = dis[j]; 
				agot = got[front[j]] + point[j];
			}
		}
		vis[marker] = true; 
		got[marker] = got[front[marker]] + point[marker];
		for (int j = 0; j < n; ++j) if (!vis[j])
		{
			if (dis[j] == dis[marker] + path[marker][j] && got[front[j]] < got[marker]) 
				front[j] = marker;
			if (dis[j] > dis[marker] + path[marker][j]) {
				dis[j] = dis[marker] + path[marker][j];
				front[j] = marker;
			}
		}
	}
}

int main()
{
	memset(dis, 0x3F, sizeof(dis));
	memset(path, 0x3F, sizeof(path));
	
	int start, end; cin >> n >> m >> start >> end;
	for (int i = 0; i < n; ++i)
	{
		cin >> point[i];
		path[i][i] = 0;
		front[i] = i;
	}
	while (m--)
	{
		int x, y, z; cin >> x >> y >> z;
		path[x][y] = z;
		path[y][x] = z;
	}
	dijkstra(start, end);
	cout << dis[end] << ' ' << got[end] << endl;
}

