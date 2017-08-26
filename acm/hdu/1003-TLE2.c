/**
 * 链接：
 * http://acm.hdu.edu.cn/showproblem.php?pid=1003
 *
 */

/**
 * 题目分析： 
 * 如果穷举所有可能的情形，选择最优解，很可能会TLE。
 * 我们需要根据题目特点进行优化。
 *
 * 不妨认为数列中所有的负数项为特殊项，因为一个数列前n项非负时，下一项为负则前(n+1)项和比前n项和小。
 * 此外，考虑数列的第一项和最后一项为特殊项，它们是遍历的起点和终点。
 *
 * 记特殊项为X，一般项为O，它们的可能排列如图所示：
 * X O O O X O O X O O O O O O X
 *
 */

#include <stdio.h>

struct collection{
    int max_sum;                // 子数列最大和
    int sequence_begin;         // 子数列起始项序号
    int sequence_end;           // 子数列终止项序号
};

struct element{
    int index;                  // 数组下标
    int value;                  // 项的值
    char special_flag;          // 特殊项标志
};

int main(void)
{
    int test_count;
    scanf("%d\n", &test_count);

    for(int test_case=1; test_case<=test_count; test_case++)
    {
        struct collection candidate = {
            0, 0, 0
        };
        
        int length;
        scanf("%d", &length);

        #ifdef ONLINE_JUDGE
            // HDOJ不支持变长数组（C99）
            struct element elements[100000];
        #else
            struct element elements[length];
        #endif
        
        for(int i=1; i<=length; i++)
        {
            elements[i-1].index = i;
            scanf("%d", &elements[i-1].value);
            if(elements[i-1].index==1 || elements[i-1].index==length || elements[i-1].value<0)
            {
                elements[i-1].special_flag=1;
            }
        }

        for(int begin=0; begin<length; begin++)
        {
            if(elements[begin].special_flag==1)
            {
                for(int end=begin; end<length; end++)
                {
                    if(elements[end].special_flag==1)
                    {
                        // Begin项到End项的数列和
                        {
                            int sum=0;
                            for(int i=begin; i<=end; i++)
                            {
                                sum += elements[i].value;
                            }
                            if(sum>candidate.max_sum){
                                candidate.max_sum = sum;
                                candidate.sequence_begin = elements[begin].index;
                                candidate.sequence_end = elements[end].index;
                            }
                        }

                        // Begin项到End项前一项的数列和
                        if(!(end-1<0))
                        {
                            int sum=0;
                            for(int i=begin; i<=(end-1); i++)
                            {
                                sum += elements[i].value;
                            }
                            if(sum>candidate.max_sum){
                                candidate.max_sum = sum;
                                candidate.sequence_begin = elements[begin].index;
                                candidate.sequence_end = elements[end-1].index;
                            }
                        }

                        // Begin项后一项到End项数列和
                        if(!(begin+1>length))
                        {
                            int sum=0;
                            for(int i=begin+1; i<=end; i++)
                            {
                                sum += elements[i].value;
                            }
                            if(sum>candidate.max_sum){
                                candidate.max_sum = sum;
                                candidate.sequence_begin = elements[begin+1].index;
                                candidate.sequence_end = elements[end].index;
                            }
                        }

                        // Begin项后一项到End项前一项数列和
                        if(!(begin+1>length)&&!(end-1<0))
                        {
                            int sum=0;
                            for(int i=begin+1; i<=(end-1); i++)
                            {
                                sum += elements[i].value;
                            }
                            if(sum>candidate.max_sum){
                                candidate.max_sum = sum;
                                candidate.sequence_begin = elements[begin+1].index;
                                candidate.sequence_end = elements[end-1].index;
                            }
                        }
                    }
                }
            }
        }

        printf("Case %d:\n", test_case);
        printf("%d %d %d\n", candidate.max_sum, candidate.sequence_begin, candidate.sequence_end);

        if(test_case!=test_count){
            printf("\n");
        }
    }

    return 0;
}
