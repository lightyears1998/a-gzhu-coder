/* 汉诺塔“动画” */
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

void show();
void move(int, int, int, int);

struct Tower
{
    vector<int> disks;
    char name;

    Tower(char name) 
    {
        this->name = name;
    }

    operator >> (Tower &oth)            // 不能写成(Tower oth)
    {
        int tmp = disks.back();
        oth.disks.push_back(tmp);
        disks.pop_back();

        cout << name << " --> " << oth.name << endl;
        show();
    }
} towers[] = {Tower('A'), Tower('B'), Tower('C')};

void show()
{
    for (int i = 0; i < 3; i++)
    {
        cout << towers[i].name << ": ";
        vector<int>::iterator it = towers[i].disks.begin();
        while (it != towers[i].disks.end())
        {
            cout << *it << " ";
            it++;
        }
        cout << endl;
    }
    cout << endl;
}

void move(int num, int src, int ast, int dst)
{
    if (num == 1) towers[src] >> towers[dst];
    else 
    {
        move(num - 1, src, dst, ast);
        move(1, src, ast, dst);
        move(num - 1, ast, src, dst);
    }
}

int main()
{
    int n;
    printf("How many disks you want me to display?\n");
    cin >> n;

    // 建塔
    for (int i = n; i > 0; i--)
    {
        towers[0].disks.push_back(i);
    }

    show();

    move(n, 0, 1, 2);

    system("pause");
}
