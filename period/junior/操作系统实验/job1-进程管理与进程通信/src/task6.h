#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

const int SHMKEY = 75;     // 共享储存区key
const int SHMSIZE = 1024;  // 共享存储区大小
