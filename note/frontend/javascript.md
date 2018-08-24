# JavaScript笔记

## Chapter 0 概述

ECMAScript是JavaSrcipt的语言标准，JavaSript是ECMAScript的一种实现。

JavaScript算是一种嵌入式语言，本身没有IO函数，需要宿主来提供。最典型的宿主是浏览器和服务器端的Node项目。

JavaScript不是纯粹的面向对象语言，也支持其他编程范式，例如函数式编程。

JavaScript的核心语法部分十分精简，只包含基本的语法构造和标准库，更多地依赖于宿主环境提供的API；以浏览器环境为例子，提供的API主要有三大类

1. 浏览器控制类
2. DOM类
3. Web类

> 摘自Wangdoc.com <https://wangdoc.com/javascript/basic/index.html>

## Chpater 1 开发环境

### 浏览器Console

开发人员工具中的Console

## Chapter 2 基础语法

语句以分号结尾；表达式不需要以分号结尾。没有内容的语句是空语句。

### 标识符

1. 第一个字符可以是任意Unicode字母，以及美元符号`$`和下划线`_`
2. 第二个字符以及其后字符还可以是数字

### 注释

- 单行注释 `//`
- 多行注释 `/* */`

`<!-- -->`形式的注释

```js
x = 1; <!-- x = 2;
--> x = 3;
```

注意只有`x = 1;` 会被执行，其他代码（包括`x = 3;`）都被注释掉了

注意只有在行首的`-->`才会被当成单行注释，否则会被认为是正常的运算

### 变量

对值的具名引用。没有赋值的变量的值是`undefined`。

使用`var`来声明变量；不使用`var`的声明可被执行。

```js
var a = 1 + 3;
```

- 变量具有动态类型
- **变量提升** 所有的变量声明的语句，都会被提升到代码的头部，并先执行

### 区块 Block

```js
{
    var a = 1;
}
a;  // 1
```

对于var声明的变量来说，区块不构成单独的作用域（Scope）

### 控制语句

`if`, `switch`, `while`, `do... while`, `for`结构与C++保持一致

可以像在Java语言中那样结合标签使用`break`和`continue`

注意`switch`表达式的匹配采用严格相等运算符`===`

## Chapter 3 数据类型

JavaScript中定义了7中数据类型

- number 数值
- string 字符串
- boolean 布尔值
- `undefined` 未定义
- `null` 空值
- object 对象，包括狭义的对象object，数组array以及函数function
- symbol 符号，ES6新增类型

### `typeof`

可以使用`typeof`运算符来判断一个变量的类型，返回“number”等字符串

因此可以用`typeof`来检查一个没有声明的变量而不报错

由于历史原因，`typeof null`返回“object”

## 链接

- [ECMAScript文档](https://www.ecma-international.org/publications/files/ECMA-ST/Ecma-262.pdf)
- [Mozilla JavaSript参考](https://developer.mozilla.org/en-US/docs/Web/JavaScript)

入门

- [Wangdoc.com](https://wangdoc.com/javascript/)
