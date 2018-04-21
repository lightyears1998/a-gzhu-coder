#include <cstdio>
#include <algorithm>
#include <queue> 
#include <iostream>
using namespace std;

const int maxN = 10010;

struct product {
	int price, deadline;
	
	bool operator <(const product &d) const {
		return price < d.price;
	}
} p[maxN];

bool cmp(const product &a, const product &b) {
	return a.deadline < b.deadline;
}

priority_queue<product> que;

int main()
{
	int n; 
	while (scanf("%d", &n) == 1)
	{
		int tailing = 0;
		while (que.size()) que.pop();
		
		for (int i=0; i<n; ++i) {
			scanf("%d%d", &p[i].price, &p[i].deadline);
			tailing = max(tailing, p[i].deadline);
		}
		sort(p, p+n, cmp);
		
		int profit = 0;
		for (int t=tailing, j=n-1; t>0; ) {
			while (j>=0 && p[j].deadline==t) 
				que.push(p[j]), --j;
			
			if (que.size()) {
				profit += que.top().price;
				que.pop();
			} 
			--t;
		}
		
		printf("%d\n", profit);
	}
}

