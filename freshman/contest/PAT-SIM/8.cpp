#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n; cin >> n;
	while (n--) {
		int d, hh, mm; scanf("%d %d:%d", &d, &hh, &mm);
	
		if (d==0) {
			printf("%d %02d:%02d\n", d, hh, mm);
			continue;
		}
		
		int tot = (d-1)*24*60+hh*60+mm; tot /= 2;
		
		int fd = tot / (24*60); tot -= fd*(24*60);
		int fh = tot / 60; tot -= fh*60;
		int fm = tot;
		
		printf("%d %02d:%02d\n", fd+1, fh, fm);
	}
}
