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
int commandint[10];
  __u8 command[10];

  //for (port = 0; port < 127; port++) {
    if (ioctl(device, I2C_SLAVE, port) < 0)
      perror("ioctl() I2C_SLAVE failed\n");
    else
      {
      res = i2c_smbus_read_word_data(device,0);
	int i=0;
	for (;;){
      		res1 = i2c_smbus_read_i2c_block_data(device,0,10,command);
               commandint[10]=(int)command[10];
		for(i=0;i<10;i++) {
      			printf("command : %d \n", command[i] );
				   }	
		printf("**************************** \n");
      
}
    }
  }

void write_i2c_motor(int device,int leftpwm, int rightpwm) {
	int port = 64 ;// 0X40 address of motor
	int writeResult;
	unsigned long funcs;
	__u8 command[2];	
		if (ioctl(device, I2C_SLAVE, port) < 0)
      		   perror("ioctl() I2C_SLAVE failed\n");
    		else {

			writeResult =i2c_smbus_write_word_data(device, 0x30, rightpwm);
			printf("writeResult %d\n", writeResult);
			writeResult =i2c_smbus_write_word_data(device, 0x34,leftpwm);
			printf("writeResult %d\n", writeResult);
			//int result=i2c_smbus_read_byte_data(device,0x10);
			 if (funcs & I2C_FUNC_I2C)
			   printf("I2C\n");
		         if (funcs & (I2C_FUNC_SMBUS_QUICK))
			   printf("I2C_FUNC_SMBUS_BYTE\n");
			//printf("result %d\n", result);
			
                      }



                                  }

int speed2pwm(int speed) {
		int maximumspeed=100;
		int minimumspeed=0;
		int higestpwm = 4095;
		int lowestpwm = 0;
		int pwmvalue=0;
		pwmvalue=(speed-minimumspeed) * (higestpwm-lowestpwm)/(maximumspeed-minimumspeed)+lowestpwm;
		return pwmvalue;

                          }


int main(void)
  {
  int device,leftspeed,rightspeed,leftpwm,rightpwm;
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

  	scan_i2c_bus(device);

/*while(1) {
	printf("enter speed for left wheel (0-100)\n");
	scanf("%d",&leftspeed);
	printf("enter speed for right wheel (0-100)\n");
	scanf("%d",&rightspeed);
    
if((leftspeed <= 0) && (leftspeed > 100) && 
    (rightspeed <= 0) && (rightspeed > 100))
	{
		printf(" speed of wheel (0-100)\n");

		printf("enter speed for left wheel (0-100)\n");
		scanf("%d",&leftspeed);
		printf("enter speed for right wheel (0-100)\n");
		scanf("%d",&rightspeed);
 	}
else {

leftpwm=speed2pwm(leftspeed);
rightpwm=speed2pwm(rightspeed);
write_i2c_motor(device,leftpwm,rightpwm); 

}

} */
	


  return 0;
  }
