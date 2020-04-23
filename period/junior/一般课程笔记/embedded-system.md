# 嵌入式系统的一些基本概念

- 存储空间映射 整个寻址空间的划分——系统空间、进程空间、外设空间；高速与低速的设备共存。
- 微控制器架构 指令集架构
  - RISC: ARM, MIPS
  - CISC: Atom
- 中断和异常处理
  - 硬件中断（外部中断） 可屏蔽、不可屏蔽
  - 软件中断 特权指令

- 通用输入输出端口GPIO
  - Bit-Band操作：直接操纵特定位
  - 输入：浮空、上拉（嵌位在高）、下拉、模拟
  - 输出：开漏（做电流型的驱动）、推挽（可以输出高，低电平，连接数字器件）、复用开漏、复用推挽
- 计时器
- 脉冲宽度调制PWM（输出电压通过通、断的时间来控制）
- 同步串行接口

- Arm汇编格式

---

Analog-to-digital converter, ADC
Bit Rate，Baut Rate, 波特率

---

## 实时笔记

### 4.20

1. <https://www.icourse163.org/learn/XMU-1001766012?tid=1450373443#/learn/content>
2. UART
3. 115200b/s coom1, coom2, 不要选中Flow Control
4. rs232与rs485只有高低电平不同；rs232 5V传输距离2M；rs485 12V距离可达100M。
5.重点SSI
