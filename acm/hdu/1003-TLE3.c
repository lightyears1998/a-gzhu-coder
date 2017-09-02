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
 * 记负数项为X，非负项为O，一个可能的数列{aₙ}如下所示：
 * 我们把连在一起的非负项合并为1组（block），连在一起的负数项合并为1组。
 * [O O O O] [X] [O O] [X X] [O O O O O O] [X]
 *
 */

#include <stdio.h>

struct result
{
    int max_sum;
    int sequence_begin;
    int sequence_end;
};

struct block
{
    int begin;              // 第一个元素在数列中的项数
    int end;
    int value;
};

int main(void)
{    
    int test_count;
    scanf("%d", &test_count);

    // 不要在循环中定义超长数组
    struct block blocks[100000];

    for(int test_case=1; test_case<=test_count; test_case++)
    {
        // 读取数列长度
        int sequence_length;
        scanf("%d", &sequence_length);

        //! 不要在循环中定义超长数组
        //! struct block blocks[100000];

        // 初始化数组
        blocks[0].value = 0;
        blocks[0].begin = 1;

        // 读取数列元素，处理分组
        int block_count = 1;
        {
            int current_block=0;
            for(int sequence_pointer=1; sequence_pointer<=sequence_length; sequence_pointer++)
            {
                int current_value;
                scanf("%d", &current_value);

                if(current_value>=0)
                // 处理值非负的情况
                {
                    if(blocks[current_block].value>=0){
                        blocks[current_block].value += current_value;
                        blocks[current_block].end = sequence_pointer;
                    }else{
                        current_block++;
                        block_count++;
                        blocks[current_block].value = current_value;
                        blocks[current_block].begin = sequence_pointer;
                        blocks[current_block].end = sequence_pointer;
                    }
                }
                else
                // 处理值为负的情况
                {
                    if(blocks[current_block].value<=0){
                        blocks[current_block].value += current_value;
                        blocks[current_block].end = sequence_pointer;
                    }else{
                        current_block++;
                        block_count++;
                        blocks[current_block].value = current_value;
                        blocks[current_block].begin = sequence_pointer;
                        blocks[current_block].end = sequence_pointer;
                    }
                }
            }
        }

        struct result candidate = {0, 0, 0};

        for(int begin=0; begin<block_count; begin++)
        {
            for(int end=begin; end<block_count; end++)
            {
                int sum=0;
                for(int i=begin; i<=end; i++){
                    sum += blocks[i].value;
                }
                if(sum>candidate.max_sum){
                    candidate.max_sum = sum;
                    candidate.sequence_begin = blocks[begin].begin;
                    candidate.sequence_end = blocks[end].end;
                }
            }
        }

        printf("Case %d:\n", test_case);
        printf("%d %d %d\n", candidate.max_sum, candidate.sequence_begin, candidate.sequence_end);

        if(test_case!=test_count){
            printf("\n");
        }
    }
}
