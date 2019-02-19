#include <bits/stdc++.h>
using namespace std;

const int maxN = 200200;

int num[maxN];
double sum;

int main()
{
	int n; cin >> n;
	for (int i=1; i<=n; ++i) {
		cin >> num[i];
		sum += num[i];
	}
	
	for (int i=1, tot=0; i<=n; ++i) {
		tot += num[i];
		if (tot >= sum/2) {
			cout << i << endl;
			break;
		}
	}
}
