#include <bits/stdc++.h>
using namespace std;

bool check(int hh, int mm)
{
	if (hh % 10 == 7) return true;
	if (hh / 10 == 7) return true;
	if (mm % 10 == 7) return true;
	if (mm / 10 == 7) return true;
	return false; 
}

int main()
{
	int x, hh, mm; cin >> x >> hh >> mm;
	int tot = 0;
	while (!check(hh, mm))
	{
		mm -= x;
		if (mm < 0) mm += 60, hh -= 1;
		if (hh < 0) hh = 23;
		tot++;
	}
	cout << tot << endl;
} 
