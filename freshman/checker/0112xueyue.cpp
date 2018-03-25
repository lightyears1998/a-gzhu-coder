#include<queue>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
typedef long long ll;

int main()
{
	ll n, o, m, a;
	while (scanf("%lld%lld", &n, &o) == 2)
	{
		priority_queue<ll, vector<ll>, greater<ll> > q[150];	//模拟球袋

		for (int i = 1; i <= n; i++)
		{
			scanf("%lld", &m);
			while (m--)
			{
				scanf("%lld", &a);
				q[i].push(a);
			}
		}

		char ques[10];
		while (o--)	//问题
		{
			ll g;
			scanf("%s", ques);

			if (ques[1] == 'o')	  //pop
			{
				scanf("%lld", &g);

				if (!q[g].empty())
					printf("%lld\n", q[g].top()), q[g].pop();
				else
					printf("-1\n");
			}

			if (ques[1] == 'u')  	  //push
			{
				ll x, y;
				scanf("%lld%lld", &x, &y);
				q[x].push(y);
			}

			if (ques[1] == 'i')	  //mix
			{
				ll x, y;
				scanf("%lld%lld", &x, &y);

				while (!q[y].empty())
				{
					q[x].push(q[y].top());
					q[y].pop();
				}
			}
		}
	}
}
