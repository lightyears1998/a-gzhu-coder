#include <bits/stdc++.h>
using namespace std;

const int maxN = 101000;

int n;
double grandpower, rate;
double tot;

int great[maxN];

vector<int> son[101000];

void walk(int root, double rt)
{
	if (!son[root].size()) {
		tot += grandpower*rt*great[root];
		return;
	}
	for (unsigned i=0; i<son[root].size(); ++i) {
		walk(son[root][i], rt*rate);
	}
}

int main()
{
	cin >> n >> grandpower >> rate; rate = 1-rate/100;
	
	for (int i=0; i<n; ++i) {
		int k; cin >> k;
		if (k) while (k--) {
			int s; cin >> s;
			son[i].push_back(s);
		}
		else {
			int s; cin >> s;
			great[i] = s;
		}
	}
	
	walk(0, 1);
	
	cout << (long long)tot << endl;
}
