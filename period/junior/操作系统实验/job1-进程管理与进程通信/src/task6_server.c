#include "task6.h"

void server()
{
    int shmid = shmget(SHMKEY, SHMSIZE, 0777 | IPC_CREAT);  // 创建共享存储区
    int *addr = shmat(shmid, 0, 0);                         // 获取共享存储区首地址
    
    system("ipcs -m");
    do
    {
        *addr = -1;
        while (*addr == -1) continue;
        printf("Server: received %d\n", *addr);
    } while (*addr);
    shmctl(shmid, IPC_RMID, 0);  // 移除共享存储区
    
    printf("Server: exited.\n");
    exit(0);
}

int main()
{
    server();
}
