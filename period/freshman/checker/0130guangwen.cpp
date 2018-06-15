#include<iostream>
#include<cstdio>
#include<cmath> 
using namespace std;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif
	
	int n; cin >> n;
	char ch[200][200];

	while (n--)
	{
		int m; cin >> m;
		int t = m;
		if (m == 1) cout << "6" << endl;
		else if (m == 2) cout << "66" << endl << " 6" << endl;
		else
		{
			int mm = m / 2;
			for (int i = 1;i <= mm;i++)
			{
				if (i % 2 == 1)
				{
					for (int h = i;h <= m;h++)
					{
						for (int v = i;v <= m;v++)
						{
							if (m - i + 1 == 2)
							{
								if (h == i) ch[h][v] = '6';
								else if (h == m)
								{
									if (v == i) ch[h][v] = ' ';
									else ch[h][v] = '6';
								}
							}
							else
							{
								if (h == i || h == m) ch[h][v] = '6';
								else if (h == i + 1)
								{
									if (v == m) ch[h][v] = '6';
									else ch[h][v] = ' ';
								}
								else if (h>i + 1 && h<m)
								{
									if (v == i || v == m) ch[h][v] = '6';
									else ch[h][v] = ' ';
								}
							}
						}
					}
					m -= 1;
				}
				else
				{
					for (int h = i;h <= m;h++)
					{
						for (int v = i;v <= m;v++)
						{
							if (h == i + 1 && v == i) ch[h][v] = '6';
						}
					}
					m -= 1;
				}
			}
		}

		// 修正特例情况 
		if (t % 4 == 0) {
			ch[t/2+1][t/2] = ' ';
		} 
		
		if (t % 4 == 1) {
			ch[t/2+1][t/2+1] = '6';
		} 
	
		// 修正特例情况 
		if (t != 1 && t != 2) for (int i = 1; i <= t;i++)
		{
			for (int k = 1; k <= t;k++)
			{
				cout << ch[i][k];
			}
			cout << endl;
		}
	}
}

