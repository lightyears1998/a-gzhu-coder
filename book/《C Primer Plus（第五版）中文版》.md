《C Primmer Plus》是很好的C语言入门自学指南。

《C Primmer Plus》可称为《C2P》或《CPx2》；
《C++ Primer Plus》可称为《C4P》或《CPx4》。

我手上的《C Primmer Plus》是人民邮电出版社2005年出版的《C2P》第五版中文版。
下面是一些笔记和一些课后编程练习的尝试解答，希望对你有所帮助。 ^_^

# 笔记

## 第1章 概览

学习内容提要：

- C的历史和特性。
- 编写程序所需的步骤。
- 关于编译器和链接器的一些知识。
- C的标准。

### C语言的起源

> C语言主要是由贝尔电话实验室的丹尼斯·M·里奇（Dennis M.Ritchie）开发的，从1969年开始设计并于1973年开发完成。……它是一种早期的程序设计语言B语言的后继者。B是BCPL（Basic CPL）语言的一种精简版本，而BCPL来源于CPL（Combined Programming Language）。
> 
> 参见[《编码》](history/《编码：隐匿在计算机软硬件背后的语言》.md)396页

> 自由的代价是永远的谨慎。

### 历史上著名的公司

- Microsoft
- Borland		宝蓝公司
- Metrowerks	出品CodeWorriors
- Digital Mars	出品Digital Mars C/C++编译器

### C语言标准

《C2P》（第五版）介绍的是C99标准，时至今日，所有现代的编译器都支持C99标准。
C语言也迎来了比C99更新的标准——C11标准。
编译器对C语言标准的支持可以在[CPP Reference][cppreference]网站上查询。

[cppreference]: http://en.cppreference.com/w/

## 第2章 C语言概述

学习内容提要：

- 运算符 =
- 函数 main() printf()
- 编写一个简单的C程序。
- 创建整形变量，为其赋值，并在屏幕上显示该值。
- 换行字符。
- 如何在程序中加入注释，建立包含多个程序的内容，以及找出程序中的错误。
- 理解什么是关键字。

### main() 函数

推荐使用`int main(void){ // body }`形式的main()函数：

- void main(){}不符合C语言标准。
- main(){}不符合C99标准。
- int main(){}能编译运行，但它不是标准的C语言形式。

参见[CPP Reference网站中关于main()函数的内容](http://en.cppreference.com/w/c/language/main_function)。

### 标识符（biāo zhì fú, identifier）

C语言的标识符可使用小写字母、大写字母、下划线和数字，不能以数字开头，以避免与数值常量混用。

推荐使用字母作为变量名的开头，把下划线留给标准库使用。

### 关键字

如果一个字符序列不能用作标识符，那么它是一个关键字（keyword）。
如果一个字符序列不应当用作标识符，那么他是一个保留标识符（reserved identifier）。

从这个角度看，main和function都不是C语言的标识符，int和char是C语言的标识符。

## 第3章 数据和C

学习内容提要：

- 关键字 int, short, long, unsigned, char, float, double, _Bool, _Complex, _Imaginary
- 运算符 sizeof
- 函数 scanf()
- C使用的基本数据类型
- 整数类型和浮点数类型的区别
- 对上述类型，如何书写常量和声明变量。
- 使用printf()和scanf()函数读写各种类型数据的值。

# 章节编程练习

## 第2章

### 练习1：输出姓名

```
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

### 练习2：输出姓名和地址

```
#include <stdio.h>

int main(void)
{
	printf("John Lightyears\n");
	printf("Guangzhou University, 230 Central West Road, Panyu District, Guangzhou");

	return 0;
}

```

### 练习3：输出年龄

```
#include <stdio.h>

int main(void)
{
	int age = 18;
	int days = age * 365;
	printf("我今年%d岁，我生活了%d天。", age, days);

	return 0;
}

```

### 练习4：输出重复的句子

```
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

### 练习5：练习使用变量

```
#include <stdio.h>

int main(void)
{
	int toes = 10;
	printf("toes is %d, and toes and toes is %d.\n", toes, toes + toes);
	printf("toes' square is %d.", toes * toes);

	return 0;
}

```

### 练习6：练习使用函数

```
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

### 练习7：练习使用函数（2）

```
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
