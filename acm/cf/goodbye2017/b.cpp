#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

// next_permutation()函数
// 手册 http://www.cplusplus.com/reference/algorithm/next_permutation/
// 博客 http://www.cnblogs.com/devymex/archive/2010/08/17/1801122.html
// next_permutation()函数返回true/false，自带回归功能

string map[50];
vector<int> p{0, 1, 2, 3};
int dir[][2] = {0, -1, -1, 0, 1, 0, 0, 1};

int main()
{
#ifdef LOCAL
    assert(freopen("test.in", "r", stdin));
#endif
    int n, m; cin >> n >> m;
    int sx, sy;
    for (int i = 0; i < n; ++i)
    {
        cin >> map[i];
        for (int j = 0; j < m; ++j)
        {
            if (map[i][j] == 'S')
            {
                sx = i, sy = j;
            }
        }
    }
    string w; cin >> w;
    int ans = 0;
    do {
        int x = sx, y = sy;
        bool fail = false;
        for (auto c : w)
        {
            x += dir[p[c - '0']][0];
            y += dir[p[c - '0']][1];
            if (x < 0 || x >= n || y < 0 || y >= m || map[x][y] == '#')
            {
                fail = true; break;
            }
            if (map[x][y] == 'E') break;
        }
        if (!fail && map[x][y] == 'E') ++ans;
    } while(next_permutation(p.begin(), p.end()));

    cout << ans << endl;
}
