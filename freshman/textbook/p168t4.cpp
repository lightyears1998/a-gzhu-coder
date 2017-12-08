/* P168T4 - 回文数判定 */
#include <iostream>
using namespace std;

int main()
{
    long long num;
    while (cin >> num)
    {
        long long replica = num, mirror = 0;
        while (replica)
        {
            mirror = mirror * 10 + replica % 10;
            replica /= 10;
        }
        if (mirror == num) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}
