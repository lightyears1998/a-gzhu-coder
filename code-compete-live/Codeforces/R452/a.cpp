#include <iostream>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
	int alone = 0, pair = 0;
	int cnt; cin >> cnt;
	while (cnt--)
	{
		int tmp; cin >> tmp;
		if (tmp == 1) alone++;
		else pair++;
	}
	
	int tot = 0;
	tot += min(alone, pair);
	alone -= tot;
	tot += alone / 3;
	
	cout << tot << endl;
}

