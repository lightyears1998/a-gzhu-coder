《C Primmer Plus》是很好的C语言入门自学指南。

《C Primmer Plus》可称为《C2P》或《CPx2》；
《C++ Primer Plus》可称为《C4P》或《CPx4》。

人民邮电出版社于2005年出版了《C2P（第五版）中文版》，于2016年4月出版了《C2P（第六版）中文版》。
第五版内容涵盖了C99标准，第六版的内容针对C11标准进行了全面更新。如果你想购买《C2P》，建议购买最新的第六版。

下面是第五版的一些笔记和一些课后编程练习的尝试解答，希望对你有所帮助。 ^_^

> 自由的代价是永远的谨慎。

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

对于浮点数，无后缀字面值总是被认定为double或更高精度的类型。要对float变量赋值，建议使用F后缀。

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
- 在赋值语句中，计算的最后结果被转换成被赋值的变量的类型（可能导致降级）。

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

`while (expression) statement;`

*statement*部分既可以是带有分号的简单语句，也可以是使用花括号包围的一个复杂语句，也可以是一条空语句。

只有*expresion*为真，*statement*才会执行。

空语句示例：

```c
while( scanf("%d", &num) == 1 )
	/* 跳过整数输入 */
;

```

### for循环

`for(ctrl_1; ctrl_2; ctrl_3) statement;`

控制表达式1在循环开始前执行；控制表达式2为真时开始一次迭代；控制表达式3在一次迭代完成后执行。

### do while循环

`do statement while(expression);`

### 循环辅助手段

- *continue* 循环的其余部分被忽略，开始下一次循环；对于for循环，从控制段的更新部分开始；对于while循环，从判断循环表达式开始。
- *break* 跳出一层循环；对于for循环，不执行控制段的更新部分。

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

### if... else...

`if(epression) statement`

`if(expression) statement1 else statement2`

`if(expression1) staement1 else if(expression2) statement2 else statement3`

### 与、或、非

- && 与
- || 或
- ! 非

可以使用iso646.h改变拼写逻辑运算符的方法：

- and 与
- or 或
- not 非

关系运算符优先级高于逻辑运算符。非运算符的优先级高于与运算符，或运算符优先级最低。与运算符和或运算符标志一个顺序点。

### 条件运算符 ?:

`expression 1 ? expression2 : expression3`

### 多重选择 switch

```
switch(integer expression)
{
	case constant1:
		statements
		break;
	case constant2:
		statements
		break;
	default:
		statements
}
```

case标签必须为整型。如果没有break标签，匹配标签之后的语句都会被执行，直到遇到break标签或switch结构结束。

### goto

`label: statement`

`goto label;`

## 第8章 字符输入/输出和输入确认

学习内容提要：

- 有关输入、输出以及缓冲和非缓冲输入之间的区别的更多内容。
- 从键盘模拟文件结尾的办法。
- 如何重定向将您的程序与文件相连接。
- 使用户界面更加友好。

### 缓冲区

缓冲分两种：完全缓冲（fully buffered）I/O和行缓冲（line-buffered）I/O。完全缓冲在缓冲区满时被清空，行缓冲在遇到换行符时清空。

### EOF

在Windows上模拟：Ctrl + Z

在Linux上模拟：Ctrl + D

### 操作系统重定向输入

- `命令 < 输入流 > 输出流`
- `命令 >> 输出流` 往现有文件末尾追加数据
- `前一个命令 | 后一个命令` 将前一个命令的输出作为后一个命令的输入

### 良好用户界面

使用单字符IO工具

```c
while((ch = getchar()) != 'q'){
	putchar(ch);
}

```

剔除错误的输入

```c
int input;
char ch;
while(scanf("%d", &input) != 1)
{
	while((ch = getchar)!='\n'){
		putchar(ch); // 剔除错误的输入
	}
	printf(" is not an integer.\n");
}

```

要创建良好的用户界面，需要注意 *scanf()* 总是将空白输入留在输入流中，在遇到EOF时，函数返回EOF，而且不改变参数的值；*getchar()* 在遇到EOF时返回EOF。

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

### 函数原型

`retrun-type function-name(arguments-list);`

函数原型中函数的参数可以省略变量名。

### 形式参数与实际参数

函数定义中头部的参数是形式参数，函数调用时使用的参数是实际参数。实参复制给形参。实参与形参相互独立。

### 函数声明

函数可以在全局声明也可以在函数中声明。在函数中声明的函数在全局有效。函数在调用前需要先声明。

函数可以声明为无参数或不确定参数。

### 递归

函数可以递归调用。在return语句之前的递归称为尾递归。

## 第10章 数组和指针

学习内容提要：

- 关键字：*static*
- 运算符：*&\*（一元）*
- 创建与初始化数组的方法。
- 指针（基于已学的基础知识）及指针和数组间的关系。
- 编写使用数组的函数。
- 二维数组。

### 数组

声明和初始化：

`type identifer[N] = {elem1, elem2, ..., elemN};`

`N`可被省略，编译器将根据指定元素的个数初始化数组；部分初始化数组，数组其余元素会被自动初始化为0。

使用`{[1]=elem1, ..., elemN}`语法来指定初始化。如果指定初始化元素后有更多元素，则它们被用于后续数组元素的初始化。如果多次对一个元素初始化，最后一次有效。

使用花括号对数组初始化的语法仅在数组声明时有效。不能将数组作为一个整体进行赋值。

#### 多维数组

`type identifier[X][Y];`

*identifier* 是一个由x个元素组成的数组，而它的每一个元素是y个type类型元素组成的数组。

可以使用花括号语法声明和初始化数组：

```c
type identifier[X][Y] = {
	{elem11, elem12, elem13, ..., elem1y},
	{elem21, elem22, elem23, ..., elem2y},
	...,
	{elemx1, elemx2, elemx3, ..., elemxy}
}
```

使用花括号声明时也可以去掉内部的花括号，前面的元素优先得到赋值。

使用指针操作多维数组，复杂度随数组维数的增加而增加。地址的地址和指针的指针是双重间接（double indirection）的一个典型例子。

区分指针的数组和数组的指针。`int * ptr[2]`是有两个int类型指针的数组而`int (* ptr) [2]`是指向一个拥有两个int类型数据的数组的指针。方括号的结合性高于*（可以借助“靠近标识符的先结合”来判断类型）。

`ptr[2]` 是一个含有两个元素的数组 → `* ptr[2]` 是一个含有两个元素的数组，数组的元素是指针 → `int * ptr[2]` 是一个含有两个元素的数组，数组的元素是指向int类型数据的指针；

`(* ptr)` 是一个指针 → `(* ptr) [2]` 是一个指针，指向拥有两个元素的数组 → `int (* ptr) [2]` 是一个指针，指向拥有两个int类型元素的数组。

#### 声明数组参数

在声明形参时，可以使用`int ar[]`代替`int * ar`。使用这样的形式可以提示 *ar* 是指向int数组中一个元素的指针。无论怎样声明，处理数组的函数实际上是使用指针作为形式参数的。

如果不希望改变数组内容，可以用*const*修饰形参中的指向数组的指针。

声明处理多维数组的函数的形式参数，可以使用`int (* ptr) [n][x][y]`和它的等价形式`int ptr[][x][y]`（第一个方括号留空表示它是指针，如果第一个方括号没有留空，效果上等价于留空的）。

#### 变长数组（VLA）

变长数组必须是自动储存类的（也就必须在函数内部或者），不能在初始化时进行声明。

声明处理变长数组的函数，变长数组参量需要在数组之前声明。如`int sum2d(int rows, int cols, int ar[rows][cols]);`，可以省略一般形参的名称和边长数组的维数，如`int sum2d(int, int, int ar[*][*]);`

### 指针

地址运算符 &

间接运算符 *

`ptr = &bah; val = * ptr;` 等价于 `val = bah;`

使用 `type * identifier;` 来声明指针。

不要对未初始化的指针取值。

自增运算符与间接运算符存在微妙的优先级关系，试区分`*ptr++`、`*++ptr`、`*(ptr++)`、`*(++ptr)`和`(*ptr)++`。其中`*ptr++`等价于`*(ptr++)`。

使指针自增1，指针指向下一个储存单元（而不是下一个字节）。

如果指针被*const*修饰，那么指针指向的数据不应该被改变。不能把*const*指针赋给非*const*指针（这样指针指向的数据可能会改变），但可以把非*const*指针赋给*const*指针，前提是只进行一层间接运算（即被赋值的*const*指针不能是指针的指针）。

下面的例子演示了如果忽略上述前提，在双重间接的情况下*const*内容被修改的例子：

```c
const int ** pp;
int * p;
const int n = 10;

pp = &p;	// 不允许
*pp = &n;	// 使p指向n
*p = 11;	// n被修改
```

#### 基本操作

- **赋值（Assignment）** 将地址赋给指针，可以使用地址运算符或数组名。还可以使用类型指派来为不兼容的指针赋值。
- **求值（value-finding）或取值(derefering)** 使用间接运算符。
- **取指针地址** 使用地址运算符。
- **指针的整数加法和减法**
- **求差值（differencing）** 差值的单位是相应类型的大小，而不是字节。有效差值运算的前提是两个指针指向同一个数组
- **比较** 可以使用关系运算符比较两个相同类型的指针。

一个指针不能另一个指针相加或相乘。

#### 指针与数组

在表达式中使用数组名，等同于使用该数组首元素的地址，即数组名是指向首元素的（只读）指针。

指针变量和数组标识符都可以使用方括号语法和指针语法：`ar[n]`等价于`*(ar + n)`。区别在于，指针可以通过自增自减运算符（如`ar++`）来修改指向的地址，而数组名虽是指针，却是指向数组首元素的只读指针，不能被修改，即`ar++`是无效的。

### 复合文字

复合文字（Compound literal）是表示数组和结构内容的字面值。它没有标识符。

```c
(int [2]){1, 2}
```

上面的表达式创建了一个含有2个int元素的数组。表达式的值是指向数组首元素的指针。

可以省略元素的个数：

```c
(int []){1, 2, 3}
```

也适用于多维数组，但只能省略第一个维度。

```c
(int [][4]){{1, 2, 3, 4}, {5, 6, 7, 8}}
```

可以使用复合文字初始化一个指针，或者使用复合文字作为实际参数传递给参量形式匹配的函数。

## 第11章 字符串和字符串函数

学习内容提要：

- 函数：*gets() puts() strcat() strncat() strcmp() strncmp() strcpy() sprintf() strchr()*
- 创建和使用字符串。
- 利用C库里的字符串和字符函数创建您自己的字符串函数。
- 使用命令行参数。

> 绝大多数程序员认为这很搞笑，但仅限于这出现在别人的程序中时。

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

> 在某种程度上，学习一门计算机语言和学习音乐、木工或工程技术是一样的。首先，您要学会使用行业工具。要学会演奏各个音阶；要了解锤子的哪一端是用来握的，哪一端是要小心的；要能解决涉及降落、滑坡以及平衡物体之类的不计其数的问题。到现在为止，您一直在学习和实践各种技能，比如创建变量、结构、函数等。但是，最后您将提升到一个更高的层次。在这个层次上，使用工具是次要的，真正的挑战是设计和创建一个工程。您将学会将工程视为一个整体。本章涉及的内容可能比前些章节中的内容要略微难一些，但是您会发现它更有价值，因为它将帮助您从初学者成长为熟练的程序员。

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

## 第7章

### 练习7.1：字符统计程序

```c
#include <stdio.h>

int main(void)
{
	char ch;
	int space=0, enter=0, other=0;
	while(ch=getchar(), ch!='#')
	{
		if(ch==' '){
			space++;
			continue;
		}
		if(ch=='\n'){
			enter++;
			continue;
		}
		other++;
	}
	printf("Space: %d, Enter: %d, Other: %d\n", space, enter, other);

	return 0;
}

```

### 练习7.2：字符统计（2）

```c
#include <stdio.h>

int main(void)
{
	char ch;
	int ascii, count=0;
	while(ch=getchar(), ch!='#')
	{
		ascii = ch;
		printf("[%c] %03d ", ch, ascii);
		count++;
		if(count%8==0){
			putchar('\n');
		}
	}

	return 0;
}

```

### 练习7.3：奇偶统计

```c
#include <stdio.h>

int main(void)
{
	int odd_count=0, odd_sum=0;
	int even_count=0, even_sum=0;
	int current;
	while(scanf("%d", &current), current!=0)
	{
		if(current%2!=0){
			odd_count++;
			odd_sum += current;
		}else{
			even_count++;
			even_sum += current;
		}
	}

	if(odd_count!=0){
		printf("[Odd]\tCount: %d Average: %f\n", odd_count, (float)odd_sum/odd_count);
	}else{
		printf("[Odd]\tCount: %d Average: Not Exist\n", odd_count);
	}
	if(even_count!=0){
		printf("[Even]\tCount: %d Average: %f\n", even_count, (float)even_sum/even_count);
	}else{
		printf("[Even]\tCount: %d Average: Not Exist\n", even_count);
	}

	return 0;
}

```

### 练习7.4：惊叹替身

```c
#include <stdio.h>

int main(void)
{
	int count=0;
	char ch;
	while(ch=getchar(), ch!='#')
	{
		if(ch=='!'){
			printf("!!");
			count++;
			continue;
		}
		if(ch=='.'){
			putchar('!');
			count++;
			continue;
		}
		putchar(ch);
	}
	printf("\nReplacement: %d\n", count);

	return 0;
}

```

### 练习7.5：使用switch重写练习7.3

```c
#include <stdio.h>

int main(void)
{
	int odd_count=0, odd_sum=0;
	int even_count=0, even_sum=0;
	int current;
	while(scanf("%d", &current), current!=0)
	{
		switch(current%2)
		{
			case 1:{
				odd_count++;
				odd_sum += current;
				break;
			}
			case 0:{
				even_count++;
				even_sum += current;
				break;
			}
		}
	}

	switch(odd_count)
	{
		case 0:{
			printf("[Odd]\tCount: %d Average: Not Exist\n", odd_count);
			break;
		}
		default:{
			printf("[Odd]\tCount: %d Average: %f\n", odd_count, (float)odd_sum/odd_count);
		}
	}
	switch(even_count)
	{
		case 0:{
			printf("[Even]\tCount: %d Average: Not Exist\n", even_count);
			break;
		}
		default:{
			printf("[Even]\tCount: %d Average: %f\n", even_count, (float)even_sum/even_count);
		}
	}

	return 0;
}

```

### 练习7.6：“诶”检测

```c
#include <stdio.h>

int main(void)
{
	char ch=0, pass=0;
	int count=0;
	while(ch=getchar(), ch!='#')
	{
		if(pass=='e'&&ch=='i'){
			count++;
		}
		pass = ch;
	}
	printf("\nSequence count: %d\n", count);

	return 0;
}

```

### 练习7.7：工资问题

```c
#include <stdio.h>

#define BASIC_PAY_GRADE 10
#define OVERTIME 40
#define OVERTIME_PAY_GRADE BASIC_PAY_GRADE * 1.5F
#define TAX_CLASS1 300
#define TAX_CLASS2 150
#define TAX_CLASS1_RATE 0.15F
#define TAX_CLASS2_RATE 0.2F
#define TAX_CLASS3_RATE 0.15F

int main(void)
{
	int hour;
	float pay;
	scanf("%d", &hour);

	if(hour<=OVERTIME){
		pay = hour * BASIC_PAY_GRADE;
	}else{
		pay = OVERTIME * BASIC_PAY_GRADE + (hour-OVERTIME) * OVERTIME_PAY_GRADE;
	}

	if(pay<=TAX_CLASS1){
		pay *= 1-TAX_CLASS1_RATE;
	}else if(pay<=TAX_CLASS2){
		pay = TAX_CLASS1 * (1-TAX_CLASS1_RATE) + (pay-TAX_CLASS1) * (1-TAX_CLASS2_RATE);
	}else{
		pay = TAX_CLASS1 * (1-TAX_CLASS1_RATE)
			+ TAX_CLASS2 * (1-TAX_CLASS2_RATE)
			+ (pay-TAX_CLASS1-TAX_CLASS2) * (1-TAX_CLASS3_RATE)
		;
	}

	printf("Income: $%.2f\n", pay);

	return 0;
}

```

### 练习7.8：工资问题（2）

```c
#include <stdio.h>

#define OVERTIME 40
#define OVERTIME_PAY_GRADE basic_pay_grade * 1.5
#define TAX_CLASS1 300
#define TAX_CLASS2 150
#define TAX_CLASS1_RATE 0.15
#define TAX_CLASS2_RATE 0.2
#define TAX_CLASS3_RATE 0.15

void print_menu(void);

int main(void)
{
	int hour;
	float basic_pay_grade, pay;
	int input;

	loop:
	print_menu();
	while(scanf("%d", &input), input!=5){
		switch(input)
		{
			case 1:
				basic_pay_grade = 8.75;
				break;
			case 2:
				basic_pay_grade = 9.33;
				break;
			case 3:
				basic_pay_grade = 10;
				break;
			case 4:
				basic_pay_grade = 11.2;
				break;
			default:
				printf("Sorry, I can only understand 1 to 5.\n");
				goto loop;
		}
		printf("Enter working hours: ");
		scanf("%d", &hour);

		if(hour<=OVERTIME){
			pay = hour * basic_pay_grade;
		}else{
			pay = OVERTIME * basic_pay_grade + (hour-OVERTIME) * OVERTIME_PAY_GRADE;
		}
	
		if(pay<=TAX_CLASS1){
			pay *= 1-TAX_CLASS1_RATE;
		}else if(pay<=TAX_CLASS2){
			pay = TAX_CLASS1 * (1-TAX_CLASS1_RATE) + (pay-TAX_CLASS1) * (1-TAX_CLASS2_RATE);
		}else{
			pay = TAX_CLASS1 * (1-TAX_CLASS1_RATE)
				+ TAX_CLASS2 * (1-TAX_CLASS2_RATE)
				+ (pay-TAX_CLASS1-TAX_CLASS2) * (1-TAX_CLASS3_RATE)
			;
		}
	
		printf("Income: $%.2f\n", pay);
		print_menu();
	}

	return 0;
}

void print_menu(void)
{
	printf("*****************************************************************\n");
	printf("Enter the number corresponding to the desired pay rate or action:\n");
	printf("1) $8.75/hr                     2) $9.33/hr                      \n");
	printf("3) $10.00/hr                    4) $11.20/hr                     \n");
	printf("5) quit                                                          \n");
	printf("*****************************************************************\n");
}

```

### 练习7.9：素数问题

```c
#include <stdio.h>

int main(void)
{
	int num;
	scanf("%d", &num);

	if(num>=1){
		printf("1 ");
	}
	for(int i=2; i<=num; i++)
	{
		int count=0;
		for(int a=1; a<=i; a++){
			if(i%a==0){
				count++;
			}
		}
		if(count==2){
			printf("%d ", i);
		}
	}

	printf("\n");

	return 0;
}

```

### 练习7.10：征税问题

```c
#include <stdio.h>

int query_classifacation(void);
double query_income(void);
double calc_after_tax(double income, double class_1);

int main(void)
{
	int status, class;
	while(class=query_classifacation())
	{
		double income, after_tax;
		switch(class)
		{
			case 1:
				income = query_income();
				after_tax = calc_after_tax(income, 17850);
				printf("您的税后收入为$%.2lf\n", after_tax);
				break;
			case 2:
				income = query_income();
				after_tax = calc_after_tax(income, 23900);
				printf("您的税后收入为$%.2lf\n", after_tax);
				break;
			case 3:
				income = query_income();
				after_tax = calc_after_tax(income, 29750);
				printf("您的税后收入为$%.2lf\n", after_tax);
				break;
			case 4:
				income = query_income();
				after_tax = calc_after_tax(income, 14875);
				printf("您的税后收入为$%.2lf\n", after_tax);
				break;
			default:
				printf("对不起，不能理解您的输入。");
				break;
		}
	}

	return 0;
}

int query_classifacation(void)
{
	int class, status;
	printf("请问您属于哪一种劳动者？\n");
	printf("1）单身 2）户主 3）已婚，共有 4）已婚，离异\n");
	status = scanf("%d", &class);
	if(status==EOF){
		return 0;
	}else{
		return class;
	}
}

double query_income(void)
{
	double income;
	printf("请输入您的应缴税收入：$");
	scanf("%lf", &income);
	return income;
}

double calc_after_tax(double income, double class_1)
{
	double after_tax;
	if(income<=class_1){
		after_tax = income * (1-0.15);
	}else{
		after_tax = class_1 * (1-0.15) + (income-class_1) * (1-0.28);
	}
	return after_tax;
}

```

### 练习7.11：蔬果订单

```c
#include <stdio.h>

int artichoke;
int sugerbeet;
int carrot;

void print_menu(void);

int main(void)
{
	artichoke = sugerbeet = carrot = 0;
	print_menu();

	char ch;
	while((ch=getchar())!='q'){
		switch(ch)
		{
			case 'a':
				printf("您正在修改朝鲜蓟订单： ");
				scanf("%d", &artichoke);
				print_menu();
				break;
			case 'b':
				printf("您正在修改甜菜订单： ");
				scanf("%d", &sugerbeet);
				print_menu();
				break;
			case 'c':
				printf("您正在修改胡萝卜订单： ");
				scanf("%d", &carrot);
				print_menu();
				break;
			case '\n':
				break;
			default:
				printf("对不起，无法理解您的输入。\n");
				print_menu();
				break;
		}
	}

	double fee = artichoke * 1.25 + sugerbeet * 0.65 + carrot * 0.89;
	double discount = 0;
	double transport = 0;
	int pounds = artichoke + sugerbeet + carrot;
	
	if(fee>=100){
		discount = fee * 0.05;
		fee *= 0.95;
	}
	if(pounds<=5){
		transport = 3.5;
	}else if(pounds<20){
		transport = 10;
	}else{
		transport = 8 + pounds * 0.1;
	}

	printf("朝鲜蓟\t$1.25/pound\t*\t%d\t=\t%.2lf\n", artichoke, (double)artichoke * 1.25);
	printf("甜菜\t$0.65/pound\t*\t%d\t=\t%.2lf\n", sugerbeet, (double)sugerbeet * 0.65);
	printf("胡萝卜\t$0.89/pound\t*\t%d\t=\t%.2lf\n", carrot, (double)carrot * 0.89);
	printf("蔬果总价格\t$%.2lf\n", fee);
	printf("折扣\t\t$%.2lf\n", discount);
	printf("运输费用\t$%.2lf\n", transport);
	printf("订单总价格\t$%.2lf\n", fee+transport);

	return 0;
}

void print_menu(void)
{
	printf("***** 订单状态 ****************\n");
	printf("a) 朝鲜蓟 \t %d\n", artichoke);
	printf("b) 甜菜 \t %d\n", sugerbeet);
	printf("c) 胡萝卜 \t %d\n", carrot);
	printf("***** 订单状态 ****************\n");
	printf("q) 订单结算\n");
}

```

### 练习8.1：字符统计程序

```c
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char ch;
	int count=0;
	while((ch=getchar()) != EOF)
	{
		if(isspace(ch)){
			continue;
		}
		count++;
	}
	printf("Count: %d", count);

	return 0;
}

```
### 练习8.2：回显字符

```c
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char ch;
	int count=0;
	while((ch=getchar()) != EOF)
	{
		count++;
		if(isprint(ch)){
			printf("[ %c] %03hhd", ch, ch);
		}else if(isblank(ch)){
			switch(ch){
				case ' ': 
					printf("[  ] %03hhd", ' ');
					break;
				case '\t':
					printf("[\\t] %03hhd", '\t');
					break;
				case '\n':
					printf("[\\n] %03hhd", '\n');
					break;
			}
		}else{
			printf("[^%c] %03hhd", ch+64, ch);
		}
		if(count%10==0){
			putchar('\n');
		}else{
			putchar(' ');
		}
	}

	putchar('\n');
	return 0;
}

```

### 练习8.3：统计大小写

```c
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char ch;
	int upper=0, lower=0;
	while((ch=getchar()) != EOF)
	{
		if(isupper(ch)){
			upper++;
			continue;
		}	
		if(islower(ch)){
			lower++;
			continue;
		}
	}
	printf("Upper: %d Lower:%d\n", upper, lower);

	return 0;
}

```

### 练习8.4：统计平均字母数

```c
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int main(void)
{
	char ch;
	int total = 0, count = 0;
	bool inword = false;
	while((ch=getchar()) != EOF)
	{
		if(isalpha(ch))
		{
			if(inword){
				total++;
			}else{
				inword = true;
				total++;
				count++;
			}
		}else{
			inword = false;
		}
	}
	printf("Total characters: %d Words: %d Average: %.2lf\n", total, count, (double)total/count);

	return 0;
}

```

### 练习8.5：二分猜测

```c
#include <stdio.h>

int main(void)
{
	int min=1, max=100;
	int guess = min+(max-min)/2;
	printf("Pick an integer from 1 to 100. I will try to guess "
		"it.\nRespond with a y if my guess is right and with"
		"\na b if your number is bigger than my guess.\n"
		"Respond with a s if your number is smaller than my guess.\n"
	);
	printf("Uh...is your number %d?\n", guess);

	char ch;
	while((ch=getchar())!='y')
	{
		while(getchar()!='\n'){
			continue;
		}
		if(ch=='b'){
			min=guess;
			guess = min+(max-min)/2;
			printf("Well, then, is it %d?\n", guess);
		}else if(ch=='s'){
			max=guess;
			guess = min+(max-min)/2;
			printf("Well, then, is it %d?\n", guess);
		}else{
			printf("Sorry, I understand only y, b or s.\n");
		}
	}
	printf("I knew I could do it!\n");

	return 0;
}

```

### 练习8.6：返回非空字符

```c
#include <stdio.h>
#include <ctype.h>

char get_first(void);

int main(void)
{
	putchar(get_first());
	putchar('\n');

	return 0;
}

char get_first(void)
{
	char ch;

	while(ch=getchar())
	{
		if(isblank(ch)){
			continue;
		}
		return ch;
	}
}

```

### 练习8.7：数字菜单

```c
#include <stdio.h>
#include <stdbool.h>

#define OVERTIME 40
#define OVERTIME_PAY_GRADE basic_pay_grade * 1.5F
#define TAX_CLASS1 300
#define TAX_CLASS2 150
#define TAX_CLASS1_RATE 0.15F
#define TAX_CLASS2_RATE 0.2F
#define TAX_CLASS3_RATE 0.15F

void print_menu(void);

int main(void)
{
	int hour;
	float basic_pay_grade, pay;
	int input;

	print_menu();
	while(input=getchar(), input!=EOF && input!='q')
	{
		hour = 0;
		bool flag = true;
		while(flag)
		{
			while(getchar()!='\n'){
				continue;
			}

			switch(input)
			{
				case 'a':
					basic_pay_grade = 8.75F;
					flag = false;
					break;
				case 'b':
					basic_pay_grade = 9.33F;
					flag = false;
					break;
				case 'c':
					basic_pay_grade = 10F;
					flag = false;
					break;
				case 'd':
					basic_pay_grade = 11.2F;
					flag = false;
					break;
				default:
					printf("Sorry, I can only understand a, b, c, d or q.\n");
					break;
			}
			break;
		}

		if(flag){
			continue;
		}else{
			flag = true;
		}

		printf("Enter working hours: ");
		while(scanf("%d", &hour)!=EOF)
		{
			if(hour>0){
				while(getchar()!='\n'){
					continue;
				}
				break;
			}else{
				char ch;
				printf("Please enter number other than ");
				while((ch=getchar())!='\n')
				{
					putchar(ch);
				}
				printf(": ");
			}
		}

		if(hour<=OVERTIME){
			pay = hour * basic_pay_grade;
		}else{
			pay = OVERTIME * basic_pay_grade + (hour-OVERTIME) * OVERTIME_PAY_GRADE;
		}
	
		if(pay<=TAX_CLASS1){
			pay *= 1-TAX_CLASS1_RATE;
		}else if(pay<=TAX_CLASS2){
			pay = TAX_CLASS1 * (1-TAX_CLASS1_RATE) + (pay-TAX_CLASS1) * (1-TAX_CLASS2_RATE);
		}else{
			pay = TAX_CLASS1 * (1-TAX_CLASS1_RATE)
				+ TAX_CLASS2 * (1-TAX_CLASS2_RATE)
				+ (pay-TAX_CLASS1-TAX_CLASS2) * (1-TAX_CLASS3_RATE)
			;
		}
	
		printf("Income: $%.2f\n", pay);
		print_menu();
	}

	return 0;
}

void print_menu(void)
{
	printf("*****************************************************************\n");
	printf("Enter the number corresponding to the desired pay rate or action:\n");
	printf("a) $8.75/hr                     b) $9.33/hr                      \n");
	printf("c) $10.00/hr                    d) $11.20/hr                     \n");
	printf("q) quit                                                          \n");
	printf("*****************************************************************\n");
}

```

### 练习8.8：加减乘除

```c
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

char get_operation(void);
void eat_line(void);
float get_first_number(void);
float ger_second_number(bool ac_zero);
void echoing(void);
void add(void);
void subtract(void);
void multiply(void);
void divide(void);

int main(void)
{
	char operation;
	for(;;){
		operation = get_operation();
		switch(operation)
		{
			case 'a': add(); break;
			case 's': subtract(); break;
			case 'm': multiply(); break;
			case 'd': divide(); break;
			case 'q': goto finishing;
		}
	}

	finishing:
	return 0;
}

void echoing(void)
{
	int ch;
	while((ch=getchar()!='\n')){
		putchar(ch);
	}
}

void eat_line(void)
{
	while(getchar()!='\n'){
		continue;
	}
}

char get_operation(void)
{
	printf("Enter the operation of your choice:\n");
	printf("a. add          s. subtract\n");
	printf("m. multiply     d. divide\n");
	printf("q. quit\n");
	
	int ch;
	for(;;)
	{
		ch = getchar();
		if(isblank(ch)){
			continue;
		}
		eat_line();
		if(ch=='a'||ch=='s'||ch=='m'||ch=='d'||ch=='q'){
			break;
		}else{
			printf("Sorry, I understand only a, s, m, d and q.\n");
		}
	}
	return (char)ch;
}

float get_first_number(void)
{
	float number;
	int status;

	printf("Enter first number: ");
	for(;;)
	{
		status = scanf("%g", &number);
		if(status==EOF){
			printf("Something was wrong. Please try again: ");
			continue;
		}else if(status==0){
			echoing(); printf(" is not a number.\n");
			printf("Please enter a number, such as 2.5, -1.78E8 or 3: ");
			continue;
		}
		eat_line();
		break;
	}

	return number;
}

float get_second_number(bool ac_zero)
{
	float number;
	int status;

	printf("Enter second number: ");
	for(;;)
	{
		status = scanf("%g", &number);
		if(status==EOF){
			printf("Something was wrong. Please try again: ");
			continue;
		}else if(status==0){
			echoing(); printf(" is not a number.\n");
			printf("Please enter a number, such as 2.5, -1.78E8 or 3: ");
			continue;
		}
		if(!ac_zero&&number==0){
			printf("Enter a number other than 0: ");
			continue;
		}
		eat_line();
		break;
	}

	return number;
}

void add(void)
{
	float a = get_first_number();
	float b = get_second_number(true);
	printf("%g + %g = %g\n", a, b, a+b);
}

void subtract(void)
{
	float a = get_first_number();
	float b = get_second_number(true);
	printf("%g - %g = %g\n", a, b, a-b);
}

void multiply(void)
{
	float a = get_first_number();
	float b = get_second_number(true);
	printf("%g * %g = %g\n", a, b, a*b);
}

void divide(void)
{
	float a = get_first_number();
	float b = get_second_number(false);
	printf("%g / %g = %g\n", a, b, a/b);
}

```

## 第9章

### 练习9.1：较小数值

```c
#include <stdio.h>

double min(double x, double y);

int main(void)
{
	printf("%lg\n", min(1, 2));
	printf("%lg\n", min(2.1E4, 2.22));
	printf("%lg\n", min(232.12, 3212));

	return 0;
}

double min(double x, double y)
{
	if(x<=y){
		return x;
	}else{
		return y;
	}
}

```

### 练习9.2：指定字符输出

```c
#include <stdio.h>

void chline(char ch, int i, int j);

int main(void)
{
	chline('*', 3, 5);

	return 0;
}

void chline(char ch, int i, int j)
{
	for(int k=1; k<=j; k++)
	{
		if(k>=i){
			putchar(ch);
		}else{
			putchar(' ');
		}
	}
	putchar('\n');
}

```

### 练习9.3：横行竖伍

```c
#include <stdio.h>

void say_words(char ch, int i, int j);

int main(void)
{
	say_words('*', 3, 5);

	return 0;
}

void say_words(char ch, int i, int j)
{
	while(j--){
		int k = i;
		while(k--){
			putchar(ch);
		}
		putchar('\n');
	}
}

```

### 练习9.4：谐均值

```c
#include <stdio.h>

double harmonic(double a, double b);

int main(void)
{
	printf("%lg\n", harmonic(1, 1));
	printf("%lg\n", harmonic(22, 23));
	printf("%lg\n", harmonic(443, 334));

	return 0;
}

double harmonic(double a, double b)
{
	return 1/((1/a + 1/b)/2);
}

```

### 练习9.5：与大同大

```c
#include <stdio.h>

void larger_of(double * a, double * b);

int main(void)
{
	double a = 121.1;
	double b = 221.9;
	larger_of(&a, &b);
	printf("%lg %lg", a, b);

	return 0;
}

void larger_of(double * a, double * b)
{
	if(*a<=*b){
		*a=*b;
	}else{
		*b=*a;
	}
}

```

### 练习9.6：字母数值报告

```c
#include <stdio.h>
#include <ctype.h>

int get_index(char ch);

int main(void)
{
	int ch;
	int count = 0;
	while((ch=getchar())!=EOF)
	{
		int index = get_index((char)ch);
		if(index>=1){
			printf("Y[%02d]", index);
		}else{
			printf("N[  ]");
		}
		count++;
		if(count%10){
			putchar('\t');
		}else{
			putchar('\n');
		}
	}

	return 0;
}

int get_index(char ch)
{
	ch = (char)toupper(ch);
	int index = ch - 'A' + 1;
	if(index<1){
		return -1;
	}else{
		return index;
	}
}

```

### 练习9.7：循环计算幂

```c
#include <stdio.h>
#include <math.h>

double power(double base, int exponent);

int main(void)
{
	printf("%lg\n", power(1, 1));
	printf("%lg\n", power(0, 1));
	printf("%lg\n", power(0, 0));
	printf("%lg\n", power(2, 0));
	printf("%lg\n", power(2.1, 3));
	printf("%lg\n", power(2, -3));

	return 0;
}

double power(double base, int exponent)
{
	if(exponent==0){
		if(base==0){
			return NAN;
		}else{
			return 1;
		}
	}
	if(exponent<0){
		exponent = -exponent;
		double result = 1;
		while(exponent--){
			result *= base;
		}
		return 1/result;
	}
	if(exponent>0){
		double result = 1;
		while(exponent--){
			result *= base;
		}
		return result;
	}
	return NAN;
}

```

### 练习9.8：递归计算幂

```c
#include <stdio.h>
#include <math.h>

double power(double base, int exponent);

int main(void)
{
	printf("%lg\n", power(1, 1));
	printf("%lg\n", power(0, 1));
	printf("%lg\n", power(0, 0));
	printf("%lg\n", power(2, 0));
	printf("%lg\n", power(2.1, 3));
	printf("%lg\n", power(2, -3));

	return 0;
}

double power(double base, int exponent)
{
	if(exponent==0){
		if(base==0){
			return NAN;
		}else{
			return 1;
		}
	}
	if(exponent<0){
		exponent = -exponent;
		return 1/(base * power(base, exponent-1));
	}
	if(exponent>0){
		return base * power(base, exponent-1);
	}
	return NAN;
}

```

### 练习9.9：进制计算

```c
#include <stdio.h>

void to_base_n(int number ,int base);

int main(void)
{
	to_base_n(3, 2); putchar('\n');
	to_base_n(11, 2); putchar('\n');
	to_base_n(256, 2); putchar('\n');
	to_base_n(256, 8); putchar('\n');

	return 0;
}

void to_base_n(int number, int base)
{
	if(base<2||base>10){
		return;
	}

	int current = number % base;
	if(number/base >= base){
		to_base_n(number/base, base);
	}else{
		putchar('0' + number/base);
		putchar('0' + current);
		return;
	}
	putchar('0' + current);
}

```

### 练习9.10：斐波拉契数列

```c
#include <stdio.h>

void Fibonacci(int index);

int main(void)
{
	Fibonacci(1);
	Fibonacci(2);
	Fibonacci(10);

	return 0;
}

void Fibonacci(int index)
{
	int current = 1, next = 1;
	printf("%d", current);
	while(--index){
		putchar(' ');
		next += current;
		current = next - current; 
		//! 不要写current = -(current-=next); 副作用不明确。
		printf("%d", current);
	}
	putchar('\n');
}

```

## 第10章

### 练习10.1：

```c
#include <stdio.h>

#define MONTHS 12
#define YEARS 5

int main(void)
{
	const float rain[YEARS][MONTHS] = {
		{4.3, 4.3, 4.3, 3.0, 2.0, 1.2, 0.2, 0.2, 0.4, 2.4, 3.5, 6.6},
		{8.5, 8.2, 1.2, 1.6, 2.4, 0.0, 5.2, 0.9, 0.3, 0.9, 1.4, 7.3},
		{9.1, 8.5, 6.7, 4.3, 2.1, 0.8, 0.2, 0.2, 1.1, 2.3, 6.1, 8.4},
		{7.2, 9.9, 8.4, 3.3, 1.2, 0.8, 0.4, 0.0, 0.6, 1.7, 4.3, 6.2},
		{7.6, 5.6, 3.8, 2.8, 3.8, 0.2, 0.0, 0.0, 0.0, 1.3, 2.6, 5.2}
	};
	int year, month;
	float subtot, total;

	printf(" YEAR       RAINFALL(inches)\n");
	for(year=0, total=0; year<YEARS; year++)
	{
		for(month=0, subtot=0; month<MONTHS; month++)
		{
			subtot += *(*(rain+year) + month);
		}
		printf("%5d %15.1f\n", 2000+year, subtot);
		total += subtot;
	}

	printf("\nThe yearly average is %.1f inches.\n\n", total/YEARS);
	printf("MONTHLY AVERAGE: \n\n");
	printf(" Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec\n");

	for(month=0; month<MONTHS; month++)
	{
		for(year=0, subtot=0; year<YEARS; year++)
		{
			subtot += *(*(rain+year)+month);
		}
		printf("%4.1f", subtot/YEARS);
	}

	putchar('\n');

	return 0;
}

```

### 练习10.2：拷贝数组

```c
#include <stdio.h>

void copy_arr(double source[], double targer[], int count);
void copy_ptr(double * source, double * target, int count);

int main(void)
{
	double source[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
	double target1[5];
	double target2[5];

	copy_arr(source, target1, 5);
	copy_ptr(source, target2, 5);

	if(source[4] == target1[4] && source[3] == target2[3]){
		printf("Done.\n");
	}

	return 0;
}

void copy_arr(double source[], double target[], int count)
{
	for(int i=0; i<count; i++)
	{
		target[i] = source[i];
	}
}

void copy_ptr(double * source, double * target, int count)
{
	for(int i=0; i<count; i++)
	{
		*target = *source;
		source++;
		target++;
	}
}

```

### 练习10.3：寻找最大数

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int numbers[5] = {rand(), rand(), rand(), rand(), rand()};
	int max, count;

	printf("The numbers are ");
	for(max=numbers[0], count=0; count<5; count++)
	{
		if(numbers[count]>max){
			max = numbers[count];
		}
		printf("%d, ", numbers[count]);
	}
	printf("and the max is %d.\n", max);

	return 0;
}

```

### 练习10.4：寻找最大数的索引

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	double numbers[5] = {rand()/10.0, rand()/10.0, rand()/10.0, rand()/10.0, rand()/10.0};
	double max;
	int index, count;

	printf("The numbers are ");
	for(index=0, max=numbers[0], count=0; count<5; count++)
	{
		if(numbers[count]>max){
			max = numbers[count];
			index = count;
		}
		printf("%lg, ", numbers[count]);
	}
	printf("and the max is %lg, its index is %d.\n", max, index);

	return 0;
}

```

### 练习10.5 寻找落差

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	double numbers[5] = {rand()/10.0, rand()/10.0, rand()/10.0, rand()/10.0, rand()/10.0};
	double max, min;
	int count;

	printf("The numbers are ");
	for(max=min=numbers[0], count=0; count<5; count++)
	{
		if(numbers[count]>max){
			max = numbers[count];
		}
		if(numbers[count]<min)
		{
			min = numbers[count];
		}
		printf("%lg, ", numbers[count]);
	}
	printf("and max - min = %lg.\n", max - min);

	return 0;
}

```

### 练习10.6：复制二维数组

```c
#include <stdio.h>

void copy_arr(double source[], double targer[], int count);
void copy_ptr(double * source, double * target, int count);

int main(void)
{
	double numbers[3][4] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	double target[3][3];
	
	for(int i=0; i<3; i++)
	{
		copy_ptr(numbers[i], target[i], 4);
		for(int j=0; j<4; j++){
			// 显示复制后数组内容
			printf("%lg ", numbers[i][j]);
		}
		putchar('\n');
	}

	return 0;
}

void copy_arr(double source[], double target[], int count)
{
	for(int i=0; i<count; i++)
	{
		target[i] = source[i];
	}
}

void copy_ptr(double * source, double * target, int count)
{
	for(int i=0; i<count; i++)
	{
		*target = *source;
		source++;
		target++;
	}
}

```

### 练习10.7：复制指定的元素

```c
#include <stdio.h>

void copy_arr(double source[], double targer[], int count);
void copy_ptr(double * source, double * target, int count);

int main(void)
{
	double numbers[7] = {1, 2, 3, 4, 5, 6, 7};
	double target[3];
	copy_ptr(numbers+2, target, 3);
	printf("The copied value are %lg, %lg and %lg.\n", target[0], target[1], target[2]);

	return 0;
}

void copy_arr(double source[], double target[], int count)
{
	for(int i=0; i<count; i++)
	{
		target[i] = source[i];
	}
}

void copy_ptr(double * source, double * target, int count)
{
	for(int i=0; i<count; i++)
	{
		*target = *source;
		source++;
		target++;
	}
}

```

### 练习10.8：二维数组

```c
#include <stdio.h>

/**
 * MSVC不支持VLA，有VLA的替代方案，可以不使用VLA。
 *
 */

void vla_copy(int rows, int cols, double origin[rows][cols], double target[rows][cols]);
void vla_show(int rows, int cols, double origin[rows][cols]);

int main(void)
{
	double origin[3][5] = {
		{1, 2, 3, 4, 5},
		{6, 7, 8, 9, 10},
		{11, 12, 13, 14, 15}
	};
	double target[4][5];
	vla_copy(3, 5, origin, target);
	vla_show(4, 5, target);

	return 0;
}

void vla_copy(int rows, int cols, double origin[rows][cols], double target[rows][cols])
{
	int row, col;
	for(row=0; row<rows; row++)
	{
		for(col=0; col<cols; col++)
		{
			*(*target + col) = *(*origin + col);
		}
		origin++;
		target++;
	}
}

void vla_show(int rows, int cols, double origin[rows][cols])
{
	int row, col;
	for(row=0; row<rows; row++)
	{
		putchar('{');
		for(col=0; col<cols; col++)
		{
			printf("%lg, ", *(*origin + col));
		}
		printf("\b\b}\n");
		origin++;
	}
}

```

### 练习10.9：元素相加

```c
#include <stdio.h>

void array_add(int count, int lhs[], int rhs[], int result[]);

int main(void)
{
	int lhs[4] = {1, 2, 3, 4};
	int rhs[4] = {5, 6, 7, 8};
	int result[4];

	array_add(4, lhs, rhs, result);
	for(int i=0; i<4; i++)
	{
		printf("%d + %d = %d\n", lhs[i], rhs[i], result[i]);
	}

	return 0;
}

void array_add(int count, int lhs[], int rhs[], int result[])
{
	for(int i=0; i<count; i++){
		*result++ = *lhs++ + *rhs++;
	}
}

```

### 练习10.10：翻倍吧，数组！

```c
#include <stdio.h>
#include <stdlib.h>

// 等价声明形式
void array_show(int rows, double (* origin) [5]);
void array_double(int rows, double (* origin) [5]);

int main(void)
{
	double nums[3][5] = {
		{rand(), rand(), rand(), rand(), rand()},
		{rand(), rand(), rand(), rand(), rand()},
		{rand(), rand(), rand(), rand(), rand()}
	};

	array_show(3, nums);
	array_double(3, nums);
	array_show(3, nums);

	putchar('\n');
	double (*ptr) [5] = (double [2][5]){{1, 2, 3, 4, 5},{6, 7, 8, 9, 10}};
	array_show(2, ptr);
	array_double(2, ptr);
	array_show(2, ptr);
	
	return 0;
}

void array_show(int rows, double origin[][5])
{
	printf("{ ");
	for(int row=0; row<rows; row++)
	{
		putchar('{');
		for(int i=0; i<5; i++){
			printf("%lg, ", *(*origin+i) );
		}
		printf("\b\b}, ");
		origin++;
	}
	printf("\b\b }\n");
}

void array_double(int rows, double origin[][5])
{
	for(int row=0; row<rows; row++)
	{
		for(int i=0; i<5; i++){
			*(*origin+i) *= 2;
		}
		origin++;
	}
}

```

### 练习10.11：重构rain

```c
#include <stdio.h>

#define MONTHS 12
#define YEARS 5

const float rain[YEARS][MONTHS] = {
	{4.3, 4.3, 4.3, 3.0, 2.0, 1.2, 0.2, 0.2, 0.4, 2.4, 3.5, 6.6},
	{8.5, 8.2, 1.2, 1.6, 2.4, 0.0, 5.2, 0.9, 0.3, 0.9, 1.4, 7.3},
	{9.1, 8.5, 6.7, 4.3, 2.1, 0.8, 0.2, 0.2, 1.1, 2.3, 6.1, 8.4},
	{7.2, 9.9, 8.4, 3.3, 1.2, 0.8, 0.4, 0.0, 0.6, 1.7, 4.3, 6.2},
	{7.6, 5.6, 3.8, 2.8, 3.8, 0.2, 0.0, 0.0, 0.0, 1.3, 2.6, 5.2}
};

void show_year(void);
void show_month(void);

int main(void)
{
	show_year();
	show_month();

	return 0;
}

void show_year(void)
{
	int month, year;
	float total, subtot;

	printf(" YEAR       RAINFALL(inches)\n");
	for(year=0, total=0; year<YEARS; year++)
	{
		for(month=0, subtot=0; month<MONTHS; month++)
		{
			subtot += *(*(rain+year) + month);
		}
		printf("%5d %15.1f\n", 2000+year, subtot);
		total += subtot;
	}
	printf("\nThe yearly average is %.1f inches.\n\n", total/YEARS);
}

void show_month(void)
{
	int month, year;
	float subtot;
	printf("MONTHLY AVERAGE: \n\n");
	printf(" Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec\n");

	for(month=0; month<MONTHS; month++)
	{
		for(year=0, subtot=0; year<YEARS; year++)
		{
			subtot += *(*(rain+year)+month);
		}
		printf("%4.1f", subtot/YEARS);
	}
	putchar('\n');
}

```

### 练习10.12：使用数组解决实际问题

```c
#include <stdio.h>

void eat_line(void);
void request_dataset(double set[][5]);
double request_number(void);
void show_average(double array[], int index);
double calc_total_average(double set[][5]);
double find_max(double set[][5]);
void show_result(double set[][5]);

int main(void)
{
	double set[3][5];
	request_dataset(set);
	
	show_result(set);

	return 0;
}

void eat_line(void)
{
	char ch;
	while((ch=getchar())!='\n')
	{
		continue;
	}
}

void request_dataset(double set[][5])
{
	printf("Please enter fifteen numbers to fill three number sets.\n");
	set--;
	for(int i=0; i<15; i++)
	{
		int j = i % 5;
		if(j==0){
			set++;
		}
		(*set)[j] = request_number();
	}
}

double request_number(void)
{
	double num;
	
	while(scanf("%lg", &num)!=1)
	{
		eat_line();
		printf("Invalid input detected. Please try again: \n");
	}

	return num;
}

void show_average(double array[], int index)
{
	double total = 0;
	for(int i=0; i<5; i++){
		total += array[i];
	}
	printf("The average number of Array %d is %lg.\n", index, total/5);
}

double calc_total_average(double set[][5])
{
	double total = 0;
	for(int i=0; i<3; i++){
		for(int j=0; j<5; j++){
			total += set[i][j];
		}
	}

	return total / 15;
}

double find_max(double set[][5])
{
	double max = set[0][0];
	for(int i=0; i<3; i++){
		for(int j=0; j<5; j++){
			if(max<set[i][j]){
				max = set[i][j];
			}
		}
	}

	return max;
}

void show_result(double set[][5])
{
	show_average(set[0], 1);
	show_average(set[1], 1);
	show_average(set[2], 1);

	printf("The total average of the number set is %lg.\n", calc_total_average(set));

	printf("The max number of the number set is %lg.\n", find_max(set));
}

```

### 练习10.13：使用变长数组重构练习10.12

```c
#include <stdio.h>

void eat_line(void);
void request_dataset(int rows, double set[rows][5]);
double request_number(void);
void show_average(double array[], int index);
double calc_total_average(int rows, double set[rows][5]);
double find_max(int rows, double set[rows][5]);
void show_result(int rows, double set[rows][5]);

int main(void)
{
	double set[3][5];
	request_dataset(3, set);
	
	show_result(3, set);

	return 0;
}

void eat_line(void)
{
	char ch;
	while((ch=getchar())!='\n')
	{
		continue;
	}
}

void request_dataset(int rows, double set[rows][5])
{
	printf("Please enter fifteen numbers to fill three number sets.\n");
	set--;
	for(int i=0; i<rows*5; i++)
	{
		int j = i % 5;
		if(j==0){
			set++;
		}
		(*set)[j] = request_number();
	}
}

double request_number(void)
{
	double num;
	
	while(scanf("%lg", &num)!=1)
	{
		eat_line();
		printf("Invalid input detected. Please try again: \n");
	}

	return num;
}

void show_average(double array[], int index)
{
	double total = 0;
	for(int i=0; i<5; i++){
		total += array[i];
	}
	printf("The average number of Array %d is %lg.\n", index, total/5);
}

double calc_total_average(int rows, double set[rows][5])
{
	double total = 0;
	for(int i=0; i<rows; i++){
		for(int j=0; j<5; j++){
			total += set[i][j];
		}
	}

	return total / 15;
}

double find_max(int rows, double set[rows][5])
{
	double max = set[0][0];
	for(int i=0; i<rows; i++){
		for(int j=0; j<5; j++){
			if(max<set[i][j]){
				max = set[i][j];
			}
		}
	}

	return max;
}

void show_result(int rows, double set[rows][5])
{
	for(int i=0; i<rows; i++){
		show_average(set[i], i+1);
	}

	printf("The total average of the number set is %lg.\n", calc_total_average(3, set));

	printf("The max number of the number set is %lg.\n", find_max(3, set));
}

```
