#include <bits/stdc++.h>
using namespace std;

const int maxN = 100010;

int head, n;
int key[maxN], nxt[maxN];

bool have[maxN];

int seq[maxN]; int scnt;
int del[maxN]; int dcnt;

int main()
{
	cin >> head >> n;
	for (int i=0; i<n; ++i) {
		int adr; cin >> adr;
		cin >> key[adr] >> nxt[adr];
	}
	
	for (int cur = head; cur != -1; cur = nxt[cur]) {
		if (!have[abs(key[cur])]) {
			seq[scnt++] = cur;
			have[abs(key[cur])] = true;
		}
		else {
			del[dcnt++] = cur;
		}
	}
	
	printf("%05d %d", seq[0], key[seq[0]]);
	for (int i=1; i<scnt; ++i) {
		printf(" %05d\n", seq[i]);
		printf("%05d %d", seq[i], key[seq[i]]);
	}
	printf(" -1\n");
	
	if (dcnt) {
		printf("%05d %d", del[0], key[del[0]]);
		for (int i=1; i<dcnt; ++i) {
			printf(" %05d\n", del[i]);
			printf("%05d %d", del[i], key[del[i]]);
		}
		printf(" -1\n");
	}
}
