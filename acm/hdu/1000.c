/**
 * 链接：
 * http://acm.hdu.edu.cn/showproblem.php?pid=1000
 *
 */

/**
 * 题目分析： 
 * 这题是OJ的第一题，用于练习程序的输入输出。
 * 程序输入输出的样例由OJ给出，位于http://acm.hdu.edu.cn/faq.php?topic=cpp
 *
 */

#include <stdio.h>

int main(void)
{
	int a, b;
	while(scanf("%d %d", &a, &b)!=EOF)
	{
		printf("%d", a+b);
	}
	
	return 0;
}
