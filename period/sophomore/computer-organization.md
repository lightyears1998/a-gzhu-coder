# 计算机组成原理

## Chapter 1 概述

### 计算机发展的历史

- ENNIC 元祖计算机
- 第一代 储存程序概念、电子管
- 第二代 高级语言、晶体管
- 第三代 集成电路
- 第四代 超大规模集成电路

### 性能评估术语

- Clock, tick, clock tick, clock, cycle 时钟周期
- Clock rate 时钟频率，是时钟周期的倒数
- CPI, cycles per instruction
- CPU时间（系统CPU时间、用户CPU时间）
- Throughput 吞吐率（Bandwidth 带宽）
- Response time, execution time, latency 响应时间、执行时间、延迟
- MIPS, million instruction per second（峰值MIPS）
- SPEC ration 将测试程序在Sun SPARCstation上的运行时间除以在机器上的运行时间得到的比值，越大性能越好

## Chapter 2 数据的机器级表示

## Chpater 3 运算方法和运算部件

## Chpater 4 指令系统

指令的分类：

1. 微指令 属于硬件范畴，微程序级命令
2. 机器指令 两者之间
3. 伪（宏）指令 属于软件范畴

### 指令格式设计

指令必须携带的信息：

1. 操作码
2. 源操作数或其地址
3. 结果地址
4. 下一条指令地址（通常隐含在Program Counter, PC或Instruction Pointer, IP中）

指令按其携带地址信息的个数可分为三地址指令、二地址指令、一地址指令和零地址指令。

### 指令格式设计原则

1. 尽量短
2. 有足够操作码位数（考虑预留空间，向后兼容）
3. 操作码有唯一的解释
4. 指令长度是byte的整数倍
5. 指令尽量规整

### 指令系统设计

基本问题包括：操作码、数据类型、指令格式（定长/变长）、通用寄存器、寻址方式、下一条指令地址等。

操作数类型待补充。

寻址方式包括：立即寻址（在指令中给出操作数/立即数）、直接寻址（给出操作数的有效地址）、间接寻址（@符号是间接寻址的标记）、多重间接寻址、寄存器寻址、寄存器间接寻址、三种偏移寻址（变址寻址、基址寻址和相对寻址）、其他寻址方式等。

操作类型待补充。

### 指令系统实例

待补充。

### 程序的机器级表示

待补充。

---

## 术语表

MIPS

- Milion instructions per second
- Machie instruction processing system
