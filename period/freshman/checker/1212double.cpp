/* 17级新生选拔赛 - 岛屿问题 */
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdio>
#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <string>  
#include <queue>
using namespace std;
struct node
{
	int x, y;
};

queue<node> q;
char map[105][105];
bool mm[105][105];
int sum;
int dr[][2] = { 1,0,0,1,-1,0,0,-1,1,1,-1,-1,1,-1,-1,1};

void bf(int m, int n)
{
	while (!q.empty())
	{
		node tt = q.front();
		q.pop();
		for (int i = 0; i < 8; i++)
		{
			node t = { tt.x + dr[i][0], tt.y + dr[i][1] };
            if (map[t.x][t.y] == '1')if(!mm[t.x][t.y])
            {
                mm[t.x][t.y] =  true;
                q.push(t); // 缺少这一行
            }
		}
	}
}
int main()
{
	int n, m;
	while (cin >> m >> n)
	{
		memset(mm, false, sizeof(mm));
        memset(map, 0, sizeof(map));
        sum = 0;
        
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				cin >> map[i][j];
			}
		}
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (map[i][j] == '1') if(!mm[i][j])
				{
                    node s = { i,j };
                    mm[i][j] = true; // 需要先于下面的一行调换位置
					q.push(s);
                    bf(m, n);
                    sum++;
				}
			}
        }
        
		cout << sum << endl;
	}
}
