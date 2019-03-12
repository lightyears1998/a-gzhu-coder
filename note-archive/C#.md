# C#笔记

## Chpater 0 概述

C#由微软推出，Java语言的竞争者；是ECMA和ISO的标准语言。

## Chapter 1 基本概念

### Hello, World程序

```csharp
using System;

namespace HelloText
{
    class Program
    {
        public static void Main(String[] args)
        {
            Console.WriteLine("Hello, world!");
        }
    }
}
```

C#区分大小写，因此`Main`必须保证首字母的大写

可以借助[命令行工具][命令行工具]进行编译

其他常见文件包括

- 引用文件夹 列出程序使用的程序集
- Properties文件夹
- App.config 应用程序配置文件

[命令行工具]: https://docs.microsoft.com/en-us/dotnet/csharp/language-reference/compiler-options/command-line-building-with-csc-exe

### 命名空间与程序集

**命名空间** `using 命名空间;`

**程序集** 类编译到程序集中，dll文件和exe文件都是程序集

程序集与命名空间并非一对一的关系

### 语句语法和语义

- 标识符等常见概念

### 命名约定

#### 变量命名

变量名大小写敏感。

- 不宜以下划线开头
- 使用驼峰风格camelCase
- 不使用匈牙利记号法则

#### 类型同义词

在C#中，

- `obejct`关键字等价于`System.Object`
- `string`等价于`String`

### 输入输出工具

- `Console.WriteLine()`
- `Int.Parse()`

### Visual Studio技巧

- 快速重构“提取方法”
- 添加`// TODO:`注释

## Chapter 2 变量与基本数据类型

int, float, double, decimal, string, char, bool

- **明确赋值原则** C#中不允许使用没有赋值的变量
- **隐式类型变量** 相当于C++中的`auto`，使用`var`关键字。由编译器负责类型推断

### 字符串插值

```cs
$"Hello, {userName.Text}"
```

### Infinity和NaN

针对于浮点数

浮点数除以0是`Infinity`

NaN参与的任何运算结果都是NaN

### 值类型和引用类型

赋值是按值传递，复制引用。

使用对象的Clone方法复制对象，必要时重载以定义“深拷贝”。

### null值和可空类型

- `null`即空引用，不能把`null`用于值类型
- 使用`?`操作符定义可空类型

```cs
int ? number = null;
if (number == null)
{
    Console.WriteLine("It is empty.");
}
```

## Chapter 3 方法

### 表达式主体方法

一种语法糖

```cs
int addValue(int a, int b) => a + b;
```

### 可选参数

如同C++

### 具名参数

与Python语法稍有不同

```cs
optMethod(first: 99, second: 100, third: "101");
```

### ref参数

按引用传递，注意调用方法时也要附加`ref`关键字

```cs
static void doIncrement(ref int it) => it++;

static void Main()
{
    int arg = 12;
    doIncrement(ref arg);  // 调用方法时需要附加ref关键字
}
```

即使是ref参数也不接受未初始化的变量作为实参

### out参数

需要由参数来初始化变量时，使用out参数来初始化未初始化的变量

使用out参数后，必须在方法内部对传递的变量赋值

```cs
static void doInitialize(out int number) => number = 12;

static void Main(string[] args)
{
    int a;
    doInitialize(out a);
}
```

## Chapter 4 分支和流程控制

bool类型的值是`true`和`false`

- `&&`和`||`都是短路运算符
- **C#只允许使用显式的布尔表达式** 不能在if后面的括号中使用数值表达式

```cs
if (boolExpression)
    statement;

switch (controllingExpression)
{
    case constantExpression:
    default:
}

while (boolExpression)
    statement;

for (init; controllingExpression; step)
    statement;

do {
    statement
} while (controllingExpression);
```

## Chapter 5 异常处理

形如Java

```cs
try
{
    something;
}
catch (Exception ex)
{
    dosomething;
}
finally
{
    finalJob;
}
```

### 异常过滤器

```cs
catch (Exception ex) when (ex.GetType() != typeof(System.OutOfMemoryException))
{
    // 捕捉OutOfMemory之外的异常
}
```

### `checked`和`unchecked`整数运算检查

也可以通过设置项目属性“高级生成设置”来手动启用溢出检查，不管项目如何编译，`checked`和`unchecked`总是覆盖项目的自动编译选项

```cs
checked{
    int number = int.MaxValue;
    checked
    {
        int willThrow = number++;
        Console.WriteLine("不会执行到这里");
    }
}
```

`checked`和`unchecked`只适用于浮点数

### 抛出异常

```cs
throw new ArgumentOutOfRangeException("不存在的月份");
```

## Chapter 6 类

类的方法默认权限为`private`

构造器、重载构造器形如Java

### Partial Class 分部类

```cs
partial class Circle
{
    // 主要功能
}

partial class Circle
{
    // 对功能的扩充
}
```

分部类不是用来将定义与实现分离的，另外C#中规定分部方法必须具有void的返回类型。

### Static Class 静态类

静态类中只能包含静态方法

### 静态using语句

将类引入作用域，使得在访问静态成员时隐藏类名，功能上Java但语法不同

```cs
using static System.Math;
using static System.Console;

var root = Sqrt(99.9);
WriteLine("");
```

### 匿名类

匿名类，没有名字的类

```cs
var anonymousObject = new { Name="John", Age = 12 };
```

编译器自动推断匿名类字段的类型，并根据字段的名称、类型、数量和声明的顺序判断两个匿名类是不是同一个类型的匿名类。

匿名类只能包含公共字段，并且不能定义方法，字段必须全部初始化，并且不能是静态的。

### is操作符

使用`is`操作符验证对象的类型

```cs
WrappedInt wi = new WrappedInt();
Object o = wi;

if (o is WrappedInt)
{
    WrappedInt tmp = (WrappedInt)o;  // 确定o是对WrappedInt的引用之后转型就是安全的
}
```

### as操作符

as操作符转换对象的类型，失败时返回`null`

```cs
WrappedInt wi = new WrappedInt();
Object o = wi;

WrappedInt tmp = o as WrappedInt;
if (tmp != null)
{
    // 只有转型成功才会执行
}
```

### System.Math

- `Sqrt()` 平方根的计算

## Chapter 7 枚举和结构

### 枚举

与C++不同，C#枚举不需要枚举类的语法即可拥有“类的名称空间”

```cs
enum Season {Spring, Summer, Fall, Winter};

Season local = Season.Spring;
```

## Chapter 14 占位符

### 使用unsafe标记不安全的代码

使用`unsafe`时，需要在项目属性中设置允许不安全的代码

```cs
public static void Main(string[] args)
{
    int x = 99, y = 12;
    unsafe
    {
        Swap(&x, &y);
    }
}

public static unsafe void Swap(int *a, int *b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}
```