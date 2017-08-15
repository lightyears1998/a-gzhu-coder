/**
 * 时间：17-08-14
 *
 * 作者：帽子（学长）
 * 
 * 题目：
 * 输入一个正整数（小于15），输出其阶乘
 * 例如，输入4，输出24
 */

#include <stdio.h>

int main(void)
{
    int a;
    scanf("%d",&a);

    int result = 1;
    for(int c=1; c<=a; c++)
    {
        result *= c; // 等价于 result = result * c;
    }
    printf("%d", result);

    return 0;
}
