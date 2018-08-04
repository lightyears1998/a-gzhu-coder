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
- NULL合并运算符 `$name = $_GET['name'] ?? false` 不存在时返回`false`，否则返回`$_GET['name']`
- 太空船操作符 `$a <=> $b` 当`$a`分别小于、等于或大于`$b`时，分别返回-1, 0或1 

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

### 数组

数组：有序映射

- 定义数组 `array{"a"=>"apple", "b"=>"banana"}; ` 短定义语法 `['a'=>1, 'b'=>2]`
- 访问数组元素 `array[key]`, `array{key}`

### 对象

`new`

### 资源

`$handle = fopen($filename, $filemode);`

### 无类型

未被赋值或被赋值为NULL，或被`unset()`的变量

- `is_null()`
- `unset()`