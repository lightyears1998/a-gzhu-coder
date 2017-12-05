#include <cstdio>
using namespace std;

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        int size = 2 * n + 1;
        int mid = (size + 1 ) / 2;
        for (int i = 1; i <= size; i++)
        {
            for (int j = 1; j <= size; j++)
            {
                if (i < mid) {
                    if (j == mid) printf("*");
                    else printf(" ");
                }
                if (i == mid) printf("*");
                if (i > mid) {
                    if (j == mid - (i - mid) || j == mid + (i - mid))
                        printf("*");
                    else printf(" ");
                }
            }
            printf("\n");
        }
    }
}
