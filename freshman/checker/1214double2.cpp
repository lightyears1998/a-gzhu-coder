#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <cctype>
using namespace std;
int main()
{
	string a;
	while (cin >> a)
	{
		int i; int x = 0;
		for (i = 0; i < a.size(); i++)
		{
			if (a[i] >= 'a' && a[i] <= 'z')
				x++;
		}
		if (x == 0)
		{
			for (i = 0; i < a.size(); i++)
			{
				cout << char(a[i] + 32);
			}
			cout << endl;
		}
		else if (x == 1 && a[0] >= 'a' && a[0] <= 'z')
		{
			cout << (char)toupper(a[0]);
			for (int i = 1; i < a.size(); i++)
			{
				cout << (char)tolower(a[i]);
			}
			cout << endl;
		}
		else cout << a << endl;
	}
	return 0;
}
