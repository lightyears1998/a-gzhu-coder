#include <bits/stdc++.h>
using namespace std;

int n;

const int maxN = 15;

char one[maxN][maxN], two[maxN][maxN];
int bgn[4][2] {0, 0, 1, 0, 1, 1, 0, 1};

void read(char (*name)[maxN])
{
	for (int i=0; i<n; ++i) {
		for (int j=0; j<n; ++j) {
			cin >> name[i][j];
		}
	}
}

bool search(int idx)
{
	bool same = false;
	
	if (!same) {
		int di = bgn[idx][0] ? -1 : 1;
		int dj = bgn[idx][1] ? -1 : 1;
		
		bool flag = true;
		for (int i1=0, i2=bgn[idx][0]; i1<n; ++i1, i2+=di) {
			for (int j1=0, j2=bgn[idx][1]; j1<n; ++j1, j2+=dj) {
				if (one[i1][j1] != two[i2][j2]) flag = false;
			}
		} 
		same = flag;
	}
	
	if (!same) {
		int di = bgn[idx][0] ? -1 : 1;
		int dj = bgn[idx][1] ? -1 : 1;
		
		bool flag = true;
		for (int i1=0, j2=bgn[idx][1]; i1<n; ++i1, j2+=dj) {
			for (int j1=0, i2=bgn[idx][0]; j1<n; ++j1, i2+=di) {
				if (one[i1][j1] != two[i2][j2]) flag = false;
			}
		}
		same = flag;
	}
	return same;
}

int main()
{
	cin >> n;
	read(one), read(two);
	
	for (int i=0; i<4; ++i) {
		for (int j=0; j<2; ++j) {
			if (bgn[i][j]) bgn[i][j] = n-1;
		}
	}
	
	bool same = false;
	for (int i=0; !same && i<4; ++i) 
		same = search(i);
	
	cout << (same ? "Yes" : "No") << endl;
}
