/******************************* *
*Ultra Sonic Raning module Pin VCC
*should * be connected to 5V power.
******************************/
#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>
#define Trig 2
#define Echo 1

void ultraInit(void) {
printf("inside ultraInit method! \n");
    pinMode(Echo, INPUT);
	pinMode(Trig, OUTPUT);
}
float disMeasure(void) {
printf("inside disMeasure method! \n");
	struct timeval tv1;
	struct timeval tv2;
	long time1, time2;
    	float dis;
printf("after variable declaration \n");
	digitalWrite(Trig, LOW);
	delayMicroseconds(2);
	digitalWrite(Trig, 1);
	delayMicroseconds(10);
	digitalWrite(Trig, 0);
	
	printf("digitalRead(Echo) initial Value: %d\n", digitalRead(Echo));

	while(!(digitalRead(Echo) == 1))
{
        printf("digitalRead(Echo) : %d\n", digitalRead(Echo));
		gettimeofday(&tv1, NULL);
        break;

}
	while(!(digitalRead(Echo) == 0)) 
{

	printf("echo and trigger value changed! \n");
	gettimeofday(&tv2, NULL); //get current time
	break;
}
	time1 = tv1.tv_sec + tv1.tv_usec; //microsecond time
	time2 = tv2.tv_sec + tv2.tv_usec;

	//time1 = tv1.tv_sec * 1000000 + tv1.tv_usec; //microsecond time
	//time2 = tv2.tv_sec * 1000000 + tv2.tv_usec;
	printf("time1 :%0.2f\n ",time1);
	printf("time2 :%0.2f\n",time2);
	dis = (float)(time2 - time1) / 1000000 * 34000 / 2; //calculate distance
	printf("dis :%0.2f\n",dis);
	return dis;
}
int main(void) {
	float dis;
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1;
	}
	ultraInit();
	printf("inside main method after ultraInit method call ! \n");
	while(1){
		dis = disMeasure();
		printf("%0.2f cm\n\n",dis);
		delay(300);
	}
	return 0;
}
