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
- `type_name()`
- `floatval()`

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

