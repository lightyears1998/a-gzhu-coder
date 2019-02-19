#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct node
{
    int x, y, cnt;
};

int dir[4][2] = {1, 0, -1, 0, 0, -1, 0, 1};

queue<node> que;
char map[15][15];

int bfs()
{
    while (!que.empty())
    {
        node top = que.front();
        que.pop();
        if (map[top.x][top.y] == 'T') return top.cnt;

        for (int i = 0; i < 4; i++)
        {
            node nxt = {top.x + dir[i][0] , top.y + dir[i][1], top.cnt + 1};
            if (nxt.x >= 0 && nxt.x < 10 && nxt.y >= 0 && nxt.y < 10)
            if (map[nxt.x][nxt.y] != '#')
            que.push(nxt);
        }

        map[top.x][top.y] = '#';
    }
    return -1;
}

int main()
{
    int t; scanf("%d", &t);
    while (t--)
    {
        memset(map, 0, sizeof(map));
        while (!que.empty()) que.pop();

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                scanf(" %c", &map[i][j]);
                if (map[i][j] == 'S')
                {
                    node tmp = {i, j, 0};
                    que.push(tmp);
                    map[i][j] = '#';
                }
            }
        }

        printf("%d\n", bfs());
    }
}
