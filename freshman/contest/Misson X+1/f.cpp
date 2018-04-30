#include <bits/stdc++.h>
using namespace std;

const int turn[][24] {
	{ 0,16, 2, 8, 4, 1, 7,15,23, 9,10,11,12, 3, 6,14,21,17,18,19,20, 5,22,13},
	{ 0, 5, 2,13, 4,21,14, 6, 3, 9,10,11,12,23,15, 7, 1,17,18,19,20,16,22, 8},	
	{ 2, 0, 3, 1, 6, 7, 8, 9,10,11, 4, 5,12,13,14,15,16,17,18,19,20,21,22,23},
	{ 1, 3, 0, 2,10,11, 4, 5, 6, 7, 8, 9,12,13,14,15,16,17,18,19,20,21,22,23},
	{ 0, 1, 6,14, 5,13,21, 7, 8, 9,10, 3, 4,12,20,15,16,17,18, 2,11,19,22,23}, 
	{ 0, 1,19,11,12, 4, 2, 7, 8, 9,10,20,13, 5, 3,15,16,17,18,21,14, 6,22,23},
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23},
};

const int mp[24] {
	 0, 1, 2, 3,
	 4, 5,12,13, 
	 6, 7,14,15, 
	 8, 9,16,17,
	10,11,18,19,
	20,21,22,23,
};

int ans;
char face[24];

bool check(char *cur) {
	for (int i=0; i<24; ++i) {
		if (cur[mp[i]] != cur[mp[i/4*4]]) return false;
	}
	return true;
}

void search(char *cur, int step)
{
	if (check(cur)) {
		ans = min(ans, step);
	}
	if (step >= ans) return;
	
	for (int i=0; i<6; ++i) {
		char nxt[24];
		for (int j=0; j<24; ++j) {
			nxt[j] = cur[turn[i][j]];
		}
		search(nxt, step+1);
	}
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	#endif
	
	int t; scanf("%d", &t);
	while (t--) {
		ans = 6;
		for (int i=0; i<24; ++i) {
			scanf(" %c", &face[i]);
		}
		
		search(face, 0);
		printf("%d\n", ans);
	}
}
