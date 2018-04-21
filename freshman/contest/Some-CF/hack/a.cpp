#include <bits/stdc++.h>
using namespace std;

int conver(int n, int base)
{
	int ret = 0;
	while (n) {
		ret += n%base;
		n /= base;
	}
	return ret;
}

int main()
{
	int n; 
	while (scanf("%d", &n) == 1 && n) {
		bool flag = true;
		
		int a = conver(n, 10);
		int b = conver(n, 12);
		int c = conver(n, 16);
		flag = (a==b) && (b==c);
		
		printf((flag?"%d is a Sky Number.\n":"%d is not a Sky Number.\n"), n);
	}
} 
