/**
 * 时间：17-08-14
 *
 * 作者：帽子（学长）
 * 
 * 题目：
 * 输入两个正整数（int类型即可），判断其大小，然后输出较大的数
 * 这些题就算写不出代码，也应该能有一个想法，慢慢来就好啦
 *
 */

#include <stdio.h>

int main(void)
{
    int a,b;
    scanf("%d", &a);
    scanf("%d", &b);

    if(a>b)
        printf("%d", a);
    else 
        printf("%d", b);

    return 0;
}
