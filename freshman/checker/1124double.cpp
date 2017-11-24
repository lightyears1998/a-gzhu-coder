/* GZHUOJ1374 口袋妖怪对战 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class dazhan
{
public:
    string name, x;
    int h, a, d, s, p;
    dazhan() {
        cin >> name >> h >> a >> d >> s >> p >> x;
    }
    int get_injury(int fy) {
        int shanghai;
        if (x == "x1")
            shanghai = (a * 42 * p / fy / 50 + 2) * 1;
        if(x == "x2")
            shanghai = (a * 42 * p / fy / 50 + 2) * 2;
        if(x == "x4")
            shanghai = (a * 42 * p / fy / 50 + 2) * 4;
//!     if (x == "x1/0")
        if (x == "x0")
            shanghai = 0;
        if(x == "x1/2")
            shanghai = (a * 42 * p / fy / 50 + 2) /2;
        if(x == "x1/4")
            shanghai = (a * 42 * p / fy / 50 + 2)/4;
        if (shanghai <= 0)
            shanghai = 1;
        return shanghai;
    }
    void victory(int k)    {
        cout << "Round #" << k << " : " << name << " win!" << endl;
    }
};

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int k = 0;
    while (n--)
    {
        dazhan one, two;
        int a1 = one.get_injury(two.d);
        int a2 = two.get_injury(one.d);
        while (1)
        {
            if (one.s >= two.s)
            {
                two.h = two.h - a1;
                if (two.h <= 0)
                {
                    one.victory(++k);
                        break;
                }
                else
                {
                    one.h -= a2;
                    if (one.h <= 0)
                    {
                        two.victory(++k);
                        break;
                    }
                }
            }
            else
            {
                one.h -= a2;
                if (one.h <= 0)
                {
                    two.victory(++k);
                    break;
                }
                else
                {
                    two.h -= a1;
                    if (two.h <= 0)
                    {
                        one.victory(++k);
                        break;
                    }
                }
            }
        }
    }
}
