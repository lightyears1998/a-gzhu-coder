/**
 * 时间：17/08/10
 *
 * 作者：仙女（学姐）
 *
 * 题目：
 * 相信你们高中数学都有讲过if...else...语句，没错，这一题目就需要你们用到这一语句。
 * 随便输入一个数，判断它属于哪一范围内的数据类型，例如2147483647属于int，然后输出它的数据类型。
 *
 */

/**
 * 基本定义：
 * C语言的数据类型有short int, int, long int 和 long long int. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void printUsage(char arg[]);
void printMessage(void);

int main(int argc, char *argv[])
{
	const int SHORT_LENGTH = sizeof(short int);
	const int INT_LENGTH = sizeof(int);
	const int LONG_LENGTH = sizeof(long int);
	const int LONG_LONG_LENGTH = sizeof(long long int);

	/* 参数检查 */
	{
		// 无参数时输出说明
		if(argv[1]==NULL){
			printUsage(argv[0]);
			return 0;
		}
		else if(argv[2]!=NULL)
		{
			printf("错误：参数过多");
			return -1;
		}
		else
		{
			char *end;
			strtoll(argv[1], &end, 10);
			if(*end!='\0'){
				printf("错误：参数含有非数字字符");
				return -1;
			}
		}
	}

	char *end;

	if( strtold(argv[1], &end) > exp2l(LONG_LONG_LENGTH * 8 - 1)  
		||  strtold(argv[1], &end) < -exp2l(LONG_LONG_LENGTH * 8 - 1) )
	{
		printf("数值过大或过小，即使LONG LONG INT类型也不能正确表示");
		return 0;
	}

	long long value = strtoll(argv[1], &end, 10);

	if(value <0)
	{
		value = -(value+1);
	}

	if( value < exp2(SHORT_LENGTH * 8 - 1))
	{
		printf("SHORT INT");
	}
	else if( value < exp2(LONG_LENGTH * 8 - 1))
	{
		printf("LONG INT");
	}else if( value < exp2(LONG_LONG_LENGTH * 8 - 1))
	{
		printf("LONG LONG INT");
	}

	if( value < exp2(INT_LENGTH *8 -1) )
	{
		printf(", INT");
	}
	return 0;
}

void printUsage(char arg[])
{
	// 取得可执行文件名
	char *path = arg;
	while((arg = memchr(arg, '\\', strlen(arg))))
	{
		arg++;
		path = arg;
	}
	// 兼容Linux
	arg = path;
	while((arg = memchr(arg,'/',strlen(arg))))
    {
        arg++;
        path = arg;
    }

	printf("语法：\n"
	"%s [<数值>]\n",
	path);

	printf("\n说明：\n"
	"这个小程序判断输入的数值在系统上哪一种整数类型的表达范围中，并输出该整数类型。\n"
	"当你不提供参数时输出程序的说明");

	printMessage();
}

void printMessage(void)
{
    printf("\n");
    
    printf("\nIf characters above aren't displayed properly.\n"
    "Please switch to UTF8 Encoding.\n"
    "Try the follwing command if you are using Windows Command Prompt:\n"
    "> chcp 65001;\n");
}
