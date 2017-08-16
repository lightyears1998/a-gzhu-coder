/**
 * 时间：17/08/10
 *
 * 作者：仙女（学姐）
 *
 * 题目：
 * 又临时加了一题。既然讲到ASCLL码，那就做一下大小写字母转换吧。
 * 如果输入一个大写字母，则输出它对应的小写字母。相反，如果输入一个小写字母，则输出它对应的大写。
 *
 */

#include <stdio.h>
#include <string.h>

void printUsage(char arg[]);
void printMessage(void);

int main(int argc, char *argv[])
{
    /* 参数检查 */
    {
        // 在无参数输入时输出程序说明
        if(argv[1]==NULL) 
        {
            printUsage(argv[0]);
            return -1;
        }
        // 检查参数的数量和格式
        else if(argv[2]!=NULL) 
        {
            printf("错误：参数过多");
            return -1;
        }
        else if(strlen(argv[1])>1){
            printf("错误：不支持的参数类型");
            return -1;
        }else if(*argv[1]<65 || (*argv[1]>90 && *argv[1]<97) || *argv[1]>122)
        {
            printf("错误：提供的参数不是英文字母，或运行环境不兼容Ascii");
            return -1;
        }
    }
    
    char character = *argv[1];
    if(character<96){
        character = character + 32;
    }else{
        character = character - 32;
    }
    printf("%c",character);
    return 0;
}

void printUsage(char arg[])
{   
    // 取得可执行文件名
    char *path = arg;
    while((arg = memchr(arg,'\\',strlen(arg))))
    {
        arg++;
        path = arg;
    }
    // 兼容Linux等以‘/’划分目录层次的环境
    arg = path;
    while((arg = memchr(arg,'/',strlen(arg))))
    {
        arg++;
        path = arg;
    }

    printf("语法：\n"
        "%s [<大写或小写英文字符>]\n",
        path);

    printf("\n说明：\n"
        "这个小程序将你输入的英文字符转换大小写后输出。\n"
        "当你不提供参数时输出程序的说明");

    printf("\n提示:\n"
        "如果你在不兼容Ascii的环境中使用这个程序，\n"
        "程序将不会正常工作。");
    
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
