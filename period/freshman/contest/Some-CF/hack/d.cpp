#include <bits/stdc++.h>
using namespace std;

int main()
{
	long long a, b;
	while (scanf("%lld%lld", &a, &b) == 2)
	{
		long long sum = a + b;
		sum%86==0 ? puts("yes") : puts("no"); 
	}
}
