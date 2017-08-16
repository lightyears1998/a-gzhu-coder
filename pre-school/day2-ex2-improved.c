/**
 * 时间：17-08-15
 *
 * 作者：仙女（学姐）
 *
 * 题目：
 * 用*号输出一个爱心。例如这样
 *  
 * 哈哈哈哈。
 * 发挥你们想象力输出爱心吧！反正去年我没做出来！
 */
 
/**
 * 这是参考[心形线方程][1]制作的改进版本
 *
 * 心形线的极坐标方程为：
 * ρ = a ( 1-cosθ ) （其中，a为参数）
 *
 * [1]: https://baike.baidu.com/item/%E5%BF%83%E5%BD%A2%E7%BA%BF/10018818
 */

#include <stdio.h>
#include <math.h>

struct point
{
    int x;      // x坐标
    int y;      // y坐标
    int flag;   // 星星标志
};

struct canvas
{
    int wide;   
    int length; 
};

int main(void)
{
    /* 定义坐标系 */
    struct canvas coordinate = {
        100,
        100
    };

    /* 定义原点 */
    struct point origin = {
        50,
        50
    };

    // 心形线方程参数
    int argument = 16;

    /* 定义坐标系点集 */
    struct point points[coordinate.wide * coordinate.length];
    for(int row=1; row<=coordinate.length; row++)
    {
        for(int column=1; column<=coordinate.wide; column++)
        {
            points[ (row-1)*coordinate.wide + column -1 ].x = row - origin.x;
            points[ (row-1)*coordinate.wide + column -1 ].y = (column - origin.y)/2;
            points[ (row-1)*coordinate.wide + column -1 ].flag = 0;
        }
    }

    /** 
     * points[4949]对应的是坐标系点集中的原点
     * points[0]对应坐标系中的第一个点
     * points[9999]对应坐标系点集中的最后一个点
     */
    
    /* 计算点的位置上是否应该有星星 */
    for(int i=0; i<= (coordinate.wide * coordinate.length -1); i++)
    {
        int x = points[i].x;
        int y = points[i].y;
        int rou = argument * (1 - x/hypot(x,y));    // ρ
        if(hypot(x,y) <= rou){
            // 在曲线内
            points[i].flag = 1;
        }
    }

    /* 逆序打印星星，让心形正立 */
    for(int i=(coordinate.wide * coordinate.length -1); i>=0 ; i--)
    {
        if(points[i].flag == 1){
            printf("*");
        }else{
            printf(" ");
        }
        if((i+1) % coordinate.wide == 0){
            printf("\n");
        }
    }

    return 0;
}
