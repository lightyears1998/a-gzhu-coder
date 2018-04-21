#include <bits/stdc++.h>
using namespace std;

const int maxN = 10100;

struct node {
	int id, money, cnt;
	bool operator <(const node &n) const {
		if (money != n.money) return money>n.money;
		if (cnt != n.cnt) return cnt>n.cnt;
		return id<n.id;
	}
} peo[maxN];

int main()
{
	int n; cin >> n;
	for (int i=1; i<=n; ++i)
	{
		peo[i].id = i;
		
		int k; cin >> k;
		while (k--) {
			int id, p; cin >> id >> p;
			peo[id].money += p;
			peo[id].cnt++;
			peo[i].money -= p;
		}
	}
	sort(peo+1, peo+1+n);
	
	for (int i=1; i<=n; ++i) {
		printf("%d %.2f\n", peo[i].id, (double)peo[i].money/100);
	}
}
