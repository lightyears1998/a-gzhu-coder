#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int INF = 0x3F3F3F3F;

int best = INF;
set<LL> sqr; 

LL assemble(string n)
{
	LL rslt = 0;
	
	bool other = false;
	for (unsigned i=0; i<n.size(); ++i) {
		if (n[i] == ' ') continue;
		else {
			if (n[i] == '0') {
				if (!other) return 0;
			}
			else other = true;
			
			rslt = rslt*10 + n[i]-'0';
		}
	}
	return rslt;
}

void search(string n, int pos = -1, int step = 0)
{
	if (step>=best) return;
	
	LL rslt = assemble(n);
	
	if (sqr.find(rslt) != sqr.end()) {
		best = min(best, step);
		return;
	}
	
	if (pos+1 == int(n.size())) return;
	
	string nxt(n); nxt[pos+1] = ' ';
	search(n, pos+1, step);
	search(nxt, pos+1, step+1);
}

int main()
{
	for (LL i=1; i*i<=2e9; ++i) {
		sqr.insert(i*i);
	}
	
	string n; cin >> n;
	search(n);
	if (best == INF) {
		cout << -1 << endl;
	}
	else cout << best << endl;
}
