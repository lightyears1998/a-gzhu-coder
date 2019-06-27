;谢金宏(aka. lightyears1998)的汇编程序
;软件171 1706300001

#LOAD "LIGHTYEARS1998.IS" ;预调入指令系统/微程序
#SET RAM 0260h = 5500h    ;数据区0260H单元预置数据5500h

org 0

tag1:
ldi r0,01h
ldi r1,01h
add r0,r0
jc tag1
halt



halt

end