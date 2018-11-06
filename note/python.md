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

- *Number* 包括`int`, `float`, `bool`以及`complex`
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

工具函数

- `min()`, `max()`
- `abs()`
- `sum([list])` 只适用于列表List

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
- `startswith()`, `endswith()` 返回真与假
- `replace('what', 'with')` 将字符串中的所有`what`替换为`with`
- `upper()`, `lower()` 字符串全文大小写转换
- `split('separator')` 分割字符串为列表

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

Tuple Unpacking

```py
numbers = (1, 2, 3)
a, b, c = numbers

# a = 1, b = 2, c = 3
```

```py
numbers = [1, 2, 3, 4, 5]
a, *b, c = numbers

# a = 1, b = [2, 3, 4], c = 5
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

注意到，Tuple及字符串也有类似方法

- `[bgn:end:step]` 以步长step包含元素`[bgn, end)`，三个参数都不是必要的
- 注意bgn可以大于end（所以上面那个区间的写法是错的😅），生成的方向总是从bgn到end，且不包含end
- 如果索引index为负数，它是指从后往前数第index个字符；`[2:-2]`生成`[2, 倒数第二个字符)`
- `[::-1]` 反转数组，如果步长为负数，那么List会反向生成

#### Comprehensions 列表解析器

从数学的集合语法（set-builder notation）中脱胎的列表解析器

```py
cubes = [i**3 for i in range(5)]                     # [0, 1, 8, 27, 64]
evens = [i**2 for i in range(10) if i**2 % 2 == 0 ]  # [0, 4, 16, 36, 64]
```

滥用列表解析器可能产生MemoryError，可使用generator缓解。

#### 其他谓词

- `all()`, `any()`

  ```py
  nums = [55, 44, 33, 22, 11]

  if all([i > 5 for i in nums]):
  print("All larger than 5")

  if any([i % 2 == 0 for i in nums]):
  print("At least one is even")
  ```

- `enumerate()` 按键值对的方式遍历列表，返回元组

  ```py
  for v in enumerate(nums):
   print(v)
  ```

### Set 集合

- 使用`set()`接受一个列表作为参数构建集合
- `add()` 添加元素
- 合并`|`, 同时存在`&`, 不同时存在`^`, 差（第一个集合中包含而第二个集合中不包含）`-`

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

### `for`

Python中没有C语言风格的`for`，注意到Python中的`for`实际上为`foreach`

```python
for word in words
    # Something

for i in range(5)
    # Something
```

### 三元运算 Ternay Operator

```py
b = 1 if a >= 5 else 42
```

### 与其他语句块配对的`else`

如果else与循环配对，如果循环不是以break方式退出，else语句块将被执行

如果else与try块配对，仅当没有异常时会执行else里的语句

## Chpater 4 函数

```python
def fun(arg1, arg2):
    # 函数体
```

参数类型限定

```python
def fun(arg: int):
    # 函数体
```

默认参数

```py
def fun(arg="default"):
    # 函数体
```

可变数量的参数

```py
def function(named_arg, *args):
    print(named_arg)
    print(args)  # args是一个tuple
```

关键字参数Key word arguments（未提前定义的具名参数）

```py
def my_func(x, y=7, *args, **kwargs):
   print(kwargs)  # kwargs是一个字典

my_func(2, 3, 4, 5, 6, a=7, b=8)

"""
{'a': 7, 'b': 8}
"""
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

- `range(n)` 生成`[0, n)`的列表
- `range(i, j)` 生成`[i, j)`的列表
- `range(i, j, k)` 生成`[i, j)`的等差列表，公差为k

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

### `with`

```py
with open(filename) as f:
  text = f.read()
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

## Chapter 8 函数式编程

函数式编程，使用函数的编程。

函数式编程尽量不适用全局变量使得其返回值只依赖于它的参数。

### Lambda表达式

创建函数而不使用标识符

创建Lambda表达式并传入参数

```py
# named function
def polynomial(x):
    return x**2 + 5*x + 4
print(polynomial(-4))

# lambda
print((lambda x: x**2 + 5*x + 4) (-4))
```

为Lambda表达式分配标识符 `double = lambda x: x * 2`

#### `map(func, arg)`

使用iterable对象作为第二个参数，返回对每个参数进行func后的iterable

#### `filter(pred, arg)`

返回满足谓词的iterable对象

### Generator 生成器

属于iteralbe，但不能随机存取

使用`yield`关键字从生成器函数中返回值

```py
def countdown():
  i = 5;
  while i > 0:
    yield i
    i -= 1

for v in countdown():
  print(v)
```

### Decorator 装饰器

不修改原始函数而拓展其功能的方法

```py
def decor(func):
  def wrap():
    print('=================')
    func()
    print('=================')
  return wrap
```

使用`@`注记可以使函数包含在decorator中

```py
@decor
def print_text():
  print("Hello world!")
```

### itertools

1. `count(value)` 从value开始向无穷计数
2. `cycle(iterable)` 开始iterable的无穷循环
3. `repeat()` 无限或有限次的重复

```py
from itertools import count;

for i in count(3):
  print(i);
  if i > 10:
    break
```

1. `takewhile(pred, iterable)` 当谓词为真时继续循环
2. `chain()` 合并多个iterable
3. `accumulate()` 返回累计值

```py
from itertools import accumulate, takewhile

nums = list(accumulate(range(8)))
print(nums)  # [0, 1, 3, 6, 10, 15, 21, 28]
print(list(takewhile(lambda x: x<= 6, nums)))  # [0, 1, 3, 6]
```

1. `product()`
2. `permutation()`

```py
from itertools import product, permutations

letters = ("A", "B")
print(list(product(letters, range(2))))  # [('A', 0), ('A', 1), ('B', 0), ('B', 1)]
print(list(permutations(letters)))       # [('A', 'B'), ('B', 'A')]
```

## Chapter 9 面向对象编程

### 类

```py
class Cat:
  eyes = 'blue'

  __init__(self, color, legs):
    self.color = color
    self.legs  = legs
```

### 构造器`__init__`

使用`self`作为第一个参数

### 静态方法与非静态方法

非静态方法的一个参数总是`self`，没有`self`作为参数的方法是静态方法

```py
Obj().method()  # 非静态方法
Obj.smethod()   # 静态方法
```

与工厂方法统一，静态方法可以使用`@staticmethod`修饰符

### 类方法（工厂方法）

类方法使用`@classmethod`修饰器，并接受`cls`作为第一个参数，返回类的一个实例

```py
class Square:
  def __init__(self, width, length):
    self.width = width
    self.length = length

  @classmethod
  def new_square(cls, side_length):
    return cls(side_length, side_length)
```

### 类继承

```py
class Animal:
  def __init__(self, name, color):
    self.name = name
    self.color = color

class Cat(Animal):
  def purr(self):
    print("Purr...")

class Dog(Animal):
  def bark(self):
    print("Woof!")
```

### `super`

使用`super`关键字调用同名的基类方法

### 魔术方法

方法名由两个下划线包围的方法称为魔术方法，如`__init__`和`__add__`

### 操作符重载

使用魔术方法来重载操作符

- __sub__ for -
- __mul__ for *
- __truediv__ for /
- __floordiv__ for //
- __mod__ for %
- __pow__ for **
- __and__ for &
- __xor__ for ^
- __or__ for |

重载比较

- __lt__ for <
- __le__ for <=
- __eq__ for ==
- __ne__ for !=
- __gt__ for >
- __ge__ for >=

含有特殊功能的重载

- __len__ for len()
- __getitem__ for indexing
- __setitem__ for assigning to indexed values
- __delitem__ for deleting indexed values
- __iter__ for iteration over objects (e.g., in for loops)
- __contains__ for in

### 封装

The Python philosophy is slightly different. It is often stated as **"we are all consenting adults here"**, meaning that you shouldn't put arbitrary restrictions on accessing parts of a class. Hence there are no ways of enforcing a method or attribute be strictly private.

以单下划线开头的类成员不会被和数据不会被`from module_name import *`自动导入

**名称隐藏**：以双下划线开头的类成员在外部引用时需要使用不同的名称，形如`_classname__method`的形式

```py
class Spam:
  __egg = 7
  def print_egg(self):
    print(self.__egg)

s = Spam()
s.print_egg()            # 7
print(s._Spam__egg)      # 7
print(s.__egg)           # AttributeError: 'Spam' object has no attribute '__egg'
```

### 属性

以字段的形式访问方法，从而使特定的字段只读或能通过方法自动生成。

支持Setter语法

```py
class Pizza:
    def __init__(self, toppings):
        self.toppings = toppings
        self._pineapple_allowed = False

    @property
    def pineapple_allowed(self):
        return self._pineapple_allowed

    @pineapple_allowed.setter
    def pineapple_allowed(self, value):
        if value:
            password = input("Enter the password: ")
            if password == "Sw0rdf1sh!":
                self._pineapple_allowed = value
            else:
                raise ValueError("Alert! Intruder!")

pizza = Pizza(["cheese", "tomato"])
print(pizza.pineapple_allowed)
pizza.pineapple_allowed = True
print(pizza.pineapple_allowed)
```

## Chapter 10 正则表达式

```py
import re
pattern = r'regular_expression'
```

基本工具

1. `re.match(pattern, string)` 从开始匹配字符串，返回可供操作的对象
2. `re.serach(pattern, string)` 从任意位置开始匹配字符串
3. `re.findall(pattern, string)` 返回所有匹配的子串

match示例

```py
import re

pattern = r"pam"

match = re.search(pattern, "eggspamsausage")
if match:
   print(match.group())
   print(match.start())
   print(match.end())
   print(match.span())

"""
>>>
pam
4
7
(4, 7)
>>>
"""
```

搜索和替换 `re.sub(pattern, repl, string, max=0)`

```py
import re

str = "My name is David. Hi David."
pattern = r"David"
newstr = re.sub(pattern, "Amy", str)
print(newstr)
```

### 正则元字符

1. `.` 除换行符外的任意字符
2. `^`, `$` 匹配行的开头和行的结尾
3. `[aeiou]`, `[a-z]`, `[0-9]` 匹配字符组中的一个；使用`[^A-Z]`来取反（排除大写字母）
4. `*` 0个或更多前述字符
5. `+` 1个或更多前述字符
6. `?` 0个或1个前述字符 `pattern = r'ice(-)?cream'`
7. `{x, y}` [x, y]个前述字符
8. `|` 或
9. `\数字n` 匹配前一形式的n次后续重复 如`r"(.+)\1"`将匹配形如"word word", "abc abc"的字符串
10. `\d`, `\s`, `\w` 数字，空白字符或word characters；`\D`, `\S`, `\W`前述功能的取反
11. `\b` 匹配`\w`与`\W`之间的空字符串（non-word characters与word characters之间的空字符串）如`\bcat\b`会匹配“The cat sat!”和“We s>cat<\tered?”但不会匹配“We scattered.”
12. `\A`与`\Z`分别输入的开头和结尾（与`^`和`$`区别）

### Group

`group(), group(0)`返回整个匹配，`group(n)`返回第n个匹配的组

可以通过`(?P<name>...)`的形式声明命名的组，并通过`group('name')`来访问

可以通过`(?...)`的形式声明non-capture组，non-catpure组不能通过group函数来访问

搜索邮件地址

```py
import re

pattern = r"([\w\.-]+)@([\w\.-]+)(\.[\w\.]+)"
str = "Please contact info@sololearn.com for assistance"

match = re.search(pattern, str)
if match:
   print(match.group())
```

## Chapter 11 Zen of Python

```py
import this
```

## Chapter 12 包装

示例层次结构

```python
SoloLearn/
   LICENSE.txt
   README.txt
   setup.py
   sololearn/
      __init__.py
      sololearn.py
      sololearn2.py
```

还有py2exe这样的神奇的存在

## Chapter 13 Time / Datetime

```py
import time
import datetime
```

### `time`

- `time.time()` 生成当前时间的Linux时间戳

### `datetime.datetime`类

构造函数

1. `fromtimestamp()` 把时间戳解释成一个本地时区的datetime对象
2. `utcfromtimestamp()` 把时间戳解释成本地时区的datetime对象，并将此对象转换成UTC时间
3. `strptime(时间字符串, 格式字符串)`

```py
now = time.time()
local = datetime.datetime.fromtimestamp(now)
utc = datetime.datetime.utcfromtimestamp(now)
print(local, utc, sep='\n')  # 数值上UTC比本地时间（UTC+8）少8小时

"""
2018-10-15 19:08:10.914724
2018-10-15 11:08:10.914724
"""
```

#### `strptime()` Parse a string to achieve a datetime object

```py
utc   = '2018-10-08T06:23:34.000Z'  # 这样的格式或许在写JS的时候是比较常见的
local = '2018-10-08 14:23:34'       # 正常人用的时间格式 🤦‍

datetime.datetime.strptime(utc, '%Y-%m-%dT%H:%M:%S.%fZ')  # %y是两位数的年份，%f微秒左侧第一位为最高位
datetime.datetime.strptime(local, '%Y-%m-%d %H:%M:%S')
```

#### `strftime()` Generate a formatted time string

类型说明符与`strptime()`保持一致

### UTC时间与本地时间的互相转换

1. 借助`timestamp`

```py
def utc2local(utc: datetime.datetime):
    now = time.time()
    offset = datetime.datetime.fromtimestamp(now) - datetime.datetime.utcfromtimestamp(now)
    return utc + offset


def local2utc(local: datetime.datetime):
    now = time.time()
    offset = datetime.datetime.utcfromtimestamp(now) - datetime.datetime.fromtimestamp(now)
    return local + offset


timestamp = time.time()
local = datetime.datetime.fromtimestamp(time.time())
print('本地时间戳', timestamp)
print('本地时间', local)
print('UTC时间', local2utc(local))
print('本地时间（验证）', utc2local(local2utc(local)))


"""
本地时间戳 1539603479.3487046
本地时间 2018-10-15 19:37:59.348705
UTC时间 2018-10-15 11:37:59.348705
本地时间（验证） 2018-10-15 19:37:59.348705
"""
```

## 主流第三方库

- Django
- BeautifulSoup 爬虫
- matplotlib 数据图表生成
- NumPy 多维数组
- SciPy 拓展Numpy
- Panda3D / pygame 3D/2D游戏开发

## 链接

- SoloLearn Python <https://www.sololearn.com/Play/Python>
