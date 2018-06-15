#include <bits/stdc++.h>
using namespace std;

// 1. 至少出现 (N + 1) / 2次
// 2. 容器记得清空哦

map<int, int> m;

int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		m.clear();

		int x;
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &x);
			m[x]++;
		}

		int cnt = 0;
		for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
		{
			if ((*it).second >= (n + 1) / 2)
				printf((cnt ? " %d" : "%d"), (*it).first), ++cnt;
		}
		printf("\n");
	}
}
