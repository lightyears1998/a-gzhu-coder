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

*最好还是不要用这样奇怪的东西*。

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

NaN是唯一的不等于自身的值，`(NaN == NaN) === false`, `(NaN === NaN) === false`

#### 与数值相关的全局方法

1. `parseInt()` 用于将字符串转换成整数
  自动去除空格，返回NaN或转换后的数值
  注意到 对于那些会自动转为科学计数法的数字，parseInt会将科学计数法的表示方法视为字符串，因此导致**一些奇怪的结果**。

  ```js
  parseInt(1000000000000000000000.5) // 1
  // 等同于
  parseInt('1e+21') // 1

  parseInt(0.0000008) // 8
  // 等同于
  parseInt('8e-7') // 8
  ```

  还可以附带第二个参数进行进制转换，`parseInt('1010', 2);`
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

#### 属性的读取与赋值

点运算符或方括号运算符均可。

方括号运算符接受；数值键名不接受点运算符。

查看所有属性，可以使用`Object.keys()`。

使用`delete`删除属性，成功后返回`true`。`delete`不能删除继承的属性。

判断属性是否存在，使用`in`运算符。

遍历可遍历的属性（包括继承的属性），使用`for ... in`循环。

```js
for (var key in obj) {
  console.log(key);
  console.log(obj[key]);
}
```

#### with

建议不使用`with`语句。

作用是操纵同一对象的属性时提供书写的方便。

#### 对象or表达式？

`{ foo: 123 }`

为了消歧义，如果行首是括号，解释为对象；否则为语句块。

1. 对象 `({ foo: 123 })  // 123`
2. 语句块 `{ foo: 123 }  // {foo: 123}`

### 函数

声明函数由三种方式

1. function命令声明
2. 函数表达式形式的声明
3. 使用Function构造函数

函数表达式形式的声明，若有`var f = function k() {...}`，则名称`k`只在函数内部有效。

函数若重复声明，后一次将覆盖前一次的声明，且由于变量提升和函数声明提升，前一次声明任何时候都是无效的。

#### 函数的属性和方法

- `name`属性 返回函数的名字；若函数为表达式形式，且为匿名函数，则返回变量的名字；若为具名函数，则返回此`function`关键字之后的函数名
- `length`属性 返回函数定义时的参数个数
- `toString()`方法 返回函数的源代码，包括其中的注释

#### 作用域

函数执行时的作用域，是定义时的作用域而不是调用时所在的作用域。函数体内部声明的函数，作用域绑定函数体内部。

#### 参数

Js允许省略参数而不报错，可以为参数传入`undefined`

参数的传递方式如下：

1. 原始数据类型（数值、字符串、布尔值）按值传递 pass by value
2. 对象按址传递 pass by reference

如果出现同名参数，则按名存取时取后一个参数名；访问前一个可以使用`arguments`关键字。

#### arguments对象

arguments对象不是一个数组，但可以通过数值下标访问和具有`length`属性；严格模式下对`arguments`的修改是无效的。

#### 闭包

“定义在函数内部的函数”，可以“记住诞生的环境”。

闭包的两大用处是：

1. 可以读取函数内部声明的变量
2. 可以使闭包诞生的环境持续存在

```js
function createIncrementor(start) {
  return function () {
    return start++;
  };
}

var inc = createIncrementor(5);

inc() // 5
inc() // 6
inc() // 7

```

#### 立即调用的函数表达式 IIFE

推而广之，任何让解释器以表达式来处理函数定义的方法，都能产生同样的效果，比如：

1. `(function () { /* code */ })();`
2. `+function() { /* code */ }();`

#### `eval` 对表达式求值

接受字符串作为参数，并将此字符串作为函数执行。

严格模式中，`eval`中声明的变量，不会影响到全局作用域，但仍可以读写当前作用域内的变量。

当`eval`使用别名调用时，其作用域为全局作用域。

### 数组

按次序排列的一组值，数组是特殊的对象，其键名是依序排列的一组值。

Js数组使用32位整数保存数组长度`length`，最大长度为4294967295。`length`属性是可写的，总是比最大的数字键值多一，修改`length`时，数组会根据值删除已有元素或增加空位。读取空位时返回`undefined`。

可以使用`in`运算符来检查数组的键，如果数组中的某位置是空位，`in`返回`false`。

空位与`undefined`是不一样的，遍历数组时，空位会被跳过而`undefined`则不会。

## Chapter 3+ 运算符

### 加法运算

#### 加法运算符

1. 数值之间的相加是平凡的
2. 数值与布尔值的相加，布尔值先转换为数值（true转换为1）
3. 存在字符串的相加，数值转换为字符串，字符串合并

对于加法以外的运算符，操作数一律转换为数值再进行计算。

#### 对象的相加

1. 先将对象转换为原始类型的值，规则如下：
    1. 调用对象的`valueOf()` 一般对象的`valueOf()`返回自身
    2. 调用对象的`toString()` 默认返回`"[object Object]"`，可重写此方法
2. 相加

### 取余运算

运算结果的**符号**由**第一个**操作数决定。

可用于浮点数。

### 数值运算符

一元运算符`+`, `-`。可以将任何值转换为数值（与`Number()`作用相同）

### 指数运算符

`a ** b`

### 比较运算

#### 非相等运算符：字符串的比较

字符串的比较按Unicode码表进行。

#### 非相等运算符：非字符串的比较

1. 原始类型值转换为数值进行比较
2. 对象先调用`valueOf()`，若返回的结果仍是对象，则调用`toString()`方法

注意下面特殊的比较：

```js
[2] > [1] // true
// 等同于 [2].valueOf().toString() > [1].valueOf().toString()
// 即 '2' > '1'

[2] > [11] // true
// 等同于 [2].valueOf().toString() > [11].valueOf().toString()
// 即 '2' > '11'

{ x: 2 } >= { x: 1 } // true
// 等同于 { x: 2 }.valueOf().toString() >= { x: 1 }.valueOf().toString()
// 即 '[object Object]' >= '[object Object]'
```

#### 严格相等运算符

1. 类型不同则返回`false`
2. 同一类型的原始类型，比较值是否相等
3. 同一类型的复合类型（函数、对象、数组），比较是否指向同一个地址
4. `undefine`和`null`与自身严格相等；`NaN`与自身不相等`!=`，也严格不相等`!===`

#### 相等运算符

1. 类型相同时，与严格相等的判断方式一致
2. 类型不同时进行类型转换
    1. 原始类型的值转换成数值再进行比较
    2. 对象与原始类型的比较，对象先转换为原始类型的值
    3. `null`, `undefined`与其他类型的值比较时，结果均为`false`；相互比较时结果为`true`。

注意违反直觉的比较

```js
0 == ''             // true
0 == '0'            // true

2 == true           // false
2 == false          // false

false == 'false'    // false
false == '0'        // true

false == undefined  // false
false == null       // false
null == undefined   // true

' \t\r\n ' == 0     // true

```

### void运算符

执行一个表达式，且不返回任何值（返回`undefined`）。

### 逗号运算符

对多个表达式求值，并返回后一个表达式的值。

### 运算符结合性

注意到指数运算符是右结合的。

## Chpater 3+ 数据类型的转换

### 强制转换

`Number()`

// todo

### 自动转换

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

## Chapter 6 异步操作

## Chapter 7 文档对象模型DOM

### 节点Node

DOM的最小组成单位，包括7种：

1. Document 文档根节点
2. DocumentType doctype标签
3. Element html标签
4. Attribute 元素属性
5. Text 标签之间或标签包含的文本
6. Comment 注释
7. DocumentFragment 文档片段

以上7种节点继承自Node对象

### 节点树

`document`节点代表整个文档

节点之间的关系：父节点、子节点、同级节点。

### Node接口

### NodeList接口和HTMLCollection接口

### ParentNode接口和ChildNode接口

### 属性的操作

- `getAttribute()`, `getAttributeNames()`
- `setAttribute()`
- `hasAttribute()`, `hasAttributes()`
- `removeAttribute()`

## Chapter 8 事件

## Chapter 9 浏览器模型

## Chapter 10 HTML接口

### Canvas

#### 绘图上下文

```js
ctx = canvas.getContext('2d');
```

#### 绘制图形

绘制矩形

- `fillRect(x, y, width, height);`
- `strokeRect(x, y, width, height);`
- `clearRect(x, y, width, height);`

绘制路径

- `beginPath()`
- `moveTo(x, y)`
- `lineTo(x, y)`
- `closePath()`
- `storke()`, `fill()`

### URLSearchParams

构造、解析和处理URL的查询字符串。
