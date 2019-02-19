#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int n, A, B;

LL head;
vector<LL> pool;

int main()
{
	cin >> n >> A >> B;
	
	cin >> head;
	LL sum = head;
	for (int i=1; i<n; ++i) {
		LL cur; cin >> cur;
		sum += cur;
		pool.push_back(cur);		
	}
	sort(pool.begin(), pool.end());
	
	if ((double(head)*A/sum) >= B) {
		cout << 0 << endl;
	}
	else for (int i=pool.size()-1; i>=0; --i) {
		sum -= pool[i];
		if (double(head)*A/sum >= B) {
			cout << int(pool.size())-i << endl;
			break;
		}
	}
}
