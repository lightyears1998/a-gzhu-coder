/**
 * 链接：
 * http://acm.hdu.edu.cn/showproblem.php?pid=1002
 *
 */

/**
 * 题目分析：
 *
 * 题干中“You may assume the length of each integer will not exceed 1000.”表明，
 * 即使是使用LONG LONG INT类型也无法满足处理题目数据的需求。（2^64 ≈ 1.84e19）
 * 我们需要自己编写能接受1000位整数的类型，并且为它实现加法。 
 * 由题干中“the integers are very large”，这里不考虑输入的整数为负的情况。
 *
 * 还记得半加器吗？
 * 这里用char数组模拟一个整数，数组中的每一个元素模拟整数中的一个位置。
 *
 */

#include <stdio.h>

int main(void)
{
    int count;
    scanf("%d", &count);
    getchar();  

    for(int i=1; i<=count; i++)
    {
        char a[1000]={0}, b[1000]={0}, sum[1001]={0};
        
        /* 接受输入 */
        {
            char input;
            char flag=0;
            int pointer=999;
            while((input=getchar()) != '\n')
            {
                if(input!=' ')
                {
                    input -= 48;
                    if(flag==0){
                        a[pointer]=input;
                    }else{
                        b[pointer]=input;
                    }
                    pointer--;
                }
                else
                {
                    pointer=999;
                    flag++;
                }
            }
        } 

        /* 进行计算 */
        char carry = 0;
        for(int pointer=999; pointer>=0; pointer--)
        {
            sum[pointer+1] = a[pointer] + b[pointer] + carry;
            if(sum[pointer+1]>=10){
                sum[pointer+1] -= 10;
                carry = 1;
            }else{
                carry = 0;
            }
            if(pointer==0 && carry==1){
                sum[0]=1;
            }
        }

        /* 输出结果 */
        printf("Case %d:\n", i);
        for(int pointer=999;pointer>=0;pointer--)
        {
            if(a[pointer]!=0){
                a[pointer]+=48;
                printf("%c", a[pointer]);
            }
        }
        printf(" + ");
        for(int pointer=999;pointer>=0;pointer--)
        {
            if(b[pointer]!=0){
                b[pointer]+=48;
                printf("%c", b[pointer]);
            }
        }
        printf(" = ");
        for(int pointer=1000;pointer>=0;pointer--)
        {
            if(sum[pointer]!=0){
                sum[pointer]+=48;
                printf("%c", sum[pointer]);
            }
        }
        printf("\n");
    }

    return 0;
}
