#include <cstdio>
#include <algorithm>
using namespace std;

int num[200000];

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        for (int i = 0; i < n; i++) scanf("%d", &num[i]);
        sort(num, num + n);
        printf("%d\n", num[(n + 1) / 2 - 1]);
    }
}
