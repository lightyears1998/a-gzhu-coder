#include <cstdio>
#include <iostream>
#include <set>
using namespace std;

int board[9][9];
set<int> candidate[9][9];

void init();
void delete_candidate();
void flush_board();

int main()
{
    freopen("suduku.out", "w", stdout);

    init();

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '0')
            {
                delete_candidate(i, j);
            }
        }
    }

    flush_board();

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (j) cout << " ";
            cout << board[i][j];
        }
        cout << endl;
    }
}

void init() {
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 1; k <= 9; k++)
            {
                candidate[i][j].insert(k);
            }
        }
    }
}

void delete_candidate(int i, int j)
{
    int cur = candidate[i][j].
}

void flush_board()
{

}
