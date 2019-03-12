# Ocatave笔记

## Chapter 0 概述

与Matlab语法兼容开源科学计算与数值分析工具。

## Chpater 1 基本概念

- 三角函数使用弧度制
- 自然对数是 *log* 而不是 *ln*
- 选择数值显示的方式 `format` `help format`
- 保存和读取工作环境/变量 `save <filename> [var1] [var2] [...]` `load <filename>`
- 在语句末尾使用分号 `;` 来隐藏显示
- 保持语义的换行是`...`，不要在省略号后附加任何符号
- 分屏显示 `more <off / on>` `space` 下一页 `b` 上一页 `q` 退出
- `disp()` 显示字符串或变量的值

## Chpater 2 变量

区分大小写 避免数值的截断误差
`who` 命令查看当前命名的函数和变量
`clear [var-name]` 清除全部变量或特定变量

## Chapter 3 数组和向量

- 构造向量
  - `a = [1 3 5]`
  - `b = [2, 4, 6]`
  - `c = [3; 6; 9]`
  - 逗号或空格隔开是行向量 由分号或回车隔开将被定义为列向量
  - `d = [a 6]` 在a的基础上添加新元素6
  - [a : step : b] 创建[a, b]之间的变量，步长为step
- 向量的构造函数
  - `zeros(M, N)`
  - `ones(M, N)`
  - `linspace(x1, x2, N)` 创建N个元素的向量，均匀分布于x1和x2
  - `logspace(x1, x2, N)`  创建N个元素的向量，指数均匀分布于x1和x2
- 向量元素操作
  - 下标从1开始
  - `a(3)` 取得第3个元素，注意没有使用中括号
  - `a(1:2:10)` 利用冒号表示法
- 向量运算
  - `*` `/` `+` `-` 向量运算
  - 在算符前添加 `.` 对单个元素的运算，如 `a .* 2`

## Chapter 4 绘图

设置Graphics Toolkit

`graphics_toolkit("gnuplot")` 备选："qt"及"gnuplot"

### 绘图指令

- `figure()` 启动一个绘图环境
- `hold on`, `hold off` 保持/不保持上个指令的绘制状态

- `title('标题')`
- `xlabel()` `ylabel()`
- `axis(xbegin, xend, ybegin, yend)`

### `plot(x, y)`

- `plot(x, y)`
- `plot(x, y, '+')`

更多选项

- `plot(t, nw, '+', 'MarkerSize', 12)`
- `plot([25:1:55], fun(P, [25:1:55]), 'LineWidth', 5)`

### 输出为图片

`print('figure.png', '-dpng')`;

## Chapter 5 逻辑

```matlab
if expression
    statements
elseif expression
    statements
else
    statements
end

switch x
    case x1
        statements
    otherwise
        statements
end

for varible = vector
    statements
end

while expression
    statements
end
```

## Chapter 6 数据处理

### 逆转行列

`filplr()` `flipud()`

### 拟合

线性拟合工具 `P = polyfit(x, y, n)` n为拟合曲线的次数
线性拟合求值函数 `polyval(P, t)` 返回拟合曲线在t处的值

非线性拟合工具 `lsqcurvefit`

```matlab
% 变温粘滞系数 Figure nw-t 图像 %

nw = [.548, .469, .343, .222, .182];
t = [ 30, 35, 40, 45, 50];

function rslt = fun(var, data)
  rslt = var(1) * exp(-var(2) * data);
endfunction

var0 = [0 0];
P = lsqcurvefit(@fun, var0, t, nw);

plot(t, nw, '+', 'MarkerSize', 12);
plot([25:1:55], fun(P, [25:1:55]), 'LineWidth', 5);
```

## 资源

### 教程

- 入门教程 <http://coer.zju.edu.cn/liu/octave-tutorial-cn.pdf>
- 在线网站 <https://octave-online.net/>

### Playground示例

- 大一下学期的物理实验 <https://github.com/lightyears1998/a-gzhu-coder/tree/master/period/freshman/%E7%89%A9%E7%90%86%E5%AE%9E%E9%AA%8C>
