#ifndef functions_h
#define functions_h

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library

#define bgColour 0x0000 //background colour
#define hlColour 0xFFFF //colour of highlighted/current selected item
#define ulColour 0x528a //colour of unselected item
#define textSeperation 40
#define xMenuOrigin 20
#define yMenuOrigin 80

extern TFT_eSPI tft;
extern int item;
extern int menu;
extern int maxItem;
extern int lastOn;
extern char menu0[3][10];

void drawUnselectedText(int x, int y, char text[]);
void drawSelectedText(int x, int y, char text[]);

#endif