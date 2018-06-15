#include <bits/stdc++.h>
using namespace std;

int main()
{
	int a, b; 
	while (scanf("%d%d", &a, &b) == 2 && a && b)
	{
		a *= 100; int cnt = 0;
		for (int i=0; i<100; ++i) if ((a+i)%b==0) {
			printf((cnt++?" %02d":"%02d"), i);
		}
		putchar('\n');
	}
}
