;课程设计检查程序2,含3条跳转指令：
;jz,jc,jmp
#LOAD "LIGHTYEARS1998.IS"

org 0

start:                     LDI  r0,12h
                           sub  r0,r0
                           jz tag1
                           ldi  r3,0eeh
                           jmp tag2
tag1:                      ldi r3,33h
tag2:                      ldi r0,88h
                           add r0,r0
                           jc tag3
                           ldi r2,0eeh
                           jmp tag4
tag3:                      ldi r2,22h
tag4:                      ldi r1,11h
                           ldi r0,0
                           add r1,r0
                           jz tag5
                           jmp tag6
tag5:                      ldi r1,0eeh
tag6:                      jc tag7
                           ldi r0,0h
                           jmp tag8
tag7:                      ldi r0,0eeh
tag8:                      hlt

end
