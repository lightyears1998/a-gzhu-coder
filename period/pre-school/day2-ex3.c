/**
 * 时间：17-08-15
 *
 * 作者：仙女（学姐）
 *
 * 题目：
 * 输入四个数字（整数就可以了），然后比较他们的大小，再然后按小到大的顺序输出。简单吧！
 *
 */

#include <stdio.h>

int main(void)
{
    int a,b,c,d;

    // 键入四个数字，数字之间用逗号分隔
    scanf("%d,%d,%d,%d", &a, &b, &c, &d);

	/* ง •̀_•́)ง */
    if(a>=b){
        // a>=b
        if(a>=c){
            // a>=b, a>=c
            if(b>=c){
                // a>=b>=c
                if(d>=a){
                    // d>=a>=b>=c
                    printf("%d,%d,%d,%d", c, b, a, d);
                }else{
                    // a>d, a>=b>=c
                    if(d>=b){
                        // a>d>b>=c
                        printf("%d,%d,%d,%d", c, b, d, a);
                    }else{
                        // a>=b>d, a>=b>c
                        if(d>=c){
                            // a>=b>d>=c
                            printf("%d,%d,%d,%d", c, d, b, a);
                        }else{
                            // a>=b>c>d
                            printf("%d,%d,%d,%d", d, c, b, a);
                        }
                    }
                }
            }else{
                // a>=c>b
                if(d>=a){
                    // d>=a>=c>b
                    printf("%d,%d,%d,%d", b, c, a, d);
                }else{
                    // a>=c>b, a>d
                    if(d>=c){
                        // a>d>=c>b
                        printf("%d,%d,%d,%d", b, c, d, a);
                    }else{
                        // a>=c>b, c>d
                        if(d>=b){
                            // a>=c>d>=b
                            printf("%d,%d,%d,%d", b, d, c, a);
                        }else{
                            // a>=c>b>d
                            printf("%d,%d,%d,%d", d, b, c, a);
                        }
                    }
                }
            }
        }else{
            // c>a>=b
            if(d>=c){
                // d>=c>a>=b
                printf("%d,%d,%d,%d", b, a, c, d);
            }else{
                // c>a>=b, c>d
                if(d>=a){
                    // c>d>=a>=b
                    printf("%d,%d,%d,%d", b, a, d, c);
                }else{
                    // c>a>=b, a>d
                    if(d>=b){
                        // c>a>d>=b
                        printf("%d,%d,%d,%d", b, d, a, c);
                    }else{
                        // c>a>=b>d
                        printf("%d,%d,%d,%d", d, b, a, c);
                    }
                }
            }
        }
	/* Σ(っ °Д °;)っ */
    }else{
        // b>a
        if(c>=b){
            // c>=b>a
            if(d>=c){
                // d>=c>=b>a
                printf("%d,%d,%d,%d", a, b, c, d);
            }else{
                // c>=b>a, c>d
                if(d>=b){
                    // c>d>=b>a
                    printf("%d,%d,%d,%d", a, b, d, c);
                }else{
                    // c>=b>a, b>d
                    if(d>=a){
                        // c>=b>d>=a
                        printf("%d,%d,%d,%d", a, d, b, c);
                    }else{
                        // c>=b>a>d
                        printf("%d,%d,%d,%d", d, a, b, c);
                    }
                }
            }
        }else{
            // b>a, b>c
            if(a>=c){
                // b>a>=c
                if(d>=b){
                    // d>=b>a>=c
                    printf("%d,%d,%d,%d", c, a, b, d);
                }else{
                    // b>a>=c, b>d
                    if(d>=a){
                        // b>d>=a>c
                        printf("%d,%d,%d,%d", c, a, d, b);
                    }else{
                        // b>a>=c, a>d
                        if(d>=c){
                            // b>a>d>=c
                            printf("%d,%d,%d,%d", c, d, a, b);
                        }else{
                            // b>a>=c>d
                            printf("%d,%d,%d,%d", d, c, a, b);
                        }
                    }
                }
            }else{
                // b>c>a
                if(d>=b){
                    // d>=b>c>a
                    printf("%d,%d,%d,%d", c, a, b, d);
                }else{
                    // b>c>a, b>d
                    if(d>=c){
                        // b>d>=c>a
                        printf("%d,%d,%d,%d", a, c, d, b);
                    }else{
                        // b>c>a, c>d
                        if(d>=a){
                            // b>c>d>=a
                            printf("%d,%d,%d,%d", a, d, c, b);
                        }else{
                            // b>c>a>d
                            printf("%d,%d,%d,%d", d, a, c, b);
                        }
                    }
                }
            }
        }
    }

	/* (((φ(◎ロ◎;)φ))) */ 
	
    return 0;
}
