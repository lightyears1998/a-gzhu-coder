# JavaScript笔记

## 链接

- [ECMAScript文档](https://www.ecma-international.org/publications/files/ECMA-ST/Ecma-262.pdf)
- [Mozilla JavaSript参考](https://developer.mozilla.org/en-US/docs/Web/JavaScript)
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

`switch case`的面向对象风格替代

```js
function doActions(action) {
    var actions = {
        'one': function () {
            return 1;
        },
        'two': function () {
            return 2;
        },
        'run': function () {
            return 'run';
        }
    };

    if (typeof actions[action] !== 'function') {
        throw new Error('Invalid action.');
    }

    return actions[action]();
}

```

## Chpater 1 开发环境

### 控制台与console对象

向控制台输出信息，自动在连续两个参数产生的输出间添加空格，并在每次输出的结尾添加换行符

1. `console.log()`, `console.debug()`, `console.info()`
2. `console.warn()`
3. `console.error()`

支持格式字符串，如`%s`, `%d`或`%i`, `%f`, 对象的链接`%o`。在浏览器上还支持CSS格式字符串`%c`（用于对输出内容进行渲染）。

可以按自己的需要覆盖console的方法，如为console的输出添加时间字符串。

```js
['log', 'warn', 'error'].forEach(function (method) {
    console[method] = console[method].bind(
        console,
        new Date().toISOString()
    );
});
```

`console.table`可以将符合类型的数据转换为表格显示

```js
console.table(
    {
        Alice: { name: 'Alice Kane', score: 32 },
        Bob: {name: 'Bob Kingdom', score: 44 }
    } // 或数组类型
);
```

`console.dir()`用于对对象进行审察，格式比直接使用console.log()美观。

`console.count('tag')`用于计数，输出它被调用了多少次。

`console.time('tag')`和`console.timeEnd('tag')`用于计算操作花费的时间。

`console.group()`, `console.groupEnd()`和`console.groupCollapsed()`用于对大量信息进行分组。

`console.trace()`用于显示调用栈。

`console.clear()`用于清空输出。

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

#### 类似数组的对象

具有length属性的对象是类似数组的对象，如函数的`arguments`。

可以使用`Array.prototype.slice.call()`方法将类似数组的对象转换为数组。

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

#### `Number()`

对于原始类型的值规则如下：

1. 数值转换后为原来的值。
2. 可以解析为数值的字符串，转换为相应的数值；否则返回`NaN`（注意与`parseInt()`函数的区别，`324abc`返回`NaN`）；空字符串`''`返回0。
3. `undefined`转换为`NaN`，`null`转换为0。
4. 对对象通常返回`NaN`，但包含单个值的数组除外。

注意，`Number()`与`parseInt()`都自动过滤前导空格后后置空格。

`Number()`方法的转换机制是先尝试调用`valueOf()`，然后尝试`toString()`；尝试均失败后报错。

#### `String()`

将任意类型的值转换为字符串。

1. 数值转换为相应字符串。
2. 字符串转换后仍为原来的值。
3. `true`转换为`'true'`，`false`转换为`'false'`。
4. 对象返回代表对象的字符串，如`[object Object]`；

`String()`方法的转换机制与`Number()`相似，只是先尝试调用`toString()`，然后尝试`valueOf()`。尝试失败后则报错。

#### `Boolean`

除以下内容外转换结果均为`true`。

1. `undefined`
2. `null`
3. `0`, `-0`, `+0`
4. `NaN`
5. `''`

因此所有对象的转换结果都为`true`，包括`Boolean(new Boolean(false))`对象。

### 自动转换

预期为何种类型，就自动转换为何种类型。

含有字符串的二元加法运算，算子均转换为字符串。其他运算符将算子转换为数值，存在将两侧的算子都转换为数值的情况。

注意一元运算符也会将算子转为数值

```js
+true;   // 1
+'abc';  // NaN

```

## Chapter 4 异常处理机制

`Error`实例对象具有错误消息`message`，通常还会具有错误名称`name`和调用栈`stack`信息。

原生JavaScript存在6个`Error`类的派生对象。

1. `SyntaxError`
2. `ReferenceError`
3. `RangeError`
4. `TypeError`
5. `URIError`
6. 不再使用的`EvalError`

可以自定义错误

```js
new Error('错误信息');

function UserError(message) {
    this.message = message || '默认信息';
    this.name = 'UserError';
}

UserError.prototype = new Error();
UserError.constructor.prototype = UserError;

new UserError('自定义错误信息');

```

使用`throw`抛出错误，使用`try ... catch()`捕获错误。

```js
try {
    // ...
}
catch (e) {
    if (e instanceof EvalError) {
        // ...
    }
    else if (e instanceof TypeError) {
        // ...
    }

    // 如果catch块中存在return或throw，将延迟到finally块后执行
}
finally {
    // 不管是否出错都在最后运行的语句
}
```

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

## Chapter 7 标准库

### Object

Object所有其他对象继承自`Object`对象，所有对象都是`Object`的实例。

#### `Object()`

`Object()`将任意值转换为对象，常用于保证某一个值一定是对象。

```js
var obj = Object();
// 等同于
var obj = Object(null);
var obj = Object(undefined);
obj instanceof Object;

// 如果参数是原始类型，则将其转换为对应包装器的类型
var obj = Object('string');
obj instanceof Object;
obj instanceof String;

// 如果方法的参数为对象，则不进行转换
// 由此可写一个判断参数是否为对象的函数
function isObject(value) {
    return value === Object(value);
}

isObject([]);    // true
isObject(true);  // false

```

`Object()`可以作为构造函数使用

```js
var obj = new Object();
// 等价于
var obj = {};

// 如果构造函数的参数是一个对象，则直接返回该对象
var o1 = { a: 1 };
var o2 = new Object(o1);
o1 === o2;  // true

var obj = new Object(123);
obj instanceof Number;  // true

```

#### Object的静态方法

指部署在Object对象自身的方法。

1. 遍历对象自身的属性（而不是继承的属性），可枚举属性`Object.keys()`，还包括不可枚举属性的`Object.getOwnPropertyNames()`
2. 对象属性模型相关方法
  1. `Object.getOwnPropertyDescriptor()` 获取某个属性的描述对象
  2. `Object.defineProperty()` 通过描述对象定义属性
  3. `Object.defineProperties()` 通过描述对象定义多个属性
3. 控制对象状态的方法
  1. `Object.preventExtensions()` 防止对象被拓展
  2. `Object.isExtensible()` 判断对象是否可拓展
  3. `Object.seal()` 禁止对象配置
  4. `Object.isSealed()` 判断对象是否可配置
  5. `Object.freeze()` 冻结对象
  6. `Object.isFrozen()` 判断对象是否被冻结
4. 原型链相关方法
  1. `Object.create()` 可以指定原型对象和属性，返回新的对象
  2. `Object.getPrototypeOf()` 获取对象的prototype对象

#### Object的实例方法

部署在`Object.prototype`对象的方法。

1. `Object.prototype.valueOf()`返回当前对象对应的值。
2. `Object.prototype.toString()`, `Object.prototype.toLocaleString()`返回当前对象对应的字符串形式。
  通过Object.prototype.toString()可以判断一个对象的类型
3. `Object.prototype.hasOwnProperty()`判断某个属性是否为当前对象自身的属性，还是继承自原型对象的属性。
4. `Object.prototype.isPrototypeOf()`判断当前对象是否为另一个对象的原型对象
5. `Object.prototype.propertyIsEnumerable()`某个属性是否可枚举

### 属性描述对象 Atrributes Object

JavaScript内部用于描述属性的对象，用于控制对象属性的行为等。

属性描述对象的例子

```js
{
  value: 123,
  writable: false,      // 属性是否可改变
  enumerable: true,     // 若不可枚举则在一些操作中会被跳过，如 (for ... in)和Object.keys()
  configurable: false,  // 是否可删除该属性，是否可改变描述属性对象的值
  get: undefined,       // getter
  set: undefined
}
```

```js
var obj = { p: 'a' };

Object.getOwnPropertyDescriptor(obj, 'p');
```

#### `Object.defineProperty(object, propertyName, attributesObject)`

为object定义属性，并返回对该object的引用。

```js
var o = Object.defineProperty({}, 'p', {
    value: 123,
    writable: true,
    enumerable: true,
    configurable: true
});

```

### Array对象

`Array`既是原生对象，又是构造函数。

#### 构造函数

不同参数时行为不同。

1. 无参数返回空数组。
2. 单一数值参数返回指定长度的空数组；负值参数报错。
3. 单一非数值参数，将该参数作为返回新数组的成员。
4. 多参数，将参数作为返回数组的成员。

#### `isArray()`

用于判定指定参数是否为数组，弥补`typeof`的不足。

```js
var arr = [1, 2, 3];

typeof arr;  // object
Array.isArray();
```

#### 实例方法

1. `valueOf()`, `toString()` `valueOf()`返回数组本身，`toString()`返回数组的字符串形式。
2. `push()`, `pop()` 添加或弹出数组中的最后一个元素；对空数组使用`pop()`将不报错而返回`undefined`
3. `shift()`, `unshift()` 在数组的第一个位置删除或添加元素。
4. `join(separator = ',')` 将数组的所有元素以指定分隔符连接为字符串。
5. `concat()` 将参数数组的成员合并到原数组中；**原数组不变**，返回合并后的新数组。
6. `reverse()` 颠倒原数组。
7. `slice(start, end)` 提取目标数组的一部分，返回新数组，**原数组不变**。可以接受负数的参数。若没有参数，实际上时创建元素组的拷贝；因此可以借助此方法将类似数组的对象转换为真正的数组。
8. `splice(start, end, addElement1, addElement2, ...)` **改变原素组** 拼接；删除指定位置的元素，并将后续参数加入原数组。
9. `sort()` 将数组元素进行排序。默认按字典序进行排序（注意数值将被转换为字符串再进行排序）。可以传入函数作为参数，按自定义方法进行排序。

    `sort`自定义排序与C++ STL的`sort()`返回值的意义相反，注意区分。

    ```js
    [1, 2, 3].sort(function (cur, nxt) {
        return nxt > cur;  // 若返回的数值大于0，则表示nxt的位置应排在cur前；否则均排在cur后面。
    });  // [3, 2, 1]

    ```
10. `map()` 将数组的每一个成员依次传入参数函数，并将执行的结果合并成一个数组返回。`forEach()`类似于`map()`但是不获取返回值，仅仅用于操纵数据。这两种方法都会跳过数组中的空位，但不会跳过`undefined`和`null`。
    
    ```js
    var out = [];

    [1, 2, 3].forEach(function (elem, index, arr) {
        this.push(2 * elem + index);
    }, out);
    ```

11. `filter()` 对每个元素执行filter中的函数，将函数返回结果为`true`的元素组成新的数组，返回新的数组。

    ```js
    [1, 2, 3].forEach(function (elem, index, arr) {
        return true;
    }, /* 可绑定函数中的this变量 */)

    ```
12. `some()`, `every()` 对数组中的每个元素执行函数，若某些/每个元素的执行结果为`true`，则返回`true`。
13. `reduce()`, `reduceRight()` 对数组中的每个元素执行函数，`reduceRight()`从右往左执行，函数接受四个参数

    ```js
    var arr = [1, 2, 3, 4, 5];

    arr.reduce(function (prev /*积累变量，默认值为arr[0] */, cur /* 当前变量，默认为arr[1] */, index, arr) {
        return prev + cur;  // 返回值作为下一次执行函数时的prev值
    });  // 数组求和
    ```

    `reduce()`函数的第二个参数可对积累变量赋初始值，注意此时`cur`变量为数组中的第一个元素。这里可以避免由于空数组无法取得初始值时出错。
14. `indexOf()`, `lastIndexOf()` 给出给定元素在数组中出现的位置，如果没有出现则返回`-1`。第二个参数表示开始搜索的位置。
    注意此方法不能用于搜索`NaN`的位置，因为`NaN`是唯一自身不等于自身的值。

### 包装对象

数值、字符串和布尔值有对应的包装对象`Number`, `String`和`Boolean`。

自动转换生成的包装对象是只读的；自动转换调用完毕后包装对象会自动销毁。

可以在包装对象的原型上定义新的方法。

### Number对象

具有一些有用的静态属性，如`Number.MAX_SAFE_INTEGER`, `Number.POSITIVE_INFINITY`

有用的实例方法：

1. `toString(不大于16的进制数)`
2. `toFixed(指定小数位数)`
3. `toExponential(小数位数)`
4. `toPrecision(指定位数的有效数字)`

### String对象

静态方法

1. `fromCharCode(unicode1, unicode2, ...)` 返回对应码点组成的字符串。码点大于0xFFFF的字符需要连续使用两次或以上此方法
2. `charCodeAt()` 上述方法的逆方法
3. `trim()` 去除字符串两端的空白字符，返回新字符串，**不改变原字符串**。
4. `toLowerCase()`, `toUpperCase()`
5. `match()`, `search()`, `replace()` 正则方法
6. `split()` 使用指定分隔符分割字符串，返回包含分割字符串的属猪；如果未指定分隔符，则返回数组的唯一成员为原字符串；如果指定分隔符为空字符串，则返回数组成员为原字符串的每一个字符。

具有类似数组的方法。

注意到`substring()`或`substr()`与`slice()`不同，会自动将参数中的负数转换为0，违反直觉。因此建议使用`slice()`

### Math对象

不是构造函数，所有属性和方法都必须在Math对象上调用。

### Date对象

1. 直接调用 无论有没有参数，`Date()`都返回代表当前时间的字符串
2. 构造函数用法
    1. 可以被`Date.parse()`解析的字符串都可以作为字符串参数
    2. 单一数值为毫秒数
    3. `new Date(year, month, day, hour, minute, second, microsecond0~999)` 参数可以使用0和负数；注意月份从0开始计算，但天数从1开始计算

注意日期的直接运算，相加为字符串的拼接，相减为毫秒数的相差（参考自动类型转换）

静态方法

1. `Date.now()` 当前时间的毫秒数。
2. `Date.parse()` 通常是`YYYY-MM-DDTHH:mm:ss.sssZ`格式，最后的Z表示时区；其他格式也能被解析。解析成功返回毫秒数，解析失败返回`NaN`
3. `Date.UTC()` 将参数当成UTC时间进行解释。其他与Date构造函数相同。

实例方法

1. `toString`, `toISOString`(等价于`toJSON`)
2. `toDateString`, `toTimeString`
3. `getDate()`等
4. `setDate()`等

### JSON对象

对值的类型和格式有严格的规定

1. `JSON.stringnify()`
2. `JSON.parse()`

### RegExp对象

Perl 5体系的正则表达式

```js
var reg1 = /reg/igm                   // 字面值
var reg2 = new RegExp('reg', 'igm');  // 对象形式

```

#### 实例属性

1. 只读
    - 与修饰符相关的`RegExp.prototype.ignoreCase`, `global`, `multiline`。
    - 返回正则表达式的字符串形式 `RegExp.prototype.source`。
2. 可写 下一次搜索时开始的位置，`RegExp.prototype.lastIndex`，只在进行连续搜索时有意义。

#### 实例方法

1. `test` 当前模式是否能匹配参数字符串

## Chapter 7+ 文档对象模型DOM

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
