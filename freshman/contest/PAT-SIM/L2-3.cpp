#include <bits/stdc++.h>
using namespace std;

const int maxN = 10100;

int n;
int fa[maxN];

struct peo
{
	int member;
	int house;
	double area;
} node[maxN];

int find(int x)
{
	return fa[x]==x ? fa[x] : find(fa[x]);
}

void merge(int a, int b) {
	if (a==-1 || b == -1) return;
	a = find(a), b = find(b);
	if (a == b) return;
	if (a > b) swap(a, b);
	fa[b] = a;
}

int main()
{
	cin >> n;
	iota(fa, fa+1+n, 0);
	for (int i=0; i<maxN; ++i) {
		peo[i].member = 1;
	}
	
	for (int i=0; i<n; ++i) {
		int id, fid, mid, k; cin >> id >> fid >> mid >> k;
		while (k--) {
			int s; cin >> s;
			merge(id, s);
		}
		merge(id, fid); merge(id, mid);
	}
	
	
}
