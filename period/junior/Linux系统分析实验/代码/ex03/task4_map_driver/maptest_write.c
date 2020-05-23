// maptest_write.c

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

#define LEN (10 * 4096)

int main(void)
{
   int fd;
   if ((fd = open("/dev/mapnopage", O_RDWR)) < 0)
      return 0;

   char *vadr = mmap(0, LEN, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_LOCKED, fd, 0);
   sprintf(vadr, "Write from userspace");

   while (1)
      sleep(1);
   return 0;
}
