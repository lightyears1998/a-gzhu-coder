/**
 * 反例
 *
 * INPUT: 1 3 2
 * OUTPUT:
 * 3 1
 * 2 3
 * 1 2
 *
 * 建议模拟一遍选择排序的过程
**/

// #include <string>
// #include <cstring>
// #include <iostream>
// #include <map>
// using namespace std;
//
// bool cmp(int a, int b)
// {
//     return a > b;
// }
//
// int main()
// {
//     int a[2050];
//     int b[2050];
//     int n;
//     while (scanf("%d", &n) == 1)
//     {
//         for (int i = 1; i <= n; i++)
//         {
//             scanf("%d", &a[i]);
//             b[i] = a[i];
//         }
//         sort(a + 1, a + 1 +n, cmp);
//         for (int i = 1; i <= n - 1; i++)
//         {
//             if (a[i] >= b[i]) printf("%d %d\n", a[i], b[i]);
//             else printf("%d %d\n", a[i], a[i]);
//         }
//         printf("\n");
//     }
// }
