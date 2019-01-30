#include <bits/stdc++.h>
using namespace std;

int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
string msg[4] = {"move-right", "move-left", "move-down", "move-up"};

int main()
{
	freopen("output-4-path.txt", "r", stdin);
	freopen("4.maker.cpp", "w", stdout);
	
	int a, b, c, d; 
	
	cin >> a >> b;
	while (cin >> c >> d)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (c-a==dir[i][0] && d-b==dir[i][1])
				cout << "cout << \"" << msg[i] << "\" << endl;" << endl;
		}
		a = c, b = d;
	}
}

