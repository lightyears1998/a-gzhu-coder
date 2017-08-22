/**
 * 链接：
 * http://acm.hdu.edu.cn/showproblem.php?pid=1001
 *
 */

#include <stdio.h>

int main(void)
{
	int n;
	int sum;
	while(scanf("%d", &n)!=EOF)
	{
		sum = n; 
		while(n--){
			sum += n;
		}
		printf("%d\n", sum);
		printf("\n");
	}
	
	return 0;
}
