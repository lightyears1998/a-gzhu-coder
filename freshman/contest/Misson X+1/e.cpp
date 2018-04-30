#include <bits/stdc++.h>
using namespace std;

const int maxN = 101010;

set<int> st;
int cnt[maxN], mx;

int main()
{
	int n;
	while (scanf("%d", &n) == 1)
	{
		mx = 0; st.clear();
		memset(cnt, 0, sizeof(cnt)); 
		
		for (int i=0; i<n; ++i) {
			int k; scanf("%d", &k);
			mx = max(mx, k);
			st.insert(k); cnt[k]++;
		}
		
		double avg = n/2.0;
		vector<int> pun;
		for (int i=1; i<=mx; ++i) {
			if (cnt[i] > avg) pun.push_back(i);
		}
		if (pun.size()) {
			for (unsigned i=0; i<pun.size(); ++i) {
				if (i) putchar(' ');
				printf("%d", pun[i]);
			} 
			printf("\n");
		}
		else puts("-1");
	}
}
