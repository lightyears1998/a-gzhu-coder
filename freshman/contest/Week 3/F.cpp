#include <cstdio>
#include <algorithm>
using namespace std;

const int maxN = 10010;

struct product {
	int price, deadline;
	
	bool operator <(const product &d) const 
	{
		if (deadline != d.deadline) return deadline < d.deadline;
		return price < d.price;
	}
} p[maxN];

int main()
{
	int n; 
	while (scanf("%d", &n) == 1)
	{
		int tailing = 0;
		
		for (int i=0; i<n; ++i) {
			scanf("%d%d", &p[i].price, &p[i].deadline);
			tailing = max(tailing, p[i].deadline);
		}
		sort(p, p+n);
		
		int profit = 0;
		for (int t=tailing, j=n-1; t>0&&j>=0; ) {
			if ()
			
			--t;
		}
		
		printf("%d\n", profit);
	}
}
