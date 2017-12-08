/* P168T3 - 将数组元素按非升序排列，输出排序后的每个元素及其在原数组中的下标 */
#include <iostream>
#include <cassert>
#include <ctime>
using namespace std;

void swap(int&, int&);
void sort(int[], int);

int main()
{
    srand(time(0));

    for (int i = 1; i <= 3; i++)
    {
        if (i != 1) cout << endl;
        cout << "Case #" << i << ": " << endl;

        int length = rand() % 10 + 1;
        int * num = new int[length]; assert(num != NULL);
        for (int i = 0; i < length; i++) num[i] = rand();

        sort(num, length);
    }
}

void swap(int &a, int &b)
{
    a = a + b;
    b = a - b;
    a = a - b;
}

void sort(int num[], int length)
{
    int *idx = new int[length]; assert(idx != NULL);
    for (int i = 0; i < length; i++) idx[i] = i;

    // 输出原数组
    for (int i = 0; i < length; i++)
    {
        if (i) cout << " ";
        cout << num[i];
    }
    cout << endl;

    // 排序
    for (int i = 0; i != length - 1; i++)
    {
        for (int j = length - 1; j > i; j--)
        {
            if (num[j] > num[j - 1])
                swap(num[j], num[j - 1]), swap(idx[j], idx[j - 1]);
        }
    }

    // 输出排序后的数组元素及其在原数组中的下标
    for (int i = 0; i < length; i++)
    {
        if (i) cout << " ";
        cout << num[i] << "(" << idx[i] << ")";
    }
    cout << endl;

    delete idx;
}
