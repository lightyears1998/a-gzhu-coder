#include <iostream>
using namespace std;
int main()
{
	int a1, a2, b1, b2, c1, c2, res1, res2;
	while (cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2)
	{
        // 小羊 小黄
		res1 = c1; res2 = c2;
		if (a1 <= b2 && a2 > b1)
        {
            cout << "小黄: " << res2 << endl;
            continue;
        }
		if (a2 <= b1 && a1 > b2)
        {
            cout << "小羊: " << res1 << endl;
            continue;
        }
// 😊
        if (a2 - b1 <= 0 && a1 - b2 <= 0)
        {
            cout << '0' << endl;
            continue;
        }
// 😀
		if (a1 > b2 && a2 > b1)
		{
			while (res1 > 0 && res2 > 0)
			{
				res1 = res1 - (a2 - b1);
				res2 = res2 - (a1 - b2);
			}
			if (res1 <= 0 && res2 <= 0) cout << '0' << endl;
			else
			{
				if (res1 > res2) cout << "小羊: " << res1 << endl;
				else cout << "小黄: " << res2 << endl;
			}
		}
		else cout << '0' << endl;
	}
}
