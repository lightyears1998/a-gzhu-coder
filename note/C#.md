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
