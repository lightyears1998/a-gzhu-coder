/**
 * One of the top hacker's implementation:
 *
 * For each prison, mark him and the furthest prison killed by him.
 * How it works is similar to how prefix-sum works.
 */
#include <iostream>
using namespace std;

int claw[(int)1e6 + 10];
int mark[(int)1e6 + 10];

int main()
{
    cin.tie(0); ios_base::sync_with_stdio(false);
    int n; cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> claw[i];
        mark[max(1, i - claw[i])]--;
        mark[i]++;
    }
    int alive = 0, idle = 0;
    for (int i = 1; i <= n; i++)
    {
        idle += mark[i];
        if (idle >= 0) alive++;
    }
    cout << alive << endl;
}
