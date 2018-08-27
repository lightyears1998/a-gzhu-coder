# PHP笔记

## Chpater 0 概述

语法上与C语言相近，用于网页服务器的脚本语言

## Chapter 1 基本概念

PHP通过PHP解释器解释执行，通常是结合Apache或Nginx在Linux或Windows操作系统上使用。

- `<?php expression; ?>`
- 直接输出表达式的值 `<?= expression ?>`
- `echo expression;`

### 注释

- 单行注释 `//` `#`
- 多行注释 `/* */` 不要嵌套多行注释

### 变量

- 区分大小写
- 以美元符号开头
- 标识符由字母数字或下划线组成，不能以数字开头

变量在声明时不需要附加类型信息。

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

有两种方式定义常量

- `define('NAME', 'PHP');` 定义NAME为字符串常量“PHP”
- `const NAME='PHP';`

辨析

- 常量的标识符前没有美元符号
- 常量不理会变量的作用域，定义之后可以在任何地方访问
- 常量一旦定义就不可以取消定义或重新定义
- 常量的值只能是标量

工具方法

- `definded(常量名字符串)` 检查某常量是否存在

内置常量

- `__DIR__`
- `__FILE__`
- `__LINE__`
- `PHP_VERSION`, `PHP_OS`
- `TRUE`, `FALSE`

### 运算符

- 赋值 `=` 赋值总是按值传递
- 引用赋值 `$a = &$b`
- 三元运算 `? :`
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
echo $a === $b;  // 返回FALSE，不产生输出
```

逻辑运算符

`&&`, `AND`, `||`, `OR`, `!`, `NOT`

`&&`比`AND`优先级高，以此类推。

错误控制运算符 `@`

```php
@mkdir('dir_name');  // 即使出现错误也会继续执行下去
```

## Chapter 2 数据类型

运行时决定

- 四种标量类型：布尔型（boolean），整型（integer），浮点型（double，float或real），字符串型（string）
- 两种符合类型：数组（array），对象（object）
- 两种特殊类型：资源（resource），无类型（NULL）

工具函数

- `gettype()` 返回boolean, integer, double, string等字符串
- `(boolean)`, `(bool)`, `(integer)`, `(int)`, `(float)`, `(double)`, `(string)`
- `floatval()`, `intval()`, `floatval()`, `strval()` 注意`int()`等是未定义的方法

变量类型转换

- 自动转换 `(type)$var` 作用是临时的
- 强制转换 `settype($var, 'int')` 作用是持久的

### 布尔型

值取`TRUE`, `FALSE`，赋值时可不区分大小写

echo输出时，对于TRUE的变量输出1，对于FALSE变量输出空字符串。

当值被转换成boolean类型时，被认为是FALSE的值的类型

- `FALSE`
- 0, 0.0, 空字符串, 字符串“0”
- 不包括任何元素的数组array
- NULL（包括尚未赋值的变量）
- 从空标记生成的SimpleXML对象

任何其他值都被认为是TRUE（包括任何资源）

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

```php
$hel = 'hel';
echo "$hel lo"  // 可解析
echo "$hello"   // 不可解析，提示未定义变量
```

heredoc

```php
<<<EOT
多行字符串
EOT

// EOT无引号包围，如同使用双引号包围
// 注意最后的EOT标记必须单独成一行，即没有缩进，其后也没有其他字符
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
$str = <<<'EOD'
a = $a\n
EOD;
echo $str;  // 输出test并附加换行符
```

- Hereodc: Here is a document and parse is needed.
- Nowdoc: The document is now parsed.

字符串的连接使用`.`操作符，而不是`+`操作符。

### 常用字符串函数

下标从0开始。

mbstring模块提供字符串函数的`mb_`版本

#### 长度

- `strlen(字符串)` 返回字符串占用的*字节*数
- `mb_strlen(字符串, 'UTF8')`  返回字符串的长度，输出8

#### 检索

找不到返回false，否则返回下标

- 区分大小写检索 `strpos()`, `strrpos()` 注意不是C风格的`strchr()`或`strstr()`
- insensitive 不区分大小写 `stripos()`, `strripos()`

#### 截取

`substr(字符串string, 起始位置start [, 截取长度length])`

- start若为负数，则从字符串结尾位置向前倒数第Start个字符开始
- string长度小于start则返回`FALSE`
- length若为负数，则string结尾处的length个字符会被省略（与Python中Slicing的右开区间保持一致）；若start不在剩余的字符串中则返回`FALSE`

示例

- `substr('abcdef', -1)` 返回`f`
- `substr('abcdef', 1, -2)` 返回`bcd`，注意不是`bcdf`

#### 替换

`str_replace(搜索字符串needle, 替换字符串replace, 被寻找字符串haystack [, 计数count])` Replace needle with replace in heystack.

- `str_replace(',', '', '1,000,000')` 删除逗号
- `str_replace('red', 'black', '<font style="red">')` 替换红色为黑色

`substr_replace(目标字符串string, 替换字符串replace, 起始位置start [, 替换长度])`

- 替换长度为0：相当于插入
- 负数：倒数

#### 清理空格或其他字符

`trim(目标字符串, 以字符串形式提供需要删除的字符)`, `ltrim()`, `rtrim()`

- `trim('abc12a3cd', 'a..z')` 注意是两个点，输出`12a3`

#### 切分和组合字符串

- `explode(分隔符glue, 字符串str)` 字符串打散为数组，注意参数的顺序（这样设置可能是想强调两个参数都需要吧）
- `implode(数组)`, `implode(分隔符glue, 数组arr)` 数组聚合成字符串，注意参数的顺序使得与`explode()`对应，注意可以不设置分割符

#### 转义与反转义

- `addslashes()`, `addcslashes()`, `stripslashes()`, `stripcslashes()`
- `quotemeta()` 将`.\+*?[^]($)`前加反斜线转义，转义在正则表达式中有特殊意义的字符

`addslashes()`用于加反斜线转义单引号、双引号、反斜线和空字符，`addcslashes()`可以在自定义的字符集之前添加反斜线转义

#### 进制转换

- `bin2hex()`, `hex2bin()` 将**数据串** *（不是字符串）*转换成对应格式

如果需要转化二进制字符，可以

```php
$binary = '11111001';
$hex = dechex(bindec($binary));
echo $hex;
```

#### 分割

- `chunk_split()` 指定字串长度打断字符（插入换行符），在结合`base64_encode($data)`等函数时比较有用
- `wordwrap()` 含有避免单词被打断的选项
- `str_split()` 分割字符串，不需要指定分割符的`explode()`
- `split()` 支持正则表达式的字符串分割

#### 哈希

- `md5()`, `crc32()`, `sha1()`, `hash()`

#### 处理csv

- `str_getcsv()` 解析csv为一个数组

### 数组

数组：有序映射

- 定义数组 `array{"a"=>"apple", "b"=>"banana"};` 短定义语法 `['a'=>1, 'b'=>2]`
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
- 统计数组中的值出现的次数 `array_count_values($array)`

### 对象

`new`

### 资源

`$handle = fopen($filename, $filemode);`

### 无类型

未被赋值或被赋值为NULL，或被`unset()`的变量

- `is_null()`
- `unset()`

## Chapter 3 流程控制

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

## Chapter 4 函数

在函数中可以通过`global`关键字获取全局变量，使用`static`关键字定义静态变量。

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

缺省参数只能位于函数参数表末端

```php
<?php
function sum($c=5, $b=3, $a) {
    echo$a."+ ".$b." + ".$c." = ".($a+$b+$c);
}
sum(1);  // raise ArgumentCountError
?>
```

```php
function foo($var = 'default') {}  // 默认参数
```

### 参数类型声明

传入参数的类型错误时，PHP7抛出`Type Error`异常，PHP5报告致命错误。

可声明的参数类型：（对象或接口）`class`, `interface`, （数组）`array`, （回调函数）`callable`, （标量类型）`bool`, `int`, `string`, `float`

```php
function foo(int $var1, bool $var2, string $var3) {}
```

`call_user_func($fun)` 运行回调函数

### 可变参数列表

```php
function foo(...$vars) {}
```

### 返回值类型声明

```php
function foo() : int {}
```

### 可变函数

```php
$functions = ['fun1', 'fun2', 'fun3'];
foreach($functions as $fun)
{
    $fun();
}
```

### 匿名函数

```php
$myfunction = function() {
    // body
};
```

## Chpater 5 表单处理

全局变量 `$_GET`, `$_POST`, `$_REQUEST`(GET，POST和COOKIE)

文本框和文本域

```php
if (isset($_GET['name'])) {
    // ...
}
```

### HTML接口

键名由name属性决定

- 文本域 键由name属性决定，值由value属性决定
- 单选按钮Radiobutton 值由value属性设定
- 复选框Checkbox，值由value属性设定，name属性应该以“[]”结尾（使得PHP以数组方式解析，避免值覆盖的问题；注意PHP中的标识符不包括“[]”）。
- 下拉列表，值由option的内容设定

## Chpater 6 Cookie

`setcookie(name, value, expire, path, domain, secure);`

- `setcookie("user", "Chloe", time()+7200, '''', 'yourdomain.com', 1);` 启用安全传输
- `setcookie("user", "", time()-3600);` 删除Cookie

## Chpater 7 Session

可以通过设置`session.auto_start`为1来自动启用Session

- 创建session `session_start()`
- 终结session `session_destroy()`

## Chapter 8 面向对象编程

<http://php.net/manual/zh/language.oop5.php>

## Chpater 9 时间与日期

> 格林尼治时间1970年1月1日0时0分0秒

### 设定时区

PHP默认时区为格林尼治时间 GMT+0

投入生产环境前注意检查日期和时间设定

1. php.ini date.timezone Asia/Shanghai
2. `date_default_timezone_set("Asia/Shanghai")`

### 工具函数2

- `time()` 返回自Unix纪元到当前时间的秒数
- `date(format [, timestamp])`
- `mktime(hour, minute, second, month, day, year)`
- `strtotime(string, now当前时间戳)` 将字符串解析为Unix时间戳
- `getdate(timestamp)` 获取包含日期信息的**数组**，获取日期字符串可以使用`date()`
- `checkdate(month, day, year)` 确认日期是否有效
- `strftime(format [, timestamp])` 输出指定格式的日期和时间

示例

- `date('Y-m-d H:i:s')` 2018-08-04 15:32:16
- `date('D', mktime(0, 0, 0, 8, 8, 2018))`
- `strtotime('next Monday')`, `strtotime(+1 week)`, `strtotime('now')`, `strtotime(2008.8.8)`

### 工具对象

- DateTime 常量定义了国际标准中使用的时间格式，如DateTime::COOKIE等；附加许多有用的方法。
- DateTimeImmutable 多数方法返回一个新的DateTimeImmutable对象，本身不会改变。
- DateTimeZone 时区相关运算
- DateInterval 表示一段时间，主要用于DateTime的add/sub/diff方法。
- DatePeriod 表示一组相同时间间隔的时间

获得2018年1月1日至2018年12月31日的每个星期五

```php
$start_date = new DateTime('2018-1-1');
$start_date->modify('next Friday');
$end_date = new DateTime('2018-12-31');
$interval = new DateInterval('P7D');  // 相隔7天

$date_period = new DatePeriod($start_date, $interval, $end_date);
foreach ($date_period as $date)
{
    echo $date->format('Y-m-d')."<br>";
}
```

## Chpater 10 文件和目录

文件资源

- `fopen(filename, mode)` mode: r, w, a, x, c;
- `feof(handle)`
- `fread(handle, length)`
- `fclose(handle)`
- `file_get_contents(handle)` 读入string
- `file_put_contents(handle, string [, mode])` mode: FILE_USE_INCLUDE_PATH, FILE_APPEND, LOCX_EX
- `file(handle [, flags])` 将文件读入数组 flags: FILE_USE_INCLUDE_PATH, FILE_IGNORE_NEW_LINES, FILE_SKIP_EMPTY_LINES

文件名

- `copy(src, dst)` 复制文件
- `unlink(filename)` 删除文件
- `is_file(filename)` 检查文件是否存在及正常（具有x权限）
- `stat(filename)` 返回关于文件的信息数组

目录操作

- `opendir(path)` 打开目录，返回目录资源
- `closedir(handle)`
- `readdir(handle)` 返回目录下的所有文件名
- `mkdir(filename [, mode [, recursive]])`, `rmdir(path)`

文件和目录

- `rename()` 重命名文件或目录
- `file_exists()` 检查文件或目录是否存在

### 国际化

主要由mb_string和intl完成国际化

- `mb_detect_encoding()`, `mb_check_encoding(字符串, 编码)` 检查字符串是否在指定的编码内有效, `mb_convert_encoding(字符串, 编码 [, 原编码（字符串或数组）])`
- `mb_parse_str()` 解析GET字符串并转换为数组
- `mb_strcut()` 按字节数截取字符串

intl

- Collator 比较字符串
- NumberFormatter 中文数字大小写转换
- IntlDateFormatter 中文日期和时间

### 面向对象方法 Directory类

<http://php.net/manual/zh/class.directory.php>

## Chpater 11 压缩文件Zip

- `zip_open()`, `zip_close()`

`zip_read()`, `zip_entry_name()`

```php
$zip = zip_open('filename.zip');
if ($zip) {
    while ($zip_entry = zip_read($zip)) {
        echo '文件名'.zip_entry_name($zip_entry)."\n";
    }
    zip_close($zip);
}
```

ZipArchive类 强大的工具类

## Chpater 12 图形图像处理 GD2

等待补充

## Chapter 13 正则表达式

- int `preg_match(pattern, subject)` 搜索subject，如果搜索到返回1，否则返回0
- string `preg_repalce(pattern, replacement, subject)` 搜索subject中的匹配串，并用replacemnet代替所有匹配串
- array `preg_split(pattern, subject)` 以字符串集合形式返回匹配结果

### 规则

元字符包括：`^$[]\.|?*+()`

- `^head`, `tail$` 定义头部和尾部
- `.` 匹配除`\n`外的任何单个字符
- `[]` 匹配指定范围内单个字符，匹配范围形如`aeiou`, `a-z`
- `|` 或操作 在多项之间选择一个进行操作 `(a|e|i|o|u|oo)`
- `\` 转义
- `()` 标记子表达式的开始位置和结束位置
- `*` 匹配左边的子表达式0次或多次
- `+` 匹配左边的子表达式至少1次
- `?` 匹配左边的子表达式0次或1次
- `{a,b}` 匹配左边的子表达式[a,b]次，如果b省略则是∞

### 修正符

PHP还有自己的一套修正符可以使用

## Chpater 14 数据库

### Mysqli

- `new mysqli(host, usrname, pwd, dbname, port)`, `mysqli::close()`
- `select_db(dbname)`
- `query(sql)`
- `error` 错误信息

结果集

- 使用数字索引数组或关联索引数组均可访问
- `num_rows`
- `fetch_row()`

```php
while ($row = $result->fetch_row())
{
    // body
}
```

### RedBeanPHP

零配置ORM（对象关系管理）类库，兼容MySQL和SQLite等

CRUD：Create, retrieve, update, delete

## Chapter 15 Composer 项目依赖管理

## 源

- 清华大学出版社 2017 《PHP+MySQL网站开发从零开始学》 樊爱宛，黄凯 如果熟悉C语言学习PHP会很方便，很喜欢这本书的风格
