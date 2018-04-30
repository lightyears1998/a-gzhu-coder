#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3F3F3F3F;

int n, m, cl, ce, v;

vector<int> stairs, elevators;

int search(int x1, int y1, int x2, int y2) 
{
	if (x1 == x2) return abs(y1 - y2);
	int cst1 = lower_bound(stairs.begin(), stairs.end(), y1)-stairs.begin();
	{
		int mn = INF;
		if (cst1 != int(stairs.size())) mn = min(mn, abs(y1-stairs[cst1])+abs(y2-stairs[cst1]));
		if (cst1-1>=0) mn = min(mn, abs(y1-stairs[cst1-1])+abs(y2-stairs[cst1-1]));
		cst1 = mn+abs(x1-x2);
	}
	int cst2 = lower_bound(elevators.begin(), elevators.end(), y1)-elevators.begin();
	{
		int mn = INF;
		if (cst2 != int(elevators.size())) mn = min(mn, abs(y1-elevators[cst2])+abs(y2-elevators[cst2]));
		if (cst2-1>=0) mn = min(mn, abs(y1-elevators[cst2-1])+abs(y2-elevators[cst2-1]));
		cst2 = mn+(abs(x1-x2)-1)/v+1;
	}
	return min(cst1, cst2);	
}

int main()
{
	cin >> n >> m >> cl >> ce >> v;
	for (int i=0; i<cl; ++i) {
		int cur; cin >> cur;
		stairs.push_back(cur);
	}	
	for (int j=0; j<ce; ++j) {
		int cur; cin >> cur;
		elevators.push_back(cur); 
	}
	
	int q; cin >> q;
	while (q--) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		cout << search(x1, y1, x2, y2) << endl;
	}
}
