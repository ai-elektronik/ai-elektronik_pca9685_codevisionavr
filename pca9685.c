#include <twi2.c>
#include <math.h>
#include <delay.h>

#define pcawrite 0x80
#define pcaread	 0x81

void pwmbegin(){
twistart();
twiwrite(pcawrite);
twiwrite(0x00);
twiwrite(0x00);
twistop();

}


void setfrekuensi(float frekuensi){
unsigned char nilai_prescaler,prescale;
unsigned char mode_lama,mode_baru;
nilai_prescaler=floor((float)(25000000)/(4096*frekuensi))-1;

twistart();
twiwrite(pcawrite);
twiwrite(0x00);
twiwrite(pcaread);
twiwrite(0x00);
mode_lama=twiread(0);
twistop();

mode_baru=(mode_lama&0x7f)|0x10;

twistart();
twiwrite(pcawrite);
twiwrite(0x00);
twiwrite(mode_baru);
twistop();

twistart();
twiwrite(pcawrite);
twiwrite(0xfe);
twiwrite(nilai_prescaler);
twistop();

twistart();
twiwrite(pcawrite);
twiwrite(0x00);
twiwrite(mode_lama);
twistop();

delay_ms(50);

twistart();
twiwrite(pcawrite);
twiwrite(0x00);
twiwrite(mode_lama | 0xa1);
twistop();
}

void setpwm(unsigned char pin_ke,unsigned int on,unsigned int off){
twistart();
twiwrite(pcawrite);
twiwrite(6+pin_ke*4);
twiwrite(on);
twiwrite(on>>8);
twiwrite(off);
twiwrite(off>>8);
twistop();
}

void setpin(unsigned char pin_ke,unsigned int nilai,unsigned char invert){
nilai = min(nilai,4095);
if(invert==1){
    if      (nilai==0)   setpwm(pin_ke,4096,0);
    else if (nilai==4095)setpwm(pin_ke,0,4096);
    else                 setpwm(pin_ke,0,4095-nilai);
}
else{
    if      (nilai==4095)setpwm(pin_ke,4096,0);
    else if (nilai==0)   setpwm(pin_ke,0,4096);
    else                 setpwm(pin_ke,0,nilai);
}
}

void sudutservo(unsigned char pin_ke,float sudut){
unsigned int lebar_pulsa;
if(sudut<0)sudut=0;
else if(sudut>180)sudut=180;
lebar_pulsa=204.8+(204.8*sudut/180);
setpin(pin_ke,lebar_pulsa,0);
}