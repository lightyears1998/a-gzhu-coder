/**
 * 链接：
 * http://acm.hdu.edu.cn/showproblem.php?pid=1003
 *
 */

/**
 * 题目分析： 
 * 可以穷举所有可能的情形，选择最优解。 
 *
 */

#include <stdio.h>

struct collection{
    int max_sum;
    int sequence_begin;
    int sequence_end;
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
            // HDOJ不支持变长数组
            int integers[100000];
        #else
            int integers[length];
        #endif
        
        for(int i=1; i<=length; i++)
        {
            scanf("%d", &integers[i-1]);
        }

        for(int begin=1; begin<=length; begin++)
        {
            for(int end=1; end<=length; end++)
            {
                int sum=0;
                for(int current=begin; current<=end; current++){
                    sum += integers[current-1];
                }
                if(sum > candidate.max_sum){
                    candidate.max_sum = sum;
                    candidate.sequence_begin = begin;
                    candidate.sequence_end = end;
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
