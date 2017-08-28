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

- 运算符 *=*
- 函数 *main()* *printf()*
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

- 关键字 *int, short, long, unsigned, char, float, double, _Bool, _Complex, _Imaginary*
- 运算符 *sizeof*
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

*sizeof()* 以字节为单位给出类型的大小，使用“%zd”打印 *sizeof()* 运算符返回的结果。

```c
printf("Long类型的占用%zd字节。", sizeof(long));

```

## 第4章 字符串和格式化输入/输出

### *printf()* 格式说明符

| 整型进位制 | 符号 | 备注 |
| --- | --- | --- |
| 十进制 | d | |
| 无符号十进制 | u | |
| 八进制 | o | |
| 前缀八进制 | #o | |
| 十六进制 | x | 不是“h”，“h”用于表示short类型 |
| 前缀十六进制 | #x 或 #X | 分别对应“0x”和“0X”前缀 |

| 整型类型 | 符号 | 备注 |
| --- | --- | --- |
| short类型 | h | |
| int类型 | N.A. | 借用十进制符号d输出 |
| long类型 | l | |
| long long类型 | ll | |

| 浮点类型 | 符号 | 备注 |
| --- | --- | --- |
| 小数形式的浮点数 | f | |
| 指数计数法的浮点数 | e | |
| 指数计数的十六进制浮点数 | a | |

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
	printf("John Lightyears");

	return 0;
}

```

### 练习2.2：输出姓名和地址

```c
#include <stdio.h>

int main(void)
{
	printf("John Lightyears\n");
	printf("Guangzhou University, 230 Central West Road, Panyu District, Guangzhou");

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
	printf("我今年%d岁，我生活了%d天。", age, days);

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
	printf("Which nobody can deny!");
}

```

### 练习2.5：练习使用变量

```c
#include <stdio.h>

int main(void)
{
	int toes = 10;
	printf("toes is %d, and toes and toes is %d.\n", toes, toes + toes);
	printf("toes' square is %d.", toes * toes);

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
	printf("done!");

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

### 练习3.1：
