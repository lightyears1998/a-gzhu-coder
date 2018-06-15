/* P122T6 - 将利用循环的程序改写成等效的递归程序 */
#include <iostream>
using namespace std;

void print(int w, bool endline = true)
{
    if (w == 1) {
        if (endline) cout << 1 << endl;
        else cout << 1 << " ";
    }
    else {
        if (endline) {
            print(w - 1);
            print(w - 1, false);
            cout << w << endl;
        }
        else {
            print(w - 1, false);
            cout << w << " ";
        }
    }
}

int main()
{
    print(5);
}
