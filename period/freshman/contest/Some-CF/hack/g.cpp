#include <bits/stdc++.h>
using namespace std;

int num[105];

int main()
{
	int n; 
	while (scanf("%d", &n) == 1 && n) {
		for (int i=0; i<n; ++i)	scanf("%d", &num[i]);
		printf("%d\n", *max_element(num, num+n));
	}
}
