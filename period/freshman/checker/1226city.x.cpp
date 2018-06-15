// 尝试使用自己的算法，TLE，数据量太大
// 改良，使用优先队列而不是遍历数组
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 10000010 * 2;
int cnt[MAX];

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++)
        {
            int begin, end; scanf("%d%d", &begin, &end);
            cnt[begin * 2]++; cnt[end * 2 + 1]--;
        }
        int tot = 0;
        for (int in = false, cur = 0, i = 0; i < MAX; i++)
        {
            cur += cnt[i];
            if (in && cur == 0)
            {
                tot++;
                in = false;
            }
            if (!in && cur != 0) in = true;
        }
        printf("%d\n", tot);

        int head = -1, tail = -1;
        for (int in = false, cur = 0, i = 0; i < MAX; i++)
        {
            cur += cnt[i];
            if (in && cur == 0)
            {
                tail = i / 2; in = false;
                printf("%d %d\n", head, tail);
            }
            if (!in && cur != 0)
            {
                in = true;
                head = i / 2;
            }
        }
    }
}
