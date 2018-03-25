#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int cnt;
char map[60][60];
string str;

struct node
{
    int x, y;
} s;

node dir[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void dfs(int i = 1)
{
    if (i == 4)
    {
        node ss = s;
        for (int k = 0; k < str.length(); k++)
        {
            ss.x += dir[str[k] - '0'].x;
            ss.y += dir[str[k] - '0'].y;
            if (map[ss.x][ss.y] == 'E')
            {
                cnt++; break;
            }
            if (map[ss.x][ss.y] == '#') break;
        }
    }
    else
    {
        for (int j = 4; j >= i; j--)
        {
            swap(dir[i - 1], dir[j - 1]);
            dfs(i + 1);
            swap(dir[i - 1], dir[j - 1]);
        }
    }
}

int main()
{
    int n, m; cin >> n >> m;
    memset(map, '#', sizeof(map));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 'S')
            {
                s.x = i; s.y = j;
            }
        }
    }
    cin >> str;

    dfs();

    cout << cnt << endl;
}
