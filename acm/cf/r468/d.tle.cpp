#include <bits/stdc++.h>
using namespace std;

struct
{
	int val, fa;
	bool nxt;
} node[100100];

int cnt;
vector<int> son[100100];

void accquire(int i)
{
	cnt -= (node[i].val/2)*2;
	node[i].val %= 2;
	node[node[i].fa].val += node[i].val;
	if (i == 1) cnt -= node[i].val;
	node[i].val = 0;
	
	unsigned tot = 0;
	for (unsigned j = 0; j < son[i].size(); ++j)
	{
		if (node[son[i][j]].nxt) accquire(son[i][j]);
		else ++tot;
	}
	if (node[i].val == 0 && tot == son[i].size()) node[i].nxt = false;
}

int main()
{
	int n; scanf("%d", &n);
	
	node[1].val = 1; 
	node[1].fa = 0; node[1].nxt = true;
	for (int i = 2; i <= n; ++i)
	{
		int t; scanf("%d", &t);
		son[t].push_back(i);
		node[i].fa = t; 
		node[i].val = 1; node[i].nxt = true;
	}
	
	cnt = n;
	while (cnt)
	{
		accquire(1);
	}
	printf("%d\n", node[0].val);
}
