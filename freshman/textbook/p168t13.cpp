#include <iostream>
#include <string>
using namespace std;

int serial[] = {1, 2, 3, 4, 5, 6};
string name[] = {"Kehao", "Shanxin", "Lightyears", "Guoyun", "Bill", "Zekar"};

int main()
{
    int id;

    cout << "Please give me a serial numeber: " << endl;
    cin >> id;
    {
        int i;
        for (i = 0; i < 6; i++) if(id == serial[i])
        {
            cout << name[i] << endl;
            break;
        }
        if (i == 6) cout << "I can't find a name with the given serial." << endl;
    }
}
