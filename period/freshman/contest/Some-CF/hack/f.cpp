#include <bits/stdc++.h>
using namespace std;

int conver(int num, int base)
{
	if (base == 10) return num;
	
	int ret = 0, w = 1;
	while (num) {
		ret += (num%10)*w;
		w *= base, num /= 10;
	}
	return ret;
}

int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		int ans = 0;
		for (int i=0; i<n; ++i)
		{
			int num, base;
			scanf("%d(%d)", &num, &base);
			ans += conver(num, base);
		}
		printf("%d\n", ans);
	}
}
