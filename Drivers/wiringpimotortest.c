#include <wiringPi.h>
#include <stdio.h>

int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	pinMode(21, OUTPUT);
	pinMode(22, OUTPUT);

while(1) {
		digitalWrite(21, LOW);
		digitalWrite(22, LOW);
}
}