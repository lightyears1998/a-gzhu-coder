
#include "task5.h"


void client()
{
    int msgqid = msgget(MSGKEY, 0777);
    for (int i = 10; i >= 1; i--)
    {
        msg.mtype = i;
        sprintf(msg.mtext, "%d", i);
        printf("Client: sent %d\n", i);
        msgsnd(msgqid, &msg, sizeof(struct msgform), 0);
    }
    exit(0);
}

void main()
{
    client();
}
