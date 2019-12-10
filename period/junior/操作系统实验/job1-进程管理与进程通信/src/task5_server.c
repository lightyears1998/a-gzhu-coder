
#include "task5.h"


void server()
{
    int msgqid = msgget(MSGKEY, 0777 | IPC_CREAT);  // 创建消息队列
    do
    {
        msgrcv(msgqid, &msg, sizeof(struct msgform), 0, 0);
        printf("Server: received %s\n", msg.mtext);
    } while (msg.mtype != 1);
    msgctl(msgqid, IPC_RMID, 0);  // 删除消息队列
    exit(0);
}

void main()
{
    server();
}
