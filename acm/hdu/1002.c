/**
 * 链接：
 * http://acm.hdu.edu.cn/showproblem.php?pid=1002
 *
 * 特别提示：
 * 截至17年8月，HDOJ中的GCC编译器默认不支持C99标准
 * HDOJMSVC编译器对C99标准的支持不完全
 * 
 * 如果在for循环的第初始化语句中初始化循环控制变量（C99引入的新特性），
 * 你需要以“C”语言提交（即不是“GCC”），以使用MSVC编译器。
 *
 */

/**
 * 题目分析：
 *
 * 长整数加法模板题
 *
 * 题干中“You may assume the length of each integer will not exceed 1000.”表明，
 * 即使是使用LONG LONG INT类型也无法满足处理题目数据的需求。（2^64 ≈ 1.84e19）
 * 我们需要自己编写能接受1000位整数的类型，并且为它实现加法。 
 * 由题干中“two positive integers”，这里不考虑输入的整数为负的情况。
 *
 * 还记得半加器吗？
 * 这里用char数组模拟一个超长整数，数组中的每一个元素模拟整数中的一个位置。
 * 数组a, b, sum从最后一个元素开始填充数据，高位在前；
 * 数组temp从第一个元素开始填充数据，高位在前。
 *
 * 图示：
 * a:       [0][0][0][0][0][0][2][3] （23）
 * b:       [0][0][0][0][0][2][6][7] （267）
 * sum:     [0][0][0][0][0][2][9][0] （290）
 * temp:    [2][9][0][0][0][0][0][0] （29或290或2900……）
 *
 */

#include <stdio.h>

int main(void)
{
    int count;
    scanf("%d\n", &count);

    for(int i=1; i<=count; i++)
    {
        char a[1000]={0}, b[1000]={0}, sum[1001]={0}, temp[1000];

        /* 获得数据 */
        access_data:
        {
            char input;
            int pointer=0;
            while(input=getchar())
            {
                switch(input)
                {
                    default:
                    {
                        temp[pointer] = input - 48;
                        pointer++;
                        break;
                    }
                    case ' ':
                    {
                        for(int current=0; pointer>0; pointer--)
                        {
                            a[999-current] = temp[pointer-1];
                            current++;
                        }
                        break;
                    }
                    case '\n':
                    {
                        for(int current=0; pointer>0; pointer--)
                        {
                            b[999-current] = temp[pointer-1];
                            current++;
                        }
                        goto perform_calculation;
                    }  
                }
            }
        }

        /* 执行运算 */
        perform_calculation:
        {
            for(int pointer=999; pointer>0; pointer--){
                if((sum[pointer+1] += (a[pointer] + b[pointer]) ) >= 10){
                    sum[pointer+1] -= 10;
                    sum[pointer] = 1;
                }
            }
            if( sum[1]+=(a[0]+b[0]) >= 10 ){
                sum[1] -= 10;
                sum[0] = 1;
            }
        }

        /* 输出结果 */
        output_result:
        {
            int flag = 0;
            printf("Case %d:\n", i);
            for(int pointer=0, flag=0; pointer<=999; pointer++)
            {
                if(flag || a[pointer]!=0){
                    flag = 1;
                    printf("%c", a[pointer]+48);
                }
            }
            printf(" + ");
            for(int pointer=0, flag=0; pointer<=999; pointer++)
            {
                if(flag || b[pointer]!=0){
                    flag = 1;
                    printf("%c", b[pointer]+48);
                }
            }
            printf(" = ");
            for(int pointer=0, flag=0; pointer<=1000; pointer++)
            {
                if(flag || sum[pointer]!=0){
                    flag = 1;
                    printf("%c", sum[pointer]+48);
                }
            }
            printf("\n");
        }

        if(i!=count){
            printf("\n");
        }
    }

    return 0;
}
