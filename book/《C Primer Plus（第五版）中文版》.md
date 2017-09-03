《C Primmer Plus》是很好的C语言入门自学指南。

《C Primmer Plus》可称为《C2P》或《CPx2》；
《C++ Primer Plus》可称为《C4P》或《CPx4》。

人民邮电出版社于2005年出版了《C2P（第五版）中文版》，于2016年4月出版了《C2P（第六版）中文版》。
第五版内容涵盖了C99标准，第六版的内容针对C11标准进行了全面更新。如果你想购买《C2P》，建议购买最新的第六版。

下面是第五版的一些笔记和一些课后编程练习的尝试解答，希望对你有所帮助。 ^_^

# 笔记

## 第1章 概览

学习内容提要：

- C的历史和特性。
- 编写程序所需的步骤。
- 关于编译器和链接器的一些知识。
- C的标准。

> 自由的代价是永远的谨慎。

### C语言的起源

> C语言主要是由贝尔电话实验室的丹尼斯·M·里奇（Dennis M.Ritchie）开发的，从1969年开始设计并于1973年开发完成。……它是一种早期的程序设计语言B语言的后继者。B是BCPL（Basic CPL）语言的一种精简版本，而BCPL来源于CPL（Combined Programming Language）。
> 
> 参见[《编码》](history/《编码：隐匿在计算机软硬件背后的语言》.md)396页

### 历史上著名的公司

- *Microsoft*
- *Borland* 宝蓝公司
- *Metrowerks* 出品CodeWorriors
- *Digital Mars* 出品Digital Mars C/C++编译器

### C语言标准

《C2P（第五版）》介绍的是C99标准，时至今日，所有现代的编译器都支持C99标准。
C语言也迎来了比C99更新的标准——C11标准，第六版在第五版的基础上对C11标准的内容做了全面更新。
编译器对C语言标准的支持可以在[CPP Reference][cppreference]网站上查询。

[cppreference]: http://en.cppreference.com/w/

## 第2章 C语言概述

学习内容提要：

- 运算符：*=*
- 函数：*main()* *printf()*
- 编写一个简单的C程序。
- 创建整形变量，为其赋值，并在屏幕上显示该值。
- 换行字符。
- 如何在程序中加入注释，建立包含多个程序的内容，以及找出程序中的错误。
- 理解什么是关键字。

### main() 函数

推荐使用`int main(void){ // body }`形式的main()函数：

- `void main(){}` 不符合C语言标准。
- `main(){}` 不符合C99标准。
- `int main(){}` 能编译运行，但它不是标准的C语言形式。

参见[CPP Reference网站中关于main()函数的内容](http://en.cppreference.com/w/c/language/main_function)。

### 标识符（biāo zhì fú）

C语言的标识符（identifier）可使用小写字母、大写字母、下划线和数字，不能以数字开头，以避免与数值常量混用。

推荐使用字母作为变量名的开头，把下划线留给标准库使用。

### 关键字

如果一个字符序列不能用作标识符，那么它是一个关键字（keyword）。
如果一个字符序列不应当用作标识符，那么他是一个保留标识符（reserved identifier）。

从这个角度看，main和function都不是C语言的标识符，int和char是C语言的标识符。

## 第3章 数据和C

学习内容提要：

- 关键字：*int, short, long, unsigned, char, float, double, _Bool, _Complex, _Imaginary*
- 运算符：*sizeof*
- 函数 *scanf()*
- C使用的基本数据类型
- 整数类型和浮点数类型的区别
- 对上述类型，如何书写常量和声明变量。
- 使用 *printf()* 和 *scanf()* 函数读写各种类型数据的值。

### 位、字节与字

位（bit）是逻辑上和物理上容纳数据的最小单位，一个位可以容纳0，1中的一个值。

字节（byte）是计算机储存数据的常用单位，一个字节*总是*等于8位。
在C语言中，有时候“字节”用来指称能容纳平台基本字符集中的一个字符的储存单位。

字（word）是自然的储存单位。Windows操作系统的字长通常为32位或64位（就是常说的“32位操作系统”或“64位操作系统”）。

### 常量书写

| 字面值 | 数据类型 | 备注 |
| --- | --- | --- |
| 32 | int | |
| 32L | long | |
| 32LL | long long | |
| 32U | unsigned int | |
| 32UL | unsigned long | |
| 32ULL | unsigned long long | |

对于整数类型，只有在硬编码（hard code）数值时的一些特殊情况下才需要字面值后缀。
一个例子是在C语言中嵌入汇编代码时，使用32ULL指示一个64位的内存地址。

对于下面的例子，有无后缀均可：

```c
long a = 32;
long b = 32L;

printf("%ld %ld", a, b);	// 输出 32 32

```

| 字面值 | 数据类型 | 备注 |
| --- | --- | --- |
| 32.64 | double | |
| .32<br />0.32 | double | |
| 3.2E3<br />3.2e3| double | = 3.2 * 10³ |
|32. | double | 默认情况下浮点数字面值总是被当作double类型 |
|32.F | float | 只有使用F后缀的字面值才被当作float类型 |
| 0xA.1FP10 | double | 十六进制浮点数，十进制值为 (10 * 16⁰ + 1 * 16⁻¹ + 15 * 16⁻² ) * 2¹⁰ |

只有在用字面值对float类型赋值时才需要字面值后缀。

没有八进制浮点数。

### 进位制与整型字面值

十六进制中的A，B，C，D，E和F分别代表十进制中的10，11，12，13，14和15。

| 进位制 | 前缀 | 例子 |
| --- | --- | --- |
| 十进制（**DEC**imal） | N.A. | 12 |
| 八进制（**OCT**al） | 0 | 014，等于十进制数12 |
| 十六机制（**HEX**adecimal） | 0x 或 0X | 0xC，等于十进制数12 |

### 字符字面值

char本质上是一个占用一个或多个字节来储存信息的形式。
如果对char类型赋值，赋值操作符右边的操作数实际上会转变成整型赋给char类型的变量。

```c
char ch = <右操作数>;

// 向屏幕输出
printf("%c", ch);

```

| “右操作数”形式 | “右操作数”类型 | 屏幕上输出的字符（在兼容Ascii的环境中） |
| --- | --- | --- |
| 'c' | 字符字面值 | c |
| '\n' | 转义字符 | （换行） |
| '\0143'<br />'\143' | 转义字符<br /> 格式为“\0ooo”或"\ooo"，其中“ooo”为八进制数 | c |
| '\x63'<br />'\0x63' | 转义字符<br /> 格式为“\xhh”，其中“hh”为十六进制数 | c |
| 99<br />0143<br />0x63 | 整型数值 | c |

### *sizeof()*

*sizeof()* 以字节为单位给出类型的大小，使用 *printf()* 打印 *sizeof()* 运算结果时，可以使用“%zd”或“%zx”等说明符。

对标识符或者字面值使用 *sizeof* 时，可以省略圆括号；对于能使用 *sizeof* 查看占用储存空间大小的关键字（如，类型名float）则不能省略圆括号。总是使用圆括号是一个好习惯。

*sizeof()*的返回值是一个*size_t*类型，它可能是unsigned int或unsigned long的同义词。

```c
printf("Long类型的占用%zd字节。", sizeof(long));

```

## 第4章 字符串和格式化输入/输出

学习内容提要：

- 函数 *strlen()*
- 关键字 *const*
- 字符串。
- 如何创建和存储字符串。
- 如何使用 *scanf()* 和 *printf()* 读取和显示字符串。
- 如何使用 *strlen()* 获取字符串的长度。
- 使用C预处理器的#define指令和ANSI C的const修饰符创建常量。

### 字符串类型

字符串以空字符（'\0'）结束。在使用 *scanf()* 读取字符串以及使用字符串字面值，以及使用*printf()*打印字符串时，空字符会被自动处理。

### *printf()* 格式说明符

组合格式说明符时，首先是“+”“-”等通用打印格式说明符，然后指定宽度和精度，（对于整型）接着是整型类型和整形进位制，（对于浮点型）或者是浮点数打印形式，或者是其他类型。

用整数来指定宽度；用小数点“.”开头，后接整数的方式指定精度。宽度为打印时最小字段宽度；精度对于小数打印为小数点右边的数字位数，对于科学计数法是指有效数字的最大位数，对于字符串是指打印字符的最大数目，对于整型是指打印数字的最小位数（如有必要，会用前导零填充）。只使用“.”而后不附加整数，则等价于“.0”，即“%.f”与“%.0f”相同，均不输出小数。

也可以使用程序中的整型或浮点型变量的值来指定宽度，这种情况下使用*修饰符。

| 通用打印形式 | 符号 | 备注 |
| --- | --- | --- |
| 左对齐 | - | *printf()* 指定宽度打印时默认右对齐 |
| 强调符号 | + | 非负时显示正号，负值时显示负号 |
| 保证符号位 | （空格） | 非负时显示前导空格，负值时显示负号 |
| 显示进制前缀/保证尾随零 | # | （整型）根据进制，可对应“0”、“0x”和“0X”前缀<br />（浮点型）保证至少有一位小数点 |
| 用前导零填充打印宽度 | 0 | |

| 整型类型 | 符号 | 备注 |
| --- | --- | --- |
| short | h | |
| int | N.A. | |
| long | l | |
| long long | ll | |

| 整型打印形式 | 符号 | 备注 |
| --- | --- | --- |
| 有符号十进制 | d 或 i | |
| 无符号十进制 | u | |
| 无符号八进制 | o | |
| 无符号十六进制 | x | 不是“h”，“h”用于表示short类型 |

| 浮点数类型 | 符号 | 备注 |
| --- | --- | --- |
| float | N.A. | |
| double | l | |
| long double | L | |

| 浮点数打印形式 | 符号 | 备注 |
| --- | --- | --- |
| 小数形式的浮点数 | f | |
| 指数计数法的浮点数 | e 或 E | |
| 指数计数的十六进制浮点数 | a 或 A | |
| 自动选择计数法 | g 或 G | 根据浮点数值的不同自动选择计数法，科学记数法在指数小于4或数值大于等于精度时使用 |

| 其他类型 | 符号 | 备注 |
| --- | --- | --- |
| char | c | 打印一个字符 |
| 百分号 | % | 打印一个百分号 |
| 字符串 | s | 打印字符串 |
| 指针 | p | 打印指针 |
| --- | --- | --- |
| 与整型结合的char | hh | 与整型说明符一起使用，表示signed char（"%hhd"）或unsigned char（"%hhu"） |
| 指针的差 | t | 与整型说明符一起使用，如“td” |
| *sizeof* 返回值（size_t类型） | z | 与整型说明符一起使用，如“zd” |

严谨地讲，格式说明符分为转换说明符和转换说明修饰符。转换说明修饰符可用于修饰转换说明符，修饰符不能独立充当说明符。上表的“整型打印形式”、“浮点数打印形式”以及“其他类型”的上半部分是说明符，“通用打印形式”、“整型类型”、“浮点数类型”以及“其他类型”的下半部分是修饰符。

### *scanf()* 格式说明符

| 读取整型 | 符号 | 备注 |
| --- | --- | --- |
| 有符号十进制 | d 或 i | |
| 无符号十进制 | u |
| 有符号八进制 | o | |
| 有符号十六进制 | x 或 X | | 
| --- | --- | --- |
| int | N.A. | |
| long | l | |
| long long | ll |

| 读取浮点数 | 符号 | 备注 |
| --- | --- | --- |
| 小数形式浮点数 | f | |
| 指数计数法形式浮点数 | e 或 E | |
| 指数计数法形式的十六进制浮点数 | a 或 A | |
| 自动判断浮点数形式 | g 或 G |
| --- | --- | --- |
| float | N.A. | |
| double | l | |
| long double | L |

| 读取其他类型 | 符号 | 备注 |
| --- | --- | --- |
| 字符 | c | |
| 字符串 | s | |
| 指针 | p | |

| 转换修饰符 | 意义 |
| --- | --- | --- |
| * | 滞后赋值 |
| 使用整数指定最大读取宽度 | 在达到最大宽度时或遇到第一个空白字符时停止读取 |
| hh | 把整数读取成signed char（"%hhd"）或unsigned char（"%hhu"）|

与 *printf()* 格式说明符类似，*scanf()* 格式说明符分为“转换说明符”和“转换说明修饰符”。上表中，“读取整型”的前半部分、“读取浮点数”的前半部分和“读取其他类型”为转换说明符，“读取整型”后半部分、“读取浮点型”后半部分、“转换修饰符”部分为转换修饰符。

格式字符串中的空格表示跳过下一个输入项之前任何空格。因此 `scanf("%c", &ch);` 表示读取下一个字符，而 `scanf(" %c", &ch);` 表示读取下一个非空白字符。

### *printf()* 和 *scanf()*

#### 返回值

*printf()*的返回值返回打印字符的个数；

*scanf()*的返回值返回成功读取项目的个数，或在遇到“文件结尾”时返回EOF。

#### 格式字符串中的*修饰符

在*printf()*的格式字符串中使用*修饰符，表示打印宽度和精度有程序中整型或浮点型的变量来指定。

在*scanf()*的格式字符串中使用\*修饰符时，将\*放在%与说明符之间，表示滞后赋值。

### 整型和浮点型数大小限制

在 *limits.h* 和 *float.h* 头文件中定义了有关整型和浮点型数大小限制的信息。

## 第5章 运算符、表达式和语句

学习内容提要：

- 关键字：*while* *typedef*
- 运算符：*= - * / % ++ -- (type)*
- C的各种各样的运算符，其中包括用于普通数学运算的运算符。
- 运算符的优先级以及术语“语句”和“表达式”的含义。
- 简单的while循环
- 如何编写带有参数的函数

### 基本运算符

赋值运算符、加减乘除运算符。C中没有幂运算符。自增、自减运算符。

### 除法与模运算

整型的除法总是截尾，并且是*趋零截尾*。

因此，正数的模是正数，负数的模是负数。

### 优先度

共享操作数的操作符，执行顺序按优先度决定；不共享操作数的操作符，即使具有同等的优先度，也不能获知哪一个运算先执行。如“ 7\*6 + 8\*9 ”，不知道7\*6先执行还是8\*9先执行。

### 表达式和语句

表达式（expression）由运算符和操作数组成，每个表达式都有值。一些表达式是其他表达式的组成部分，称为子表达式（subexpression）。

一个（有作用的）语句（statement）是一条完整的计算机指令，语句用结束处的分号标识。C把结束处有分号的表达式看作语句，称为*表达式语句*。

声明语句（declaration statement）不是一个表达式语句，它没有值。

赋值语句（assignment statement）是表达式语句的一个特例。

函数语句（function statement）引起函数的执行。

结构化语句（structrued statement）是比一般语句复杂的语句。

复合语句（compound statement）或代码块（block）

空语句是什么也不做的语句。

#### 副作用和顺序点

从C的角度看，C的主要目的是为表达式求值。表达式引起的数据对象的变化、文件的修改等称为副作用（side effect）。

顺序点（sequence point）是程序执行中的一点，在该点处，所有的副作用都在进入下一步前被计算。在C中，语句的分号、一些运算符、任何完整的表达式（不是子表达式的表达式）的结束标志了顺序点。

### 类型转换

自动类型转换的规则如下：

- 在表达式里，char和short类型自动转换为int，需要时转换为unsigned int。
- 在包含两种数据类型的运算中，两个值被转换成两种类型里较高级的类型。
- 在赋值语句中，计算的最后结果被转换成被赋值的变量的类型（可能导致降级）

可以通过指派运算符强制转型。

### 自增/自减操作符

由于不能保证在语句执行过程中何时自增，在下列情况不要使用自增/自减运算符：

- 变量多次出现在同一个表达式里
- 变量出现在同一个函数的多个参数中

## 第6章 C控制语句：循环

学习内容提要：

- 关键字：*for while do while*
- 运算符：*< > >= <= != == += \*= -= %=*
- 函数：*fabs()*
- C的三种循环结构：while、for和do while
- 使用关系运算符构建控制循环的表达式。
- 其他一些运算符。
- 编写具有返回值的函数。

每次循环都被称为一次*迭代*。

### 关系运算符

大于（>）、小于（<）、大于或等于（>=）、小于或等于（<=）、等于（==）和不等于（!=）。

不能使用关系运算符比较字符串。

只能使用“>”或“<”来比较浮点数。

如果关系表达式为真，值为1；反之，值为0。

如果比较的双方有一方是常量，可以把常量放在左边，有助于发现错误。` 5 == canoes `

### 逻辑真与假

非零为真，零为假。

### 逗号运算符

逗号运算符“,”标志了一个顺序点，保证被它分开的表达式从左到右计算。逗号表达式的值是右边成员的值。

逗号“,”也被用作分隔符。

### while循环

*while (expression) statement;*

*statement*部分既可以是带有分号的简单语句，也可以是使用花括号包围的一个复杂语句，也可以是一条空语句。

只有*expresion*为真，*statement*才会执行。

空语句示例：

```c
while( scanf("%d", &num) == 1 )
	/* 跳过整数输入 */
;

```

### for循环

*for(ctrl_1; ctrl_2; ctrl_3) statement;*

控制表达式1在循环开始前执行；控制表达式2为真时开始一次迭代；控制表达式3在一次迭代完成后执行。

### do while循环

*do statement while(expression);*

## 第7章 C控制语句：分支和跳转

学习内容提要：

- 关键字：*if、else、switch、continue、break、case、default、goto*
- 运算符：*&&* *||* *?:*
- 函数：*getchar()*、*putchar*以及*ctype.h*系列
- 怎样使用if和if else语句以及如何嵌套使用它们
- 使用逻辑运算符将关系表达式组合为更加复杂的判断表达式。
- C的条件运算符。
- switch语句。
- break、continue和goto跳转。
- 使用C的字符I/O函数：getchar()和putchar()。
- 由ctype.h头文件提供的字符分析函数系列。

## 第8章 字符输入/输出和输入确认

学习内容提要：

- 有关输入、输出以及缓冲和非缓冲输入之间的区别的更多内容。
- 从键盘模拟文件结尾的办法。
- 如何重定向将您的程序与文件相连接。
- 使用户界面更加友好。

## 第9章 函数

学习内容提要：

- 关键字：*return*
- 运算符：*\*（一元）* *&（一元）*
- 函数及其定义方式。
- 参数和返回值的使用方法。
- 使用指针变量作为函数参数。
- 函数类型。
- ANSI C原型。
- 递归。

## 第10章 数组和指针

学习内容提要：

- 关键字：*static*
- 运算符：*&\*（一元）*
- 创建与初始化数组的方法。
- 指针（基于已学的基础知识）及指针和数组间的关系。
- 编写使用数组的函数。
- 二维数组。

## 第11章 字符串和字符串函数

学习内容提要：

- 函数：*gets() puts() strcat() strncat() strcmp() strncmp() strcpy() sprintf() strchr()*
- 创建和使用字符串。
- 利用C库里的字符串和字符函数创建您自己的字符串函数。
- 使用命令行参数。

## 第12章 储存类、链接和内存管理

学习内容提要：

- 关键字：*auto external static register const volatile restricted*
- 函数：*rand() srand() time() malloc() calloc() free()*
- 在C中如何确定变量的作用域（它在多大范围内可知）以及变量的生存周期（它存在多长时间）。
- 设计更复杂的程序。

## 第13章 文件输入/输出

学习内容提要：

- 函数：*fopen() getc() putc() exit() fclose() fprintf() fscanf() fgets() fputs() rewind() fseek() ftell() fflush() fgetpos() fsetpos() feof() ferror() ungetc() setvbuf() fread() fwrite()*
- 如何使用C的标准I/O函数系列处理文件。
- 文本模式和二进制模式，文本格式和二进制格式，以及缓冲和非缓冲I/O。
- 使用既可以顺序存取文件又可以随机存取文件的函数。

## 第14章 结构和其他数据形式

学习内容提要：

- 关键字：*struct union typedet*
- 运算符：*. ->*
- 什么是C语言中的结构？如何创建结构模板和结构变量？
- 如何访问结构成员？如何编写处理结构的函数？
- C的typedef工具。
- 联合及指向函数的指针。

## 第15章 位操作

学习内容提要：

- 运算符：*~* *&amp;* *|* *^* *>>* *<<* *&amp;=* *|=* *^=* *>>=* *<<=*
- 二进制、十进制和十六进制计数法（回顾）。
- 用于处理一个值中个别位的两个C工具：位运算符和位字段。

## 第16章 C预处理器和C库

学习内容提要：

- 预处理器指令：*#define #include #ifdef #else #endif #ifndef #if #elif #line #error #pragma*
- 函数：*sqrt() atan() atan2() exit() atexit() assert() memcpy() memmove() va_start() va_arg() va_copy() va_end()*
- C预处理的更多功能。
- 类函数宏和条件编译。
- 内联函数。
- C库概述和其中一些方便的函数

## 第17章 高级数据表示

学习内容提要：

- 用C表示多种数据类型。
- 新的算法，以及增强您从概念上开发程序的能力。
- 函数：进一步学习*malloc()*

# 章节编程练习

## 第2章

### 练习2.1：输出姓名

```c
#include <stdio.h>

int main(void)
{
	printf("John Lightyears\n");
	printf("John\n");
	printf("Lightyears\n");
	printf("John Lightyears\n");

	return 0;
}

```

### 练习2.2：输出姓名和地址

```c
#include <stdio.h>

int main(void)
{
	printf("John Lightyears\n");
	printf("Guangzhou University, 230 Central West Road, Panyu District, Guangzhou\n");

	return 0;
}

```

### 练习2.3：输出年龄

```c
#include <stdio.h>

int main(void)
{
	int age = 18;
	int days = age * 365;
	printf("我今年%d岁，我生活了%d天。\n", age, days);

	return 0;
}

```

### 练习2.4：输出重复的句子

```c
#include <stdio.h>

void print_sentence(void);
void print_another_sentence(void);

int main(void)
{
	print_sentence();
	print_sentence();
	print_sentence();
	print_another_sentence();

	return 0;
}

void print_sentence(void) 
{
	printf("For he's a jolly good fellow!\n");
}

void print_another_sentence(void)
{
	printf("Which nobody can deny!\n");
}

```

### 练习2.5：练习使用变量

```c
#include <stdio.h>

int main(void)
{
	int toes = 10;
	printf("toes is %d, and toes and toes is %d.\n", toes, toes + toes);
	printf("toes' square is %d.\n", toes * toes);

	return 0;
}

```

### 练习2.6：练习使用函数

```c
#include <stdio.h>

void smile(void);

int main(void)
{
	smile();smile();smile();printf("\n");
	smile();smile();printf("\n");
	smile();printf("\n");

	return 0;
}

void smile(void) 
{
	printf("Smile!");
}

```

### 练习2.7：练习使用函数（2）

```c
#include <stdio.h>

void one_three(void);
void two(void);

int main(void)
{
	printf("starting now:\n");
	one_three();
	printf("done!\n");

	return 0;
}

void one_three(void) 
{
	printf("one\n");
	two();
	printf("three\n");
}

void two(void)
{
	printf("two\n");
}

```

## 第3章

### 练习3.1：观察上溢和下溢

```c
#include <stdio.h>

int main(void)
{
	int i = 2147483647;	//32位int的最大值
	double d1 = 1.79e+308;
	double d2 = 2.22e-308;
	
	printf("整型上溢\n");
	printf("i=\t%d\n", i);
	printf("i+1=\t%d\n\n", i);
	
	printf("浮点数上溢\n");
	printf("d1=\t%e\n", d1);
	printf("d1+1e308=\t%e\n\n", d1 + 1e308);

	printf("浮点数下溢\n");
	printf("d2=\t%e\n", d2);
	printf("d2/1.79e+15=\t%e\n", d2 / 1.79e+15);
	printf("d2/1.79e+16=\t%e\n", d2 / 1.79e+16);

	return 0;
}

```

### 练习3.2：Ascii转换

```c
#include <stdio.h>

int main(void)
{
	int ascii;
	char ch;
	scanf("%d", ascii);
	ch = ascii;
	printf("%c\n", ch);
	
	return 0;
}
```

### 练习3.3：Ascii报警和打印文字

```c
#include <stdio.h>

int main(void)
{
	printf("\a");
	printf("Started by the sudden sound, Sally shouted, \"By the Great Pumpkin, what was that! \"\n");
	
	return 0;
}

```

### 练习3.4：输入和输出浮点数

```c
#include <stdio.h>

int main(void)
{
	float d;
	scanf("%f", &d);
	printf("The input is %f or %e.\n", d, d);

	return 0;
}

```

### 练习3.5：年龄问题

```c
#include <stdio.h>

int main(void)
{
	float sec = 3.156e7;
	int age;
	scanf("%d", &age);
	printf("%f\n", sec * age);

	return 0;
}

```

### 练习3.6：水分子问题

```c
#include <stdio.h>

int main(void)
{
	double mass = 3e-23;
	int quart = 950;
	int count;
	scanf("%d", &count);
	printf("%le\n", quart * count / mass );
	
	return 0;
}

```

### 练习3.7：英寸厘米转换

```c
#include <stdio.h>

int main(void)
{
	float intermediate = 2.54;
	float inch;
	scanf("%f", &inch);
	printf("%f\n", inch * intermediate);

	return 0;
}

```

## 第4章

### 练习4.1：输入和输出字符串

```c
#include <stdio.h>

int main(void)
{
	char last_name[40];
	char family_name[40];

	scanf("%s", last_name);
	scanf("%s", family_name);

	printf("%s %s\n", last_name, family_name);

	return 0;
}

```

### 练习4.2：输入和输出字符串（2）

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
	char name[40];

	scanf("%s", name);

	printf("\"%s\"\n", name);
	printf("\"%20s\"\n", name);
	printf("\"%-20s\"\n", name);
	printf("%*s\n", strlen(name)+3, name);

	return 0;
}

```

### 练习4.3：输入和输出浮点数

```c
#include <stdio.h>

int main(void)
{
	float value;
	scanf("%f", &value);

	printf("a. The input is %.1f or %.1e\n", value, value);
	printf("b. The input is %+.3f or %.3E\n", value, value);

	return 0;
}

```

### 练习4.4：混合输入与输出字符串与浮点数

```c
#include <stdio.h>

int main(void)
{
	char name[40];
	float height;

	scanf("%s %f", name, &height);
	printf("%s, you are %.3f metre tall.\n", name, height/100);

	return 0;
}

```

### 练习4.5：格式化字符串输入和输出

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
	char name[40];
	char family[40];

	scanf("%s%s", name, family);
	printf("%s %s\n", name, family);
	printf("%*d %*d\n", strlen(name), strlen(name), strlen(family), strlen(family));
	printf("%s %s\n", name, family);
	printf("%-*d %-*d\n", strlen(name), strlen(name), strlen(family), strlen(family));

	return 0;
}

```

### 练习4.6：浮点数精度测试

```c
#include <stdio.h>
#include <float.h>

int main(void)
{
	double d = 1.0/3.0;
	float f = 1.0/3.0;

	printf("Double:\n%.4lf\n%.12lf\n%.16lf\n", d, d, d);
	printf("Float:\n%.4f\n%.12f\n%.16f\n", f, f, f);

	printf("FLT_DIG: %d\n", FLT_DIG);
	printf("DBL_DIG: %d\n", DBL_DIG);

	return 0;
}

```

### 练习4.7：燃料表示

```c
#include <stdio.h>

int main(void)
{
	float mile;
	float gallon;
	const float convert_dis = 1.609;
	const float convert_oil = 3.785;

	scanf("%f%f", &mile, &gallon);
	printf("%.1f\n", mile/gallon);
	printf("%.1f\n", (gallon*convert_oil) / (mile*convert_dis) * 100);

	return 0;
}

```

## 第5章

### 练习5.1：小时和分钟转换

```c
#include <stdio.h>

const int M_PER_H = 60;

int main(void)
{
	int hrs;
	int mins;
	while(scanf("%d", &mins) != EOF)
	{
		if(mins <= 0){
			break;
		}
		hrs = mins / M_PER_H;
		mins -= hrs * M_PER_H;
		printf("%d:%02d\n", hrs, mins);
	}

	return 0;
}

```

### 练习5.2：循环输出

```c
#include <stdio.h>

int main(void)
{
	int num;
	scanf("%d", &num);
	int target = num + 10;

	while( num <= target)
	{
		printf("%d", num);
		if(num!=target){
			printf(" ");
		}
		num++;
	}

	printf("\n");

	return 0;
}

```

### 练习5.3：天周转换

```c
#include <stdio.h>

int main(void)
{
	int days;
	int weeks;
	while(scanf("%d", &days)!=EOF && days>=0)
	{
		printf("%d days are ", days);
		weeks = days / 7;
		days %= 7;
		printf("%d weeks, %d days.\n", weeks, days);
	}

	return 0;
}

```

### 练习5.4：厘米英寸转换

```c
#include <stdio.h>

int main(void)
{
	float centimeters;
	int feet;
	float inches;

	printf("Enter a height in centimeters: ");

	while(scanf("%f", &centimeters)!=EOF && centimeters>0)
	{
		inches = centimeters / 2.54;
		feet = inches / 12;
		inches -= feet * 12;
		printf("%.1f cm = %d feet, %.1f inches\n", centimeters, feet, inches);
		printf("Enter a height in centimeters (<=0 to quit): ");
	}

	printf("bye\n");
	
	return 0;
}

### 练习5.5：改写addemup.c

```c
#include <stdio.h>

int main(void)
{
	int count = 0, sum = 0;
	scanf("%d", &count);
	while(count>0)
	{
		sum += count;
		count--;
	}
	printf("%d\n", sum);

	return 0;
}

```

### 练习5.6：改写addemup.c（2）

```c
#include <stdio.h>

int main(void)
{
	int count = 0, sum = 0;
	scanf("%d", &count);
	while(count>0)
	{
		sum += count * count;
		count--;
	}
	printf("%d\n", sum);

	return 0;
}

```

### 练习5.7：计算立方

```c
#include <stdio.h>

float calc_cube(float side);

int main(void)
{
	float side;
	scanf("%f", &side);
	printf("%.2f\n", calc_cube(side));

	return 0;
}

float calc_cube(float side)
{
	return side * side * side;
}

```

### 练习5.8：温度计算

```c
#include <stdio.h>

void temperatures(double fahrenheit);

int main(void)
{
	double fahrenheit;
	int status = scanf("%lf", &fahrenheit);
	
	while(status!=0 && status!=EOF)
	{
		temperatures(fahrenheit);
		status = scanf("%lf", &fahrenheit);
	}

//! 这样做是不行的：while(status = scanf("%d", &fahrenheit) && status!=0 && status!=EOF)
//! 这是因为C只保证status值改变的副作用在进入下一条语句前被计算
//! 但可以这样写：
//! while(status = scanf("%lf", &fahrenheit), status!=0 && status!=EOF) {
//! 	temperatures(fahrenheit);
//! }
//! 参考第6章“逗号运算符”

	return 0;
}

void temperatures(double fahrenheit)
{
	const double C1 = 1.8;
	const double C2 = 32.0;
	const double C3 = 273.16;

	printf("Fahrenheit: %.2lf Celsius: %.2lf Kelvin: %.2lf\n",
		fahrenheit,
		C1 * fahrenheit + C2,
		C1 * fahrenheit + C2 + C3	
	);
}

```

## 第6章

### 练习6.1：显示小写字母

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
	char alphabet[] = "abcdefghijklmnoprstuvwxyz";
	for(int i=0; i<strlen(alphabet); i++)
	{
		printf("%c", alphabet[i]);
	}

	return 0;
}

```

### 练习6.2：嵌套循环

```c
#include <stdio.h>

int main(void)
{
	for(int i=1; i<=5; i++){
		for(int c=1; c<=i; c++){
			printf("$");
		}
		printf("\n");
	}

	return 0;
}

```

### 练习6.3：嵌套循环（2）

```c
#include <stdio.h>

int main(void)
{
	char lets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int line=5;
	for(int i=line; i>=0; i--)
	{
		for(int b=line; b>=i; b--){
			printf("%c", lets[b]);
		}
		printf("\n");
	}

	return 0;
}

```

### 练习6.4：嵌套循环（3）

```c
#include <stdio.h>

char lets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char lets_lower[] = "abcdefghijklmnopqrstuvwxyz";

int get_index(char c);

int main(void)
{
	char input;
	scanf("%c", &input);

	int line = get_index(input) + 1;
	for(int l=1; l<=line; l++)
	{
		for(int s=line-l; s>0; s--){
			printf(" ");
		}
		for(int c=0; c<=l-1; c++){
			printf("%c", lets[c]);
		}
		for(int c=l-1; c>0; c--){
			printf("%c", lets[c-1]);
		}
		printf("\n");
	}

	return 0;
}

int get_index(char c)
{
	int i=0;
	for(; i<=26; i++)
	{
		if(c==lets[i] || c==lets_lower[i]){
			break;
		}
	}

	return i;
}

```

### 练习6.5：表

```c
#include <stdio.h>

int main(void){
	int upper;
	int lower;
	scanf("%d %d", &lower, &upper);

	for(int i=lower; i<=upper; i++)
	{
		printf("%d %d %d\n", i, i*i, i*i*i);
	}

	return 0;
}

```

### 练习6.6：回文

```c
#include <stdio.h>
#include <string.h>

int main(void){
	char word[40];
	scanf("%s", word);

	for(int i=strlen(word)-1; i>=0; i--)
	{
		printf("%c", word[i]);
	}
	printf("\n");

	return 0;
}

```

### 练习6.7：浮点数与循环

```c
#include <stdio.h>

int main(void){
	float a, b;
	int status;

	while(status=scanf("%f %f", &a, &b), status!=EOF && status==2)
	{
		printf("%f\n", (a-b)/(a*b));
	}

	return 0;
}

```

### 练习6.8：浮点数、循环与函数

```c
#include <stdio.h>

float cal(float a, float b);

int main(void){
	float a, b;
	int status;

	while(status=scanf("%f %f", &a, &b), status!=EOF && status==2)
	{
		printf("%f\n", cal(a, b));
	}

	return 0;
}

float cal(float a, float b)
{
	return (a-b)/(a*b);
}

```

### 练习6.9：平方和

```c
#include <stdio.h>

int main(void){
	int a, b;
	int status;
	printf("Enter lower and upper integer limits: ");

	while(status=scanf("%d %d", &a, &b), status!=EOF && a<b)
	{
		int sum = 0;
		for(int i=a; i<=b; i++)
		{
			sum += i*i;
		}
		printf("The sums of the squares for %d to %d is %d\n", a, b, sum);
		printf("Enter next set of limits: ");
	}

	printf("Done\n");

	return 0;
}

```

### 练习6.10：反向打印数组

```c
#include <stdio.h>

int main(void)
{
	int nums[8];
	for(int i=0; i<8; i++){
		scanf("%d", &nums[i]);
	}
	for(int i=7; i>=0; i--){
		printf("%d ", nums[i]);
	}
	printf("\n");

	return 0;
}

```

### 练习6.11：收敛

```c
#include <stdio.h>

int sign(int a);

int main(void)
{
	double seq_1=0, seq_2=0;
	int count;
	scanf("%d", &count);

	for(int a=1; a<=count; a++){
		seq_1 += 1.0/a;
	}
	for(int a=1; a<=count; a++)
	{
		seq_2 += 1.0/a * sign(a);
	}
	printf("%lf\n%lf\n", seq_1, seq_2);

	return 0;
}

int sign(int a)
{
	if(a%2==1){
		return 1;
	}else{
		return -1;
	}
}

```

### 练习6.12：2的幂

```c
#include <stdio.h>

int main(void)
{
	int num[8]={2};
	int count;
	for(count=1; count<=7; count++){
		num[count] = 2 * num[count - 1];
	}
	count = 0;
	do{
		printf("%d ", num[count]);
		count++;
	}while(count<=7);
	printf("\n");

	return 0;
}

```

### 练习：6.13：积累

```c
#include <stdio.h>

int main(void)
{
	double a[8],b[8];

	for(int i=0; i<8; i++){
		scanf("%lf", &a[i]);
		printf("%8.2lf ", a[i]);
	}
	printf("\n");

	b[0] = a[0];
	printf("%8.2lf ", b[0]);
	for(int i=1; i<8; i++){
		b[i] = a[i] + b[i-1];
		printf("%8.2lf ", b[i]);
	}

	printf("\n");
	return 0;
}

```

### 练习6.14：反向打印行

```c
#include <stdio.h>

int main(void)
{
	char ch[256];
	int count=0;
	int status;
	while(status=scanf("%c", &ch[count]), status!=EOF)
	{
		if(ch[count]=='\n'){
			break;
		}
		count++;
	}
	while(count>0){
		printf("%c", ch[count-1]);
		count--;
	}
	printf("\n");

	return 0;
}

```

### 练习6.15：投资

```c
#include <stdio.h>

int main(void)
{
	int daphne=100, deirdre=100, year=0;
	while(deirdre<=daphne)
	{
		year++;
		daphne += 100 * 0.1;
		deirdre += deirdre * 0.05;
	}
	printf("%d years, daphne: $%d, deirdre: $%d\n", year, daphne, deirdre);

	return 0;
}

```
### 练习6.16：赢家

```c
#include <stdio.h>

int main(void)
{
	int account=100, year=0;
	while(account>0)
	{
		account += account * .08;
		account -= 10;
		year++;
	}
	printf("%d years\n", year);

	return 0;
}

```
