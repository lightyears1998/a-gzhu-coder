/* 寻找规律：13的阶乘的阶乘取模后为0 */
#include <cstdio>
using namespace std;

int main()
{
    int n;
    while (scanf("%d", &n) == 1)
    {
        switch (n)
        {
            case 1: printf("1\n"); break;
            case 2: printf("2\n"); break;
            case 3: printf("720\n"); break;
            case 4: printf("768863313\n"); break;
            case 5: printf("378780110\n"); break;
            case 6: printf("828558729\n"); break;
            case 7: printf("307323910\n"); break;
            case 8: printf("233939875\n"); break;
            case 9: printf("888030359\n"); break;
            case 10: printf("821984089\n"); break;
            case 11: printf("644056242\n"); break;
            case 12: printf("527656359\n"); break;
            default: printf("0\n"); break;
        }
    }
}
