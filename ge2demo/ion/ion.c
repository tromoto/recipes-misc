#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"    
#include "sys/ioctl.h"
#include "fcntl.h"     
#include "asm/etraxgpio.h"







int main(void) {
  int fd;
  int i;
  int iomask;

  if ((fd = open("/dev/gpiog", O_RDWR))<0) {
    printf("Open error on /dev/gpiog\n");
    exit(0);
  }

  iomask=1<<25;

  for (i=0;i<10;i++) {
    printf("Led ON\n");
    ioctl(fd,_IO(ETRAXGPIO_IOCTYPE,IO_SETBITS),iomask);
    sleep(1);

    printf("Led OFF\n");
    ioctl(fd,_IO(ETRAXGPIO_IOCTYPE,IO_CLRBITS),iomask);
    sleep(1);
  }
  close(fd);
  exit(0);
}
