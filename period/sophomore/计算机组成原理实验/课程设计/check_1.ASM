;课程设计检查程序1,含除跳转指令外的12条指令：
;add,and,dec,ldi,clr,rl,rr,ldr,sta,mov,out,hlt
#LOAD "LIGHTYEARS1998.IS"  ;预调入指令系统/微程序

org 0

start:

LDI r0,12h
sta 100h,r0
lda r1,100h
dec r1
rl  r0
add r0,r1
rr  r0
add r0,r1
ldi r2,76h
and r2,r0
mov r3,r2
add r3,r1
clr r0
out ioh,r3
hlt

end
