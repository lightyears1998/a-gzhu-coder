#include "task6.h"

void client()
{
    int shmid = shmget(SHMKEY, SHMSIZE, 0777);  // 打开共享存储区
    int *addr = shmat(shmid, 0, 0);             // 获取共享存储区首地址
    for (int i = 9; i >= 0; i--)
    {
        while (*addr != -1) continue;
        *addr = i;
        printf("Client: sent %d\n", i);
    }
    exit(0);
}

int main()
{
    client();
}
