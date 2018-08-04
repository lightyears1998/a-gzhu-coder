## 基础

- `<?php expression; ?>`
- 直接输出表达式的值 `<?= expression ?>`
- `echo expression;`

注释

- 单行注释 `//` `#`
- 多行注释 `/* */` 不要嵌套多行注释

### 变量

- 区分大小写
- 以美元符号开头
- 标识符由字母数字或下划线组成，不能以数字开头

### 可变变量

变量的变量名可以动态地设置和使用

```php
$a = 'hello';
$$a = 'world';
echo $a;        // 输出hello
echo $$a;       // 输出world
echo $hello;    // 输出world
```

### 常量

定义常量

- `define('NAME', 'PHP');` 定义NAME为字符串常量“PHP”
- `const NAME='PHP';` 

辨析

- 常量的标识符前没有美元符号
- 常量不理会变量的作用域，定义之后可以在任何地方访问
- 常量一旦定义就不可以取消定义或重新定义
- 常量的值只能是标量

工具方法

- `definded()` 检查某常量是否存在

内置常量

- `__DIR__` 
- `__FILE__`
- `__LINE__`
- `PHP_VERSION`, `PHP_OS`
- TRUE, FALSE

## 运算

- 赋值 `=` 赋值总是按值传递
- 引用赋值 `$a = &$b`
- 三元运算 `? : `
- NULL合并运算符，简化`isset()` `$name = $_GET['name'] ?? false` 不存在时返回`false`，否则返回`$_GET['name']`
- 太空船操作符（组合比较符） `$a <=> $b` 当`$a`分别小于、等于或大于`$b`时，分别返回-1, 0或1，比较的规则沿用PHP常规比较规则

慎用比较

- `!=` `<>` 数据类型转换后不相等
- `==` 数据类型转换后相等
- `===` 数据类型及值全等
- `!==`

```php
$a = 1;
$b = '1 test';
echo $a == $b;  // 返回TRUE
echo $a === $b;  // 返回FALSE 
```

逻辑运算符

`&&`, `AND`, `||`, `OR`, `!`, `NOT`

`&&`比`AND`优先级高，以此类推。

错误控制运算符 `@` 

```php
@mkdir('dir_name');  // 即使出现错误也会继续执行下去
```


## 数据类型

运行时决定

- 四种标量类型：布尔型（boolean），整型（integer），浮点型（float, double或real），字符串型（string）
- 两种符合类型：数组（array），对象（object）
- 两种特殊类型：资源（resource），无类型（NULL）

工具函数

- `gettype()`
- `(boolean)`, `(bool)`, `(integer)`, `(int)`, `(float)`, `(double)`, `(string)`
- `floatval()`, `intval()`, `floatval()`, `strval()`

变量类型转换

- 自动转换 `(type)$var`
- 强制转换 `settype($var, 'int')`

### 布尔型

值取TRUE, FALSE，赋值时可不区分大小写

echo输出时，对于TRUE的变量输出1，对于FALSE变量输出空字符串。

当值被转换成boolean类型时，被认为时false的值的类型

- FALSE
- 0, 0.0, 空字符串, 字符串“0”
- 不包括任何元素的数组array
- NULL（包括尚未赋值的变量）
- 从空标记生成的SimpleXML对象

任何其他值都被认为时TRUE（包括任何资源）

### 整型

```php
$num = 1234;
$num = 0234;  // 八进制
$num = 0x34;  // 十六进制
```

高精度拓展：BC Math，GMP

### 浮点型

### 字符串

- 单引号字符串 `'string'`
- 双引号字符串 `"string"`

用双引号定义的字符串，其中的变量会被解析，并且转义特殊字符。

heredoc

```php
<<<EOT
多行字符串
EOT
```

heredoc会对其中变量解析并且转义特殊字符

```php
$a = 'test'
$str = <<<EOD
a = $a\n
EOD;
echo $str;  // 输出test并附加换行符
```

nowdoc

```php
<<<'EOT'
多行字符串
EOT
```
nowdoc不解析变量也不转义

```php
$a = 'test'
$str = <<<EOD
a = $a\n
EOD;
echo $str;  // 输出test并附加换行符
```

字符串的连接使用`.`操作符，而不是`+`操作符。

### 常用字符串函数

下标从0开始。

mbstring模块提供字符串函数的`mb_`版本

长度

- `strlen(字符串)` 返回字符串占用的*字节*数
- `mb_strlen(字符串, 'UTF8')`  返回字符串的长度，输出8

检索，找不到返回false，否则返回下标

- 区分大小写 `strpos()`, `strrpos()`
- insensitive 不区分大小写 `stripos()`, `strripos()`

截取

`substr(字符串, 起始位置 [, 截取长度])`

- 负数：从-1开始自字符串最后一个字符开始倒数
- `substr('abcdef', -1)` 返回f
- `substr('abcdef', 1, -2)` 返回bcd，注意不是bcdf

替换

`str_replace(搜索字符串needle, 替换字符串replace, 被寻找字符串haystack [, 计数count])`

- `str_replace(',', '', '1,000,000')` 删除逗号
- `str_replace('red', 'black', '<font style="red">')` 替换红色为黑色

`substr_replace(目标字符串string, 替换字符串replace, 起始位置start [, 替换长度])`

- 替换长度为0：相当于插入
- 负数：倒数

清理空格或其他字符

`trim(目标字符串, 需要删除的字符串)`, `ltrim()`, `rtrim()`

- `trim('abc12a3cd', 'a..z')` 注意是两个点，输出12a3

切分和组合字符串

- `explode(分隔符, 字符串)` 字符串打散为数组 
- `implode(数组)`, `implode(分隔符, 数组)` 数组聚合成字符串

转义与反转义

- `addslashes()`, `addcslashes()`, `stripslashes()`, `stripcslashes()`
- `quotemeta()` 将.\\+*?\[^]($)前加反斜线转义

进制转换

- `bin2hex()`, `hex2bin()`

分割

- `chunk_split()` 指定字串长度打断字符
- `wordwrap()` 含有避免单词被打断的选项
- `str_split()` 分割字符串，不需要指定分割符的`explode()`
- `split()` 支持正则表达式的字符串分割

哈希

- `md5()`, `crc32()`, `sha1()`, `hash()`

处理csv

- `str_getcsv()` 解析csv为一个数组

### 数组

数组：有序映射

- 定义数组 `array{"a"=>"apple", "b"=>"banana"}; ` 短定义语法 `['a'=>1, 'b'=>2]`
- 访问数组元素 `array[key]`, `array{key}`
- 打印数组 `var_dump()`, `print_r()`

php支持多维数组

#### 数字索引数组

自动设置键名

```php
$food = array("饼干", "巧克力", "蛋糕");
$food[] = "瓜子";  // 设置键名为3
```

此外还有关联索引数组

#### 数组指针

数组中有内部指针，指向当前的元素。foreach不会移动数组内部指针。

`current()`, `each()`以数字索引数组和关联索引数组形式返回键名和键值，并移动, `end()`, `next()`, `prev()`

#### 工具函数

- `count(array [, mode])` 计算数组中元素的个数，mode=1时递归统计多维数组的元素
- 数字索引数组排序 `sort(array, [, sortingtype])`, `rsort()` 可设定多种排序类型
- 关联索引数组键值排序 `asort()`, `arsort()` 保持键值对，按值进行排序
- 关联索引数组键名排序 `ksort()`, `krsort()` 保持键值对，按键名排序
- 添加元素 `array_push()` 向末尾追加元素 `array_unshift()` 向开头添加元素，往弹夹里压子弹
- 删除元素 `array_pop()`, `array_shift()`
- 删除重复元素，即使键名不同 `array_unique()`
- 查询数组元素 `in_array()`
- 返回键名/键值数组 `array_keys()`, `array_values()`
- 删除数组中的元素 `unset($array[key])`

### 对象

`new`

### 资源

`$handle = fopen($filename, $filemode);`

### 无类型

未被赋值或被赋值为NULL，或被`unset()`的变量

- `is_null()`
- `unset()`

## 流程控制

```php
if (exp) 
else if (exp)
elseif (exp)
```

```php
switch(exp) {
    case 1:
    case 2: break;
    default:
}
```

```php
while (exp) {
    // body
}

do {
    // body
} while (exp);
```

```php
for (exp1; exp2; exp3) {
    // body
}
```

```php
foreach($数组 as $数组元素) {
    // body
}

foreach($数组 as $键值 => $元素值) {
    // body
}
```

## 函数

```php
function foo($arg1, $arg2, $arg3, ...)
{
    return $val;
}
```

函数具有全局作用域，可以在一个函数内定义而在这个函数外调用。

```php
function foo(&$var){
    // 通过引用传递参数
}
```

```php
function foo($var = 'default') {}  // 默认参数
```

参数类型声明

传入参数的类型错误时，PHP7抛出`Type Error`异常，PHP5报告致命错误。

可声明的参数类型：（对象或接口）`class`, `interface`, （数组）`array`, （回调函数）`callable`, （标量类型）`bool`, `int`, `string`, `float`

```php
function foo(int $var1, bool $var2, string $var3) {}
```

`call_user_func($fun)` 运行回调函数

可变参数列表

```php
function foo(...$vars) {}
```

返回值类型声明

```php
function foo() : int {}
```

可变函数

```php
$functions = ['fun1', 'fun2', 'fun3'];
foreach($functions as $fun)
{
    $fun();
}
```

匿名函数

```php
$myfunction = function() {
    // body
};
```

在函数中可以通过`global`关键字获取全局变量，使用`static`关键字定义静态变量。

## 表单处理

全局变量 `$_GET`, `$_POST`, `$_REQUEST`(GET，POST和COOKIE)

文本框和文本域

```php
if (isset($_GET['name'])) { 
    // ...
}
```

单选按钮radiobutton，值由value属性设定

复选框checkbox，值由value属性设定，name属性应该以“[]”结尾（使得PHP以数组方式解析，避免值覆盖的问题；注意PHP中的标识符不包括“[]”）。

下拉列表，值由option的内容设定

## Cookie

`setcookie(name, value, expire, path, domain, secure);`

- `setcookie("user", "Chloe", time()+7200, '''', 'yourdomain.com', 1);` 启用安全传输
- `setcookie("user", "", time()-3600);` 删除Cookie

## Session

- 创建session `session_start()`
- 终结session `session_destroy()`

## 常用工具函数

- `time()` 返回自Unix纪元到当前时间的秒数

## 源

- 清华大学出版社 2017 《PHP+MySQL网站开发从零开始学》 樊爱宛，黄凯 如果熟悉C语言学习PHP会很方便，很喜欢这本书的风格
