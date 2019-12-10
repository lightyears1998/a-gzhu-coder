#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

const int MSGKEY = 75;  // 使用75作为消息队列的key

// 消息队列中消息的格式
struct msgform
{
    long mtype;
    char mtext[1000];
} msg;
