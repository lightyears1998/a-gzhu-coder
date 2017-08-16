@echo off
if "%1" neq "next" ( chcp 65001 )
set a=%random%
set b=%random%
set c=%random%
set d=%random%
echo %a%,%b%,%c%,%d% -输入-
echo %a%,%b%,%c%,%d%|.\bin\day2-ex3.exe
echo.
%0 next
