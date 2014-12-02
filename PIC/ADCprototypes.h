/* 
 * File:   ADCprototypes.h
 * Author: Rachel
 *
 * Created on December 1, 2014, 1:56 PM
 */
void initadc(void);
long Color(char r, char g, char b);
void setPixelColor(short n, long color);
void colorWipe(long c);
void bitbang(int num);
void zeros(void);
void delaymicros(int micros);
void show(void);
void setstrip(void);
void main(void);
