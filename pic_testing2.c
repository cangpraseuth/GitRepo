/* 
 * File:   ADC.c
 * Author: Rachel
 *
 * Created on November 19, 2014, 11:45 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p32xxxx.h>
// char 8 bits
// short 16 bits
// long 32 bits



//short numLEDs;
//short numBytes;
long numBytes = 96; //
long numLEDs = 32; //the number of LEDs in the strip
char *pixels; // the array with the color value for each led

/*
// sets up the ADC
void initadc(void) {

AD1CHS = 0x00070000; //selects the channel RB7/AN7
AD1PCFG = 0xFF7F; // connect as all portb = digital, but rb7 = analog
AD1CON1bits.ON = 1; 	 	// turn ADC on
AD1CON1bits.SAMP = 1; 	 	// begin sampling
AD1CON1bits.DONE = 0; 	 	// clear DONE flag
}


//reads in a value from desired pin
// returns that value
int readadc(void) {
AD1CON1bits.SAMP = 0; 	 	// end sampling, star conversion
while (!AD1CON1bits.DONE); // wait until DONE
AD1CON1bits.SAMP = 1; 	 	// resume sampling
AD1CON1bits.DONE = 0; 	 	// clear DONE flag
return ADC1BUF0; 			// return result
}

*/


// convert separate R,G, B, returns in 32 bit
// GRB color
long Color(char r, char g, char b){
    return ( (g | 0x80) << 16) | //g is first 8 bits
            ((r | 0x80) << 8) | // red is second 8 bits
            (b | 0x80); // blue is third 8 bits
}


//takes in packed 32 bit color value, and led number n
// will set desired LED with desired color
void setPixelColor(short n, long color) {
    if (n<numLEDs) { //check to see if a legal value is being called
        int *p = &pixels[n*3]; //each led expects data in the order of green, red, blue
        *p++ = (color >> 16) | 0x80;
        *p++ = (color >> 9) | 0x80;
        *p++ =  color   | 0x80;
    }
}


//makes all the leds on a strip a single color, input as a 32 bit compact number
void colorWipe(long c) {
    int i;
    for (i=0; i<numLEDs; i++){ // cycles through the entire strand
      setPixelColor(i, c); //sets each the same color
      show(); // sends over spi
    }

}




//sets clock high and sets desired  output
// wait half the time
// set clock low
// wait other half of time
void bitbang(int num, int delay) {
    TRISG = 0x0000;
    num = (0x0002 | num);
    PORTD = num;
    delaymicros(delay);
    num = (0x0001 & num);
    PORTD = num;
    delaymicros(delay);

}

void zeros(void) {
    int i =0;
    while(i<24)
    {
        bitbang(0);
        i++;
    }
}

void delaymicros(int micros) {
if (micros > 1000) { // avoid overflow
    delaymicros(1000);
    delaymicros(micros-1000);
}

else if (micros > 6){
    TMR1 = 0; //reset timer to 0
    T1CONbits.ON =1; //turn timer on
    PR1 = (micros-6)*20; //20 clocks per microsecond
                    // function has overhead of 6us
    IFS0bits.T1IF = 0; //clear overflow flag
    while(!IFS0bits.T1IF); // wait until overflow flag is set
}
}


void show(void) {
    char *ptr = pixels;
    short i = 3*numLEDs;
    short n = 0; 
    while(i--){
        while(n<8){
            output = *ptr >> n
            bitbang(output);
            n++; 
        }
        *ptr++; //advance to next packet
    }
    }


// set for each LED
// send out 24 zeros
// send colors
//send out 24 zeros

void setstrip(void){
    zeros();
    show();
    zeros();
}

void main() {

}