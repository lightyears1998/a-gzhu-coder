# Python笔记

## Chpater 0 概述

> 从减少程序开发人员的工作上来说，Python似乎做到了这一点。

某种程度上可视为改良的LISP。

## Chapter 1 基本概念

目前主流的Python版本有Python2和Python3，语法不兼容。

Python脚本文件`.py`通过Python解释器`python`边解释边运行。

在官方解释器*CPython*之外存在其他Python解释器，具有相当程度的性能优势，如*PyPy*。

在Python中，数字类型是不可变的对象，因此数字类型没有自增和自减操作符。

Python的表达式子可以省略分号；如果在一行中存在多个语句，则最后一个语句之前的分号是必须的。

## Chapter 2 数据类型与变量

变量不需要声明类型，标志符使用字母数字和下划线。

变量就是变量，没有所谓类型。变量“类型”指变量所指向的内存中的对象的类型。

六种基本数据类型

- *Number* 包括`int`, `float`, `bool`以及`complex`，内建大整数支持
- *String* 使用成对出现的单引号或双引号创建
- *Tuple* 使用小括号`()`创建
- *List* 使用中括号`[]`创建
- *Dictionary* 使用花括号`{}`配合冒号作为分隔符创建
- *Set* 使用花括号`{}`或者`set()`创建，必须用`set()`创建空集合，因为花括号默认用于创建Dictionary

前三种数据类型：*Number*，*String*，*Tuple*是不可变类型（immutable）；后三种：*List*，*Dictionary*，*Set*是可变类型（mutable）。

可以采用多变量赋值语法

```python
a, b, c = 2, 3, "5"
```

使用`type()`查看变量类型。

变量定义之后可以删除定义，`del name_of_variable`。

### None 无类型

未定义返回类型的函数返回`None`

`None`可被转换成布尔类型值的`False`

### Number 数字

- `True`, `False`在参与数字运算时分别转化为1和0
- 转换 `int()`, `bin()`
- 布尔表达式 `and(&&)`, `not(!)`, `or(||)` and的优先级高于or，与C++保持一致。
- 四则运算
- 浮点除法 `/` 整除 `//`
- 取模 浮点取模 `%`
- 乘方 `**`

### String 字符串

用`''`或`""`来声明，单引号与双引号作为定界符需要成对出现，两者无区别。

- 不能与数字直接相加
- 与整数的乘法，如`str * 3`会复制字符串

#### `format()`

```py
nums = [4, 5, 6]
msg = "Numbers: {0}, {1}, {2}".format(nums[0], nums[1], nums[2])

msg = "({x}, {y})".format(x=5, y=2)
```

#### 字符串工具函数

- `分隔符.join([字符串列表])` 形如PHP中的`implode()`，利用分割符合并字符串
- `startswith()`, `endswith()`

### Tuple 元组

元组与list行为类似，但是immutable对象。使用小括号而不是方括号。也可以不使用小括号，直接使用逗号分隔元素即可。

```py
# list
list = ["one", "two"]

# dictionary
dictionary = {1:"one", 2:"two"}

# tuple
tuple = ("one", "two")
tuple = "one", "two"
```

### List 列表

List使用方括号`[]`定义，下标从0开始。

```py
['1', '2', '3', ]  # List中只有3个元素
```

List间加法乘法操作有效。

#### 列表工具函数

- `in` 操作符判断元素是否在List内
- `len()` 返回List的长度

#### 方法

- `append()`
- `insert()` 原位置元素后移
- `index()` 返回值的第一个索引位置，不存在时抛出`ValueError`

#### Slicing 切片

- `[bgn:end:step]` 以步长step包含元素[bgn, end)，三个参数都不是必要的
- 注意bgn可以大于end（所以上面那个区间的写法是错的😅），生成的方向总是从bgn到end，且不包含end
- 如果索引index为负数，它是指从后往前数第index个字符；`[2:-2]`生成[2, 倒数第二个字符)
- `[::-1]` 反转数组，如果步长为负数，那么List会反向生成
- Tuple及字符串也有类似方法

#### Comprehensions 列表解析器

从数学的集合语法（set-builder notation）中脱胎的列表解析器

```py
cubes = [i**3 for i in range(5)]                     # [0, 1, 8, 27, 64]
evens = [i**2 for i in range(10) if i**2 % 2 == 0 ]  # [0, 4, 16, 36, 64]
```

滥用列表解析器可能产生MemoryError，可使用generator缓解。

### Dictionary 字典

```py
ages = {"Dave": 24, "Mary":42, "John":58}

print("Mary" in ages)      # True
print("Will" not in ages)  # True

ages.get("Dave")
ages.get("Hurry")          # 返回None
ages.get("Hurry", 34)      # 返回34
```

只有不变的（immutable）对象才能作为Dictionary的键，否则抛出KeyError。

## Chapter 3 控制语句

### `if`

```python
if exp:
    # Something

if exp:
    # Something
else:
    # Something

if exp:
    # Something
elif exp2:
    # Something
else:
    # Something
```

### `while`

```python
i = 0
while i <= 5:
    i = i + 1
```

### for

Python中没有C语言风格的`for`，注意到Python中的`for`实际上为`foreach`

```python
for word in words
    # Something

for i in range(5)
    # Something
```

## Chpater 4 函数

```python
def fun(arg1, arg2):
    # 函数体
```

参数类型限定

```python
def fun(arg:int):
    # 函数体
```

### Docstrings 函数注释

```python
def shout(word):
  """
  Print a word with an
  exclamation mark following it.
  """
  print(word + "!")

shout("spam")
```

### Modules 模块

```python
import random
from math import pi
from math import sqrt as rt
```

## Chapter 5 异常

```python
try:
    # Something
except:
    raise # 重新抛出异常
except(Error, Error):

finally:
    # 即使产生未捕获的异常时也会执行

raise NameError("Invilid Name!")

assert exp # 断言失败即抛出异常
assert exp, "额外说明"
```

异常处理是按配对的。

## Chapter 6 工具函数

### range()

- `range(n)` 生成[0, n)的列表
- `range(i, j)` 生成[i, j)的列表
- `range(i, j, k)` 生成[i, j)的等差列表，公差为k

## Chapter 7 文件IO

### `open()` and `close()`

```python
# write mode
open("filename.txt", "w")

# read mode
open("filename.txt", "r")
open("filename.txt")

# binary write mode
open("filename.txt", "wb")

file.close()
```

### read()

```python
file = open("filename.txt", "r")
print(file.read(16)) # 按字节数量读取
print(file.read())   # 读取剩余文本
print(file.read())   # 输出空串
file.close()
```

```python
file = open("filename.txt", "r")
print(file.readlines(16)) # 返回list，按行分割，元素中包含换行符
```

### write()

`file.write(content)`

不附加换行符，返回写入文件的字符数量。

### 保证close()方法最终被调用

使用异常处理机制：

```python
try:
    file = open("in.txt")
finally:
    file.close()
```

使用with... as...机制：

```python
with open("in.txt") as file:
    printf(f.readlines())
```

## 链接

- SoloLearn Python <https://www.sololearn.com/Play/Python>
