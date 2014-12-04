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
        pixels[n] = color;
    }
}


//makes all the leds on a strip a single color, input as a 32 bit compact number
void colorWipe(long c) {
    int i;
    for (i=0; i<numLEDs; i++){ // cycles through the entire strand
      setPixelColor(i, c); //sets each the same color
      //show(); // sends over spi
    }

}




//sets clock high and sets desired  output
// wait half the time
// set clock low
// wait other half of time
void bitbang(int num) {
    TRISD = 0x0000;
    num = (0x0002 | num);
    PORTD = num;
    delaymicros(1);
    num = (0x0001 & num);
    PORTD = num;
    delaymicros(1);

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
    //char *ptr = pixels;
    short i = 0;
    short n = 32;
    int output;
    while(i<numLEDs){
        while(n>0){
            output = pixels[i];
            output = output >> n;
            bitbang(output);
            n--;
        }
        i++; //advance to next packet
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



void main(void) {
   //zeros();
   //long red = Color(0,127,0);
   int color = 0xFFF0F0;
   //colorWipe(color);
    //short i = 0;
    short n = 24;
    int output;
    int i = 0;
    while(i<numLEDs-1){
        while(n>0){
            output = color;
            output = output >> (n-1);
            bitbang(output);
            n--;
        }
        i++;
    }
     zeros();
    }
