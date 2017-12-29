#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct circle
{
    long double x;
    long double dis;
};

vector<circle> v;

int main()
{
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false);
    cout.flags(cout.fixed);
    cout.precision(11);

    int n, r; cin >> n >> r;
    for (int i = 0; i < n; i++)
    {
        long double x; cin >> x;
        circle c = {x, (long double)r}; v.push_back(c);

        for (int j = 0; j < i; j++)
        {
            long double diff = abs(v[i].x - v[j].x);
            if (2 * r < diff) continue;
            long double idle = sqrt(4 * r * r - diff * diff);
            v[i].dis = max(idle + v[j].dis, v[i].dis);
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (i) cout << " ";
        cout << v[i].dis;
    }
}
