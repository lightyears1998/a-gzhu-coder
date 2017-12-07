/* 挤牛奶 */
/**
 * 最长一人挤奶时间 - 反例
 *
 * 输入：
 * 4
 * 0 50
 * 25 100
 * 120 150
 * 75 125
 * 正确输出：150
 *
**/

/**
 * 最长无人挤奶时间 - 反例
 *
 * 输入：
 * 5
 * 200 300
 * 120 150
 * 75 125
 * 25 100
 * 0 50
 * 正确输出：50
 *
**/
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	long long s[6000][2];
	int	n;
	while (cin >> n)
	{

		for (int i = 0;i < n; i++)
		{
			for (int j = 0;j < 2; j++)
			{
				cin >> s[i][j];
			}
		}

		long long a, b, max = 0;
		for (int i = 0; i < n; i++)
		{
			a = s[i][0];
			b = s[i][1];
			for (int j = 0; j < n; j++)
			{
				if (s[j][0] < a && a <= s[j][1] && s[j][1] <= b) a = s[j][0];
				if (s[j][1] > b && a <= s[j][0] && s[j][0] <= b) b = s[j][1];
			}
			max = (b - a) > max ? (b - a) : max;
		}

		long long x = 0, y = 0;
		long long h, m;
		long long max1 = 0;
		for (int i = 0; i < n; i++)
		{
			h = s[i][0];
			m = s[i][1];
			for (int j = 0; j < n; j++)
			{
				if (s[j][0] < h && h <= s[j][1] && s[j][1] <= m) h = s[j][0];
				if (s[j][1] > m && h <= s[j][0] && s[j][0] <= m) m = s[j][1];
			}

			if (x == 0 && y == 0)
			{
				x = h;
				y = m;
			}
			if (x != h && y != m)
			{
				max1 = (h - y) > max1 ? (h - y) : max1;
				x = h;
				y = m;
			}
		}

		cout << max << ' ' << max1 << endl;
	}

}
