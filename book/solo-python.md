# 自学Python

https://www.sololearn.com/Play/Python

## 基本概念

字符串 `'' 或 ""`
浮点除法 `/ 整除 //`
取模 浮点取模 `%` 
乘方 `**`
不存在自增/自减操作符：整数对象不可变

交互式IO `input('提示')`

### 字符串

不能与数字直接相加

与整数的乘法会复制字符串

### 类型

类型转换 `int()`

变量无需声明类型，合法的变量名使用数字、字母和下划线，大小写敏感。

删除定义 `del name_of_a_varible`

#### 布尔类型

True False

整数与浮点数直接比较的浮点误差存在，但误差远小于1e-9。

and(&&) not(!) or(||) 可用于连接布尔表达式，优先级最低；
and的优先级高于or，与C++保持一致

## 控制语句

### if
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

### while

```python
i = 0
while i <= 5:
	i = i + 1

```

### for

foreach语法

```python

for word in words
	# Something

for i in range(5)
	# Something

```

## 数据类型

### List

下标从0开始。

List间加法乘法操作有效。


```python

['1', '2', '3', ] # List中只有3个元素

```

`in` 操作符判断元素是否在List内

`append()` `len()` 
`insert()` 原位置元素后移
`index()`

## 函数与工具函数

```python

def fun(arg1, arg2):
	# 函数体

```

### Docstrings

```python

def shout(word):
  """
  Print a word with an
  exclamation mark following it.
  """
  print(word + "!")
    
shout("spam")

```

### Modules

`import random`
`from math import pi`
`from math import sqrt as rt`

### range()

`range(n)` 生成[0, n)的列表
`range(i, j)` 生成[i, j)的列表
`range(i, j, k)` 生成[i, j)的列表，元素间隔2

## 异常

```python

try:

except:
	raise # 重新抛出异常
except(Error, Error):

finally:
	# 即使产生未捕获的异常时也会执行

raise NameError("Invilid Name!")

assert exp # 断言失败即抛出异常
assert exp, "额外说明"

```

## 文件IO

### open() close()

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
print(file.readlines(16)) # 返回list，按行分割，元素包含换行符

```
