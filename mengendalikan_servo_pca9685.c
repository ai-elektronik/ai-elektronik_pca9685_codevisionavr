#include <mega328p.h>
#include <stdio.h>
#include <pca9685.c>
void main(void){
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

twiinit();
pwmbegin();
setfrekuensi(50);

//setpin(0,409,0);
//setpin(1,212,0);
sudutservo(0,90);
sudutservo(1,45);
sudutservo(2,135);
sudutservo(3,32.2);
while (1){

}
}
