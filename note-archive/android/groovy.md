# Groovy笔记

## 基础语法

- 分号可以省略
- 括号在不产生歧义时可以省略

Groovy没有Primitive type，所有类都使用包装类

Groovy自动引入如下包：

1. java.lang, java.util, java.io, java.net
2. groovy.lang, groovy.util

java.math.BigInteger和Java.math.BigDecimal在没有引入语句时也可使用

## 基本数据类型

```groovy
assert 3.class == Integer
assert (3.5).class = BigDecimal
assert 'abc' instanceof String
assert "abc" instanceof String

String name = 'Dolly'
assert "Hello, ${name}!" == 'Hello, Dolly!'  // 字符串插值完整形式
assert "Hello, $name" == 'Hello, Dolly!'     // 字符串插值无歧义时的简短形式
assert "Hello, $name" instanceof GString
```

静态数据类型和动态数据类型

```groovy
Integer n = 3
Date now = new Date()

def x = 3
assert x.class = Integer
x = 'abc'
assert x.class = String
x = new Date()
assert x.class = Date
```

Groovy真值

- 非0数字是真
- 非空集合是真
- 非null引用是真
- Boolean类型的true是真

## 操作符重载

- 求幂运算 `**`
- String的操作符重载 `-`

## 集合

- 定义集合 `def nums = [1, 1, 2, 3, 5]` ArrayList默认语法
- 转换集合 `Set uniques = nums as Set` `as`用于转换兼容集合
- `Range(a, b)`闭区间[a, b] `[a..b]`

Map:

- `def map = [a:1, b:2, c:3]`
- `map.a`, `map['b']`, `map.get('c')`

## 闭包

each方法 提供每个元素一个闭包，然后一同被解析

```groovy
def nums = [1, 2, 3, 4, 5]
def doubles = []

nums.each { n ->  // 箭头操作符
    doubles << n * 2
}

assert doubles == [2, 4, 6, 8, 10]
```

在闭包中修改闭包外定义的变量被认为是由副作用的。

collect方法 在每个元素上应用一个闭包collect方法

```groovy
def nums = [1, 2, 3, 4, 5]
def doubles = nums.collect { it * 2 }
assert doubles = [2, 4, 6, 8, 10]
```

如果一个方法接受闭包作为最后一个参数，这个闭包通常在括号之后添加

## POGOs

只包含属性和getters，setters的类：Plain Old Java Objects(POJOs)
类似的，Groovy中称为Plain Old Groovy Objects

```groovy
import groovy.transform.Canonical

@Canonical
class Event {
    String name
    Date when
    int priority
}
```

对于一个POGO

- 类默认public
- 属性默认private
- 方法默认public
- getters, setters未被标记成public或者private
- 自动生成一个默认构造器和一个基于map的构造器（可以使用atrribute:value形式的参数）

@Canonical注解

- 触发一个抽象语法树（Abstract Syntax Tree, AST）的转换
- 是@ToString，@EqualsAndHashCode和@TupleConstructor的简写
- @ToString 提供toString方法
- @EqualsAndHashCode equals 检查等值性 hashcode 基于属性的值生成一个整数
- @TupleConstrutor 添加附加构造函数，依次接受所有的属性为参数

```groovy
Event e1 = new Event(name: 'Android Studio 1.0',
    when: Date.parse('MMM dd, yyyy', 'Dec 8, 2014'),
    priority: 1)

Event e2 = new Event(name: 'Android Studio 1.0',
    when: Date.parse('MMM dd, yyyy', 'Dec 8, 2014'),
    priority: 1)

assert e1.toString() = ...
assert e1 == e2
```

## 源

- 电子工业出版社 2017 《巧用Gradle构建Android应用 Gradle Receipe for Android》 Ken Kousen，李建 简单地介绍了必要的groovy知识
