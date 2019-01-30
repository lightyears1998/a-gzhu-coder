#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 10010;

struct
{
    int cur, todo;
    vector<int> sub;
} node[MAXN];

queue<int> que;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    long long cnt; cin >> cnt;
    for (int i = 2; i <= cnt; i++)
    {
        int tmp; cin >> tmp;
        node[tmp].sub.push_back(i);
    }

    for (int i = 1; i <= cnt; i++)
    {
        int tmp; cin >> tmp;
        node[i].todo = tmp;
    }

    cnt = 0;
    que.push(1);

    while (!que.empty())
    {
        int top = que.front();
        que.pop();

        if (node[top].cur != node[top].todo) cnt++;
        int size = node[top].sub.size();
        for (int i = 0; i < size; i++)
        {
            node[node[top].sub[i]].cur = node[top].todo;
            que.push(node[top].sub[i]);
        }
    }

    cout << cnt << endl;
}
