#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wiringPi.h>

#define PORT 64
#define PORTMOTORSTART 16
#define leftmotor 21
#define rightmotor 22

void write_i2c_motor(int leftpwm, int rightpwm, int device) {


	
	int  writeResultleft,writeResultright, resultLength;
	
	__u8 rawData[1];	
		
		
		
		printf("device %d\n", device);
		if (ioctl(device, I2C_SLAVE, PORT) < 0)
      		   perror("ioctl() I2C_SLAVE failed in writing values to address\n");
    		else {
			
			writeResultleft =i2c_smbus_write_word_data(device, 0x34,leftpwm);
			printf("writeResultleft %d\n", writeResultleft);
			
			if (writeResultleft == -1)
			{
			writeResultleft =i2c_smbus_write_word_data(device, 0x34,leftpwm);
			printf("writeResultleft %d\n", writeResultleft);
			}
			writeResultright =i2c_smbus_write_word_data(device, 0x30, rightpwm);
			printf("writeResultright %d\n", writeResultright);
		
						
                      }
                        
         
                      
               }
               
 void start(int device) {
	 
	  int resultLength;
	 __u8 rawData[1];
	
			printf("device %d\n", device);
			if (ioctl(device, I2C_SLAVE, PORTMOTORSTART) < 0)
      		   perror("ioctl() I2C_SLAVE failed in the start call\n");
    		else {
			resultLength = i2c_smbus_read_i2c_block_data(device,0x25,0,rawData);
			//resultLength = i2c_smbus_read_byte(0x25);
			printf("rawData[0]  %d \n",rawData[0]);
			printf("resultLength %d\n", resultLength);
			
		}
	 
	 }
               
 void stop(int device) {
	 
	 int resultLength;
	 __u8 rawData[1];
	
			printf("device %d\n", device);
			if (ioctl(device, I2C_SLAVE, PORTMOTORSTART) < 0)
      		   perror("ioctl() I2C_SLAVE failed in the start call\n");
    		else {
			resultLength = i2c_smbus_read_i2c_block_data(device,0X24,0,rawData);
			printf("rawData[0]  %d \n",rawData[0]);
			printf("resultLength %d\n", resultLength);
					
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


int main() {
int leftspeed,rightspeed,leftpwm,rightpwm, direction,device;
unsigned long funcs;


if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		
		}
		
else {
	
	
	if ((device = open("/dev/i2c-1", O_RDWR)) < 0)
  		  {
  			  perror("open() failed");
    			  exit (1);
  		  }
		
		pinMode(leftmotor,OUTPUT);
		pinMode(rightmotor,OUTPUT);
		printf("pin mode sucessfully setup \n");
		}


while(1) {
	
	printf("enter speed for right wheel (0-100)\n");
	scanf("%d",&rightspeed);
	
	printf("enter speed for left wheel (0-100)\n");
	scanf("%d",&leftspeed);
	
	printf("enter direction for (0-fwd, 1/ bkwd)\n");
	scanf("%d",&direction);
    



leftpwm=speed2pwm(leftspeed);
rightpwm=speed2pwm(rightspeed);

write_i2c_motor(leftpwm,rightpwm, device);
start(device) ;
  
digitalWrite(leftmotor, direction);
digitalWrite(rightmotor, direction);


} 
return 0;
}
