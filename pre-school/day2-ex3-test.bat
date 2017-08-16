@echo off
goto start

====== 注释开始啦 ======

这个批处理脚本可以产生随机数测试程序的排序算法
Enjoy it~

<提示>
停止批处理的办法是在命令行工具中按 Ctrl+C
（C可能代表Cancel？？ 知道的同学请讲一下 ☆⌒(*＾-゜)v THX!!）

====== 注释结束了 ======

:start
if "%1" neq "next" ( chcp 65001 )

set a=%random%
set b=%random%
set c=%random%
set d=%random%

echo %a%,%b%,%c%,%d% -输入-
echo %a%,%b%,%c%,%d%|.\bin\day2-ex3.exe
echo.

%0 next
