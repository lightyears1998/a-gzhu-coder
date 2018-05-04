#include <bits/stdc++.h>
using namespace std;

const char peo[4][4] {".O.", "/|\\", "(.)"};

int h, w;
bool take[150][150];
char pic[150][150];

void dye(int x, int y)
{
	for (int i=0; i<3; ++i) {
		for (int j=0; j<3; ++j) {
			if (peo[i][j] == pic[x+i][y+j]) {
				take[x+i][y+j] = true;
			}
		}
	}
}

int check()
{
	int ans = 0;
	for (int i=5; i<=h+4; ++i) {
		for (int j=5; j<=w+4; ++j) {
			if (take[i][j]) continue;
			if (pic[i][j] == 'O') {
				++ans; dye(i, j-1);
			}
			if (pic[i][j] == '/') {
				++ans; dye(i-1, j);
			}
			if (pic[i][j] == '|') {
				++ans; dye(i-1, j-1);
			}
			if (pic[i][j] == '\\') {
				++ans; dye(i-1, j-2);
			}
			if (pic[i][j] == '(') {
				++ans; dye(i-2, j);
			}
			if (pic[i][j] == ')') {
				++ans; dye(i-2, j-2);
			}
		}
	}
	return ans;
}

int main()
{
	int t; scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &h, &w);
		memset(take, 0, sizeof(take));
		memset(pic, 0, sizeof(pic));
		for (int i=5; i<=h+4; ++i) {
			for (int j=5; j<=w+4; ++j) {
				scanf(" %c", &pic[i][j]);
			}
		}
		printf("%d\n", check());
	}
}
