#include <iostream>
using namespace std;

const double PI = 3.141592;

int main()
{
    cout.flags(cout.fixed);
    cout.precision(5); // 忘记几位小数了

    int t; cin >> t;
    while (t--)
    {
        int n; cin >> n;
        double mx = 0;
        while (n--)
        {
            char ch; cin >> ch;
            double tmp;
            switch (ch)
             {
                case 'R':
                {
                    int a, b; cin >> a >> b;
                    tmp = a * b;
                    break;
                }
                case 'T':
                {
                    int a, b; cin >> a >> b;
                    tmp = (double)a * b / 2;
                    break;
                }
                case 'C':
                {
                    int r; cin >> r;
                    tmp = PI * r * r;
                }
            }
            if (tmp > mx) mx = tmp;
        }
        cout << mx << endl;
    }
}
