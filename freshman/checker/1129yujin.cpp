#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

struct yxt
{
	int m;
	int d;
	char s[10];
	int t;
} a[1005];

bool cmp(yxt a, yxt b)
{
	if(a.m!=b.m)              return a.m < b.m;
	else if(a.d!=b.d)         return a.d < b.d;
	else if(a.t!=b.t)         return a.t < b.t;
}

int main()
{
	int n;
	while(cin >> n)
	{

		for(int i = 0; i < n; i++)
		{
		   cin >> a[i].m >> a[i].d >> a[i].s;
           // 注意到a[i].s是char数组，不能直接用 == 来比较
		   if(strcmp(a[i].s, "LIVE") == 0)            a[i].t=1;
		   else if(strcmp(a[i].s, "Practice") == 0)   a[i].t=2;
		   else if(strcmp(a[i].s, "Game") == 0)       a[i].t=3;
	    }

		sort(a, a + n, cmp);

	    for(int i = 0; i < n; i++)
		      cout << a[i].m << ' ' << a[i].d << ' ' << a[i].s << endl;
	    cout << endl;
	}
}
