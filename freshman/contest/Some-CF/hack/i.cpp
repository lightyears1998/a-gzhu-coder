#include <bits/stdc++.h>
using namespace std;

int main()
{
	int kase = 0;
	
	int n; while (scanf("%d", &n) == 1)
	{
		if (kase) putchar('\n');
		++kase;
		
		int sum = 0;
		while (n) {
			int q = n%10;
			if (q % 2 == 0) sum += q;
			n /= 10;
		}
		printf("%d\n", sum);
	}
}
