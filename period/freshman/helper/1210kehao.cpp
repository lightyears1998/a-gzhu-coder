/* 异或最大值 */
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n; // 每组数据的个数
    while (cin >> n)
    {
        int * num = new int[n]; // 动态分配内存
        for (int i = 0; i < n; i++) cin >> num[i];

        int mx = 0;
        for (int i = 0; i < n; i++)
        {
            int cur = num[i];
            for (int j = i + 1; j < n; j++)
            {
                cur = cur ^ num[j];
                mx = max(cur, mx);
            }
        }

        cout << mx << endl;
        delete num;
    }
}
