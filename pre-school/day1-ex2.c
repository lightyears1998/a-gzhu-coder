/**
 * 时间：17/08/10
 *
 * 作者：仙女（学姐）
 *
 * 题目：
 * 简单的int类型的四则运算。
 * 输入格式为：（整数a） （运算符号）（整数b）.
 * 输出格式为：“a （运算符号）b = ？？？”
 * 双引号不用输出。
 * 
 * 题目拓展：
 * 整数改为浮点数，输出精度为小数点后两位。
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printUsage(char arg[]);

int main(int argc, char *argv[])
{
    /* 参数检查 */
    {
        if(argc>2)
        {
            printf("错误：参数过多");
            return -1;
        }
        if(argc==1)
        // 无参数时输出说明
        {
            printUsage(argv[0]);
            return 0;
        }
    }

    char *end;

    double lhs = strtod(argv[1], &end);
    if(strlen(end)==strlen(argv[1]))
    {
        printf("错误：左操作数格式错误");
        return -1;
    }
    switch(*end)
    {
        case '+':
        {
            end++;
            double rhs = strtod(end, &end);
            if(strlen(end)!=0)
            {
                printf("错误：右操作数格式错误");
                return -1;
            }
            printf("a+b=%.2f",lhs+rhs);
            return 0;
        }
        case '-':
        {
            end++;
            double rhs = strtod(end, &end);
            if(strlen(end)!=0)
            {
                printf("错误：右操作数格式错误");
                return -1;
            }
            printf("a-b=%.2f",lhs-rhs);
            return 0;
        }
        case '*':
        {
            end++;
            double rhs = strtod(end, &end);
            if(strlen(end)!=0)
            {
                printf("错误：右操作数格式错误");
                return -1;
            }
            printf("a*b=%.2f",lhs*rhs);
            return 0;
        }
        case '/':
        {
            end++;
            double rhs = strtod(end, &end);
            if(strlen(end)!=0)
            {
                printf("错误：右操作数格式错误");
                return -1;
            }
            if(rhs==0){
                printf("数学错误：NaN");
                return 0;
            }
            printf("a/b=%.2f",lhs/rhs);
            return 0;
        }
        case '\\':
        {
            printf("请使用“/”表示除");
            return 0;
        }
        default:{
            printf("错误：左操作数错误、无操作符或操作符不支持");
            return -1;
        }
    }
}

void printUsage(char arg[])
{
    // 取得可执行文件名
    char *path = arg;
    while(arg = memchr(arg, '\\', strlen(arg)))
    {
        arg++;
        path = arg;
    }
    // 兼容Linux
    arg = path;
    while(arg = memchr(arg,'/',strlen(arg)))
    {
        arg++;
        path = arg;
    }

    printf("语法：\n"
	"%s [<左操作数><运算符><右操作数>]\n",
	path);

	printf("\n说明：\n"
	"这个小程序根据输入的操作数和运算符计算结果，仅支持四则运算\n"
    "当你不提供参数时输出程序的说明");
    
    printf("\n");
    
    printf("\nIf characters above aren't displayed properly.\n"
    "Please switch to UTF8 Encoding.\n"
    "Try the follwing command if you are using Windows Command Prompt:\n"
    "> chcp 65001;\n");
}
