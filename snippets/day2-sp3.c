/**
 * 时间：17-08-14
 *
 * 作者：帽子（学长）
 * 
 * 题目：输入一个正整数（小于100000），判断其是否为奇数
 */

#include <stdio.h>

int main(void)
{
    int a;
    scanf("%d", &a);
    
    if(a%2 == 0)
        printf("输入的是偶数");
    else
        printf("输入的是奇数");

    return 0;
}
