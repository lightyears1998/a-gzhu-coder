#include <bits/stdc++.h>
using namespace std;

// RMQÏß¶ÎÊ÷

const int maxN = 100100;

struct node {
	int l, r;
	int val; 
} t[maxN]; 
int arr[maxN]; 
 
void build(int x, int arr[], int l, int r)
{
	t[x].l = l, t[x].r = r; 
	if (l==r) 
		t[x].val = arr[l];
	else {
		int mid = (l+r) / 2;
		build(2*x, arr, l, mid);
		build(2*x+1, arr, mid+1, r);
		t[x].val = max(t[x*2].val, t[x*2+1].val); 
	} 
}

void update(int x, int idx, int diff)
{
	if (t[x].l==idx&&t[x].r==idx) 
		t[x].val +=	diff;
	else {
		int mid = (t[x].l+t[x].r)/2;
		if (mid>=idx)
			update(2*x, idx, diff);
		else 
			update(2*x+1, idx, diff); 
		t[x].val = max(t[2*x].val, t[2*x+1].val);
	}
} 

int query(int x, int l, int r)
{
	if (t[x].l==l&&t[x].r==r) 
		return t[x].val;
	else {
		int mid = (t[x].l+t[x].r)/2;
		if (mid>=r)
			return query(2*x, l, r);
		else if (mid<l)
			return query(2*x+1, l, r);
		else 
			return max(query(2*x, l, mid), query(2*x+1, mid+1, r)); 
	} 
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif 
	
	int t; scanf("%d", &t);
	for (int i = 1; i <= t; ++i)
	{
		int n; scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &arr[i]);
		build(1, arr, 1, n);
		
		printf("Case %d:\n", i); 
		while (true)
		{
			char cmd[10]; scanf("%s", cmd);
			if (cmd[0] == 'A') {
				int idx, diff; scanf("%d%d", &idx, &diff);
				update(1, idx, diff); 
			} 
			if (cmd[0] == 'S') {
				int idx, diff; scanf("%d%d", &idx, &diff);
				update(1, idx, -diff); 
			} 
			if (cmd[0] == 'Q') {
				int l, r; scanf("%d%d", &l, &r);
				printf("%d\n", query(1, l, r)); 
			} 
			if (cmd[0] == 'E') break; 
		} 
	} 
} 
