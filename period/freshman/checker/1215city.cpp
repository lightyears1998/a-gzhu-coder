/*

测试用数据

5
1 10 100
1 20 100
2 10 100
2 10 300
2 20 200

期望输出

1 20 100
1 10 100
2 20 200
2 10 100
2 10 300

*/

#include <cmath>
#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct P
{
	long long a;
	long long b;
	long long c;
};

bool one(P x, P y)
{
	return x.a < y.a;
}

bool two(P x, P y)
{
	if (x.a == y.a) return x.b > y.b;
    // 默认返回true，相当于如果x.a不等于y.a，即返回true。
    // 也就是说，对于a属性不相等的动物x和y，x在排序中优先于位置（即使x的A属性比y大）。
}

bool three(P x, P y)
{
	if (x.a == y.a && x.b == y.b) return x.c < y.c;
    // 同理
}

int main()
{
	P s[105];
	long long n;
	scanf("%lld", &n);

    for (int i = 0;i<n;i++)
	{
		scanf("%lld%lld%lld", &s[i].a, &s[i].b, &s[i].c);
	}

    // 分别输出三次比较中得出的结果
	sort(s, s + n, one);
    for (int i = 0; i < n; i++)
	{
		printf("%lld %lld %lld\n", s[i].a, s[i].b, s[i].c);
	}
    cout << endl;

	sort(s, s + n, two);
    for (int i = 0; i < n; i++)
	{
		printf("%lld %lld %lld\n", s[i].a, s[i].b, s[i].c);
	}
    cout << endl;

	sort(s, s + n, three);
    for (int i = 0; i < n; i++)
	{
		printf("%lld %lld %lld\n", s[i].a, s[i].b, s[i].c);
	}
}
