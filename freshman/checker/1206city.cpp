/* Wrong Answer - 用指针排序之后不能得到正确答案，未解之谜，算法存在问题吗？= */

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

bool cmp(long long (*lhs)[2], long long (*rhs)[2])
{
	if ((*lhs)[0] != (*rhs)[0]) return (*lhs)[0] < (*rhs)[0];
	else return (*lhs)[1] < (*rhs)[1];
}

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

		long long (* ps[6000])[2];
		for (int i = 0; i < n; i++) ps[i] = &s[i];
		sort(ps, ps + n, cmp);

		cout << "--------" << endl;
		for (int i = 0;i < n; i++)
		{
			for (int j = 0;j < 2; j++)
			{
				cout << (*ps[i])[j] << " ";
			}
			cout << endl;
		}
		cout << "--------" << endl;

		long long a, b, max = 0;
		for (int i = 0; i < n; i++)
		{
			a = (*ps[i])[0];
			b = (*ps[i])[1];
			for (int j = 0; j < n; j++)
			{
				if ((*ps[j])[0] < a && a <= (*ps[j])[1] && (*ps[j])[1] <= b) a = (*ps[j])[0];
				if ((*ps[j])[1] > b && a <= (*ps[j])[0] && (*ps[j])[0] <= b) b = (*ps[j])[1];
			}
			max = (b - a) > max ? (b - a) : max;
		}

		long long x = 0, y = 0;
		long long h, m;
		long long max1 = 0;
		for (int i = 0; i < n; i++)
		{
			h = (*ps[i])[0];
			m = (*ps[i])[1];
			for (int j = 0; j < n; j++)
			{
				if ((*ps[j])[0] < h && h <= (*ps[j])[1] && (*ps[j])[1] <= m) h = (*ps[j])[0];
				if ((*ps[j])[1] > m && h <= (*ps[j])[0] && (*ps[j])[0] <= m) m = (*ps[j])[1];
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
