# Java笔记

> 言语创造了思想，思想是人类对宇宙的度量。

## Chpater 0 概述

诞生于1990年，源自甲骨文的跨平台解决方案。

## Chapter 1 基本概念

源文件的拓展名是`.java`，需要使用Java编译器*Java Complier*`javac`编译成字节码`.class`，然后载入Java虚拟机*Java Virtual Machine*`java`运行。

Java使用引用来操作对象。Java使用垃圾回收器来监视使用`new`创建的所有对象，辨明不再需要的对象，随后释放这些对象的内存空间。

Java类中的数据成员称为“字段”，成员函数称为“方法”。

## Chapter 2 数据类型

> 一切都是对象

boolean(Boolean), char(Character), byte(Byte), short(Short), int(Integer), long(Long), float(Float), double(Double), void(Void)

BigInteger, BigDecimal

## Chapter 3 类

### 初始化

Java为类的基本数据成员提供默认的初始化。
