// http://120.78.162.102/problem.php?cid=1332&pid=7
// 错误数据：
// 5 0 2 5 6 6 7 3 5 1 4
// 期望 1 0 7
// 结果 1 0 6
#include<cmath>
#include<string>
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	long long s[6000][2];
	int	n;
	while (scanf("%d", &n) == 1)
	{
		for (int i = 0;i<n;i++)
		{
			for (int j = 0;j<2;j++)
			{
				scanf("%lld", &s[i][j]);
			}
		}
		long long a1, b1, work = 1, sum = 0, x[300], y[300], ji = 0;
		long long a, b;
		for (int i = 0; i < n; i++)
		{
			a = s[i][0];
			b = s[i][1];
			for (int j = 0;j<n;j++)
			{
				if (s[j][0]<a&&a <= s[j][1] && s[j][1] <= b)a = s[j][0];
				if (s[j][1]>b&&a <= s[j][0] && s[j][0] <= b)b = s[j][1];
				if (s[j][0]<a&&s[j][1]>b)
				{
					a = s[j][0]; b = s[j][1];
				}
			}
			for (int j = n - 1; j >= 0; j--)
			{
				if (s[j][0]<a&&a <= s[j][1] && s[j][1] <= b)a = s[j][0];
				if (s[j][1]>b&&a <= s[j][0] && s[j][0] <= b)b = s[j][1];
				if (s[j][0]<a&&s[j][1]>b)
				{
					a = s[j][0]; b = s[j][1];
				}
			}
			if (work == 1)
			{
				sum++;
				x[ji] = a; y[ji] = b; ji++;
				a1 = a; b1 = b;
				work = 0;
			}
			else
			{
				if (a1 != a)
				{
					sum++; x[ji] = a; y[ji] = b;
					ji++;
					a1 = a; b1 = b;
				}
			}
		}
		printf("%lld\n", sum);
		sort(x, x + sum);
		sort(y, y + sum);
		for (int i = 0; i < sum; i++)
		{
			printf("%lld %lld\n", x[i], y[i]);
		}
	}
}
