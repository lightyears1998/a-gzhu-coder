;谢金宏(aka. lightyears1998)的汇编程序
;软件171 1706300001

#LOAD "LIGHTYEARS1998.IS" ;预调入指令系统/微程序
#SET RAM 0260h = 5500h    ;数据区0260H单元预置数据5500h

org 0

ldi r0,00h
ldi r1,01h
ldi r2,02h
ldi r3,03h

end