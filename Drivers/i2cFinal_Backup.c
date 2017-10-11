#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BEAC1 0x00

/* Suche nach I2C-Adressen */
void scan_i2c_bus(int device)
  {
  int port= 17, res, res1;
  __u8 command[10];

    if (ioctl(device, I2C_SLAVE, port) < 0)
      perror("ioctl() I2C_SLAVE failed\n");
    else
      {
      res = i2c_smbus_read_word_data(device,0);
      int i=0;
      res1 = i2c_smbus_read_i2c_block_data(device,BEAC1,0x0a,command);
	for(i=0;i<res1;i++) {
      	printf("command : %d \n", command[i] );
		   }
    
    }
  }


int main(void)
  {
  int device;
  unsigned long funcs;

  printf("Opening device...");
  if ((device = open("/dev/i2c-1", O_RDWR)) < 0)
    {
    perror("open() failed");
    exit (1);
    }
  printf(" OK\n");
 
  if (ioctl(device,I2C_FUNCS,&funcs) < 0)
    {
    perror("ioctl() I2C_FUNCS failed");
    exit (1);
    }

//  if (funcs & I2C_FUNC_I2C)
//    printf("I2C\n");
//  if (funcs & (I2C_FUNC_SMBUS_BYTE))
//    printf("I2C_FUNC_SMBUS_BYTE\n");

  scan_i2c_bus(device);

  return 0;
  }
