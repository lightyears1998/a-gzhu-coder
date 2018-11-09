# JavaScript笔记

## 链接

- [ECMAScript文档](https://www.ecma-international.org/publications/files/ECMA-ST/Ecma-262.pdf)
- [Mozilla JavaSript参考](https://developer.mozilla.org/en-US/docs/Web/JavaScript)

入门

- [Wangdoc.com](https://wangdoc.com/javascript/)

## Chapter 0 概述

ECMAScript是JavaSrcipt的语言标准，JavaSript是ECMAScript的一种实现。

JavaScript算是一种嵌入式语言，本身没有IO函数，需要宿主来提供。最典型的宿主是浏览器和服务器端的Node项目。

JavaScript不是纯粹的面向对象语言，也支持其他编程范式，例如函数式编程。

JavaScript的核心语法部分十分精简，只包含基本的语法构造和标准库，更多地依赖于宿主环境提供的API；以浏览器环境为例子，提供的API主要有三大类

1. 浏览器控制类
2. DOM类
3. Web类

> 摘自Wangdoc.com <https://wangdoc.com/javascript/basic/index.html>

### 重要的编程风格

1. Javascript中区块起首的大括号紧跟在关键字后面，避免[难以察觉的错误](https://wangdoc.com/javascript/features/style.html#区块)。
2. 尽量使用严格相等运算符`===`，以避免[自动类型转换带来的不确定性](https://wangdoc.com/javascript/features/style.html#相等和严格相等)。
3. `switch... case`结构可以用面向对象结构替代。
4. 严格模式，在产生任何实际运行效果的语句前添加`'use strict'`字符串

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

#### `<!-- -->`形式的注释

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

JavaScript中定义了7种数据类型

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

### null与undefined

if语句中两者都会自动被转换成false，使用`==`会报告两者相等

Dart语言中只有null，没有undefined。

null表示空对象，转换成数值时表示0；undefined表示未定义，转换成数值时表示NaN

调用函数时，未提供参数时，该参数返回undefined；函数无返回值时返回undefined

### 布尔值

以下值被自动转换为false

1. undefined和null
2. false
3. 0
4. NaN
5. 空字符串 ''

使用`Boolean()`进行强制类型转换

### 数值

在Javascript内部，所有数值（包括整数）使用64位浮点数储存

由于64位浮点数的特性，绝对值小于2的53次方的整数都能精确地表示，即对15位的进制数都能精确处理

数值范围是[0, Infinity)；`Number`对象提供`MaxValue`和`MinValue`方法。

表示数值的字面值

- 十进制：没有前导0的数值。
- 八进制：有前缀0o或0O的数值，或者有前导0、且只用到0-7的八个阿拉伯数字的数值。
- 十六进制：有前缀0x或0X的数值。
- 二进制：有前缀0b或0B的数值。

#### 正零与负零

`toString()`方法都返回`0`

唯一有区别的场合是作为分母时分别得到`+Infinity`和`-Infinity`

#### NaN

NaN参与的运算结果都是NaN

NaN是唯一的不等于自身的值

#### 与数值相关的全局方法

1. `parseInt()` 用于将字符串转换成整数
  自动去除空格，返回NaN或转换后的数值
  注意到 对于那些会自动转为科学计数法的数字，parseInt会将科学计数法的表示方法视为字符串，因此导致一些奇怪的结果。

  ```js
  parseInt(1000000000000000000000.5) // 1
  // 等同于
  parseInt('1e+21') // 1

  parseInt(0.0000008) // 8
  // 等同于
  parseInt('8e-7') // 8
  ```

  还可以附带第二个参数进行进制转换
2. `parseFloat()`
3. `isNaN()`, `isFinite()`

使用`Number()`进行强制类型转换

### 字符串

使用单引号或双引号均可，一般约定使用单引号，以与html相区分。

反斜线转义

1. `\HHH` 八进制转义
2. `\xHH` 十六进制转义
3. `\uXXXX` Unicode转义

可以使用方括号语法访问字符串中的单个字符，但*无法改变*单个字符。

字符串具有`length`属性

使用`String()`进行强制类型转换

#### Base64

`btoa()`, `atob()`

### 对象

无序的键值对的集合

```js
{
  foo: 'hello',
  bar: 'world'
};
```

键名又称属性。最后一个属性后面可以添加逗号

所有的键名都是字符串，因此加引号与否无影响。（数值键名会被自动转换为字符串，如果键名不满足作为标识符的条件，则必须加上引号）

```js
var obj = {
  1p : 'Page 1',    // 报错
  h + w: 'H and W'  // 报错
};

var obj = {
  '1p': 'Page 1',
  'h + w': 'H and W'
}
```

键值可以是任何数据类型，包括函数。

## Chapter 4 异常处理机制

// TODO
// <https://wangdoc.com/javascript/features/error.html>

## Chapter 5 面向对象编程

对象是一种容器，封装了属性和方法。

JavaScript的对象基于原型链

### 构造函数

```js
var CheseBoard = function () {
  this.length = 8;
};
```

1. 构造函数内部使用了`this`关键字，表示所要生成的对象的实例
2. 调用构造函数必须使用`new`命令

### `new`命令

```js
var v = new ChessBoard(arg);
```

如果不使用`new`命令，构造函数将成为普通函数，不能生成实例对象。通常this引用全局对象，造成意想不到的结果。

#### 确保使用`new`命令

1. `'use strict'`
    严格模式中this不能引用全局对象，默认为`undefined`

    ```js
    function Foobar(foo, bar) {
      'use strict'
      this.foo = foo;
      this.bar = bar;
    }

    Foobar()  // TypeError: Cannot set property 'foo' of undefined
    ```

2. 构造函数内部判断是否使用`new`命令

    ```js
    function Foobar(foo, bar) {
      if (!this instanceof Foobar) {
        return new Foobar(foo, bar);
      }

      this.foo = foo;
      this.bar = bar;
    }
    ```

#### `new`命令的原理

1. 创建一个空对象，作为将要返回的实例
2. 将这个空对象的原型，指向构造函数的`prototype`属性
3. 将这个空对象赋给函数内部的this关键字
4. 执行构造函数内部的代码

若构造函数内部有return语句，且return后面指定了一个对象，则返回return语句指定的对象；否则返回this对象。

若对普通函数使用new命令，则返回一个空对象。

#### `new.target`

函数内部可以使用`new.target`属性。如果当前函数是`new`命令调用，`new.target`指向当前函数，否则为`undefined`。

### Object.create()

以现有对象为模板创建对象

### `this`

`this`总是返回一个对象。

`this`是属性或方法“当前”所在的对象（当前所在的运行环境），即只要函数被赋值给另一个对象（或其他运行环境的改变），`this`的指向就会改变。

必要时，可以使用中间变量固定`this`；必要时，应该绑定`this`。

应该避免，

1. 使用多层this
2. 在数组方法中使用this
3. 在回调函数中使用this

### `this`的绑定

- `Function.prototype.call(obj, arg1, arg2, ...)` 将函数内部的this指定到obj上，然后所指定的作用域中调用该函数。
- `Function.prototype.apply(obj, [arg1, arg2, ...])` 同call，但接受数组形式的参数
- `Function.prototype.bind(obj)` 将函数内部的`this`绑定到obj上，并返回一个新函数

#### 使用环境

1. 全局环境下`this`指代顶层对象`window`
2. 构造函数中`this`指代实例对象
3. 如果对象的方法中包含`this`，则`this`指向方法运行时所在的对象

注意JavaScript的方法是可以单独取出来使用的，如`foo.bar();`，此时`this`将指向全局环境。

如果`this`所在的对象不在第一层，则this只是指向当前一层的对象，不会继承上层对象。

### 继承

实例对象的`prototype`属性指向原型对象。

只要修改原型对象，变更就会体现在所有实例对象上。

原型对象的作用即定义所有实例对象所共享的属性和方法。

#### 继承链

所有对象的原型可以追溯到`Ojbect.prototype`，`Ojbect.prototype`的原型是`null`，原型链到此为止。

覆盖（Overwhelming），实例对象定义了与原型对象相同的方法。

#### `constructor`属性

可获知实例对象是由哪一个构造函数产生的。

#### `instanceof`

判断对象是否为某个构造函数的实例。

对于`null`和`undefined`，`instanceof`总是返回false。

### Object方法

#### `in` 运算符

检查对象是否具有某个属性

## Chapter 6 浏览器模型

### URLSearchParams

构造、解析和处理URL的查询字符串。
