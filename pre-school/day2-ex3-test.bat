@echo off
set a=%random%
set b=%random%
set c=%random%
set d=%random%
echo %a%,%b%,%c%,%d% <输入> 
echo %a%,%b%,%c%,%d%|.\a.exe
echo.
%0
