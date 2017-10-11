#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define PORT 17
#define SENSORCOUNT 5
#define REGSTARTADDRESS 0
#define REGENDADDRESS (REGSTARTADDRESS + (SENSORCOUNT * 2))

//#define RawDataInt[10]
//#define AnalogData[5]

/* Suche nach I2C-Adressen */
int * rawResult( )
  {
 
  int  resultLength, device;
  
  __u8 rawData[REGENDADDRESS];
  
  int static rawDataInt[REGENDADDRESS];
	  
if ((device = open("/dev/i2c-1", O_RDWR)) < 0)
    {
    perror("open() failed");
    exit (1);
    }

    if (ioctl(device, I2C_SLAVE, PORT) < 0)
      perror("ioctl() I2C_SLAVE failed\n");
    else
      {
	int i=0;
	
      		resultLength = i2c_smbus_read_i2c_block_data(device,REGSTARTADDRESS,REGENDADDRESS,rawData);
	int j=0;
	for (j=0;j <REGENDADDRESS ; j++) {
	 rawDataInt[j] = (int)rawData[j];
	}	
		
			}
   
		
	return rawDataInt;
  }
  
  int * analogResult() {
	  int static analogData[SENSORCOUNT];
          int *rawDataPtr;
	  rawDataPtr=rawResult();
	  int rawData[REGENDADDRESS];
	  int i=0;
	  for (i=0; i<REGENDADDRESS; i++) {

	  rawData[i] = *(rawDataPtr+i);

		}
	  
	  int j = 0;
	  for (j= 0; j < REGENDADDRESS ; j++ )
	  {	  
		int high_byte = rawData[j*2] << 8 ;
		int low_byte = rawData[j*2+1];
		analogData[j] = high_byte + low_byte;
	  }
	  return analogData;
  }
  
  int * digitalResult() {
  
  int static digitaldata[SENSORCOUNT];
  int *analogresultPtr;
  int referenceValue, lowReference, highReference;
  int analogresult[SENSORCOUNT];
  analogresultPtr=analogResult();
  int i=0;
  for(i=0; i<SENSORCOUNT; i++) {
 
	analogresult[i] = *(analogresultPtr+i);

	}


		int j=0;
		lowReference = analogresult[0];  // need to start with some value
		
		highReference = analogresult[0];  // need to start with some value
		
		for ( j=1; j < SENSORCOUNT; j++) {
			if (analogresult[j] < lowReference)
				lowReference = analogresult[j];
			if (analogresult[j] > highReference)
				highReference = analogresult[j];
		}
		referenceValue = lowReference + ((highReference-lowReference)/4);
               // if((highReference-lowReference)>=20) {
				   int k=0;
				   for (k=0; k < SENSORCOUNT; k++) {
					   
                                if (analogresult[k] >= (referenceValue)) {
                                        digitaldata[k]=0;
					}
                                else if (analogresult[k] < (referenceValue)){
                                        digitaldata[k]=1;
					}					
				   }
                
                        return digitaldata;
		//		}
               /* else {
                        digitaldata={0,0,0,0,0};
                        return digitaldata;
						
					  }	 */
  
  
  
  }


                     


int main(void)
  {
  int device,leftspeed,rightspeed,leftpwm,rightpwm;
  unsigned long funcs;
  int numberOfSensor =10;
  int port = 17;
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
while(1){
       int *DigitalResultPtr;
       int DigitalResult[SENSORCOUNT];
  	DigitalResultPtr=digitalResult();
  int x=0;
   for (x=0;x<SENSORCOUNT;x++) {
DigitalResult[x]=*(DigitalResultPtr+x);
printf ("DigitalResult : %d \n", DigitalResult[x] );

}
printf("*********************************************** \n");
}


  return 0;
  }
