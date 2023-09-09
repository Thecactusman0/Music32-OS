#ifndef functions_h
#define functions_h

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include "touch.h"


#define bgColour 0x0000 //background colour
#define hlColour 0xFFFF //colour of highlighted/current selected item
#define ulColour 0x528a //colour of unselected item
#define textSeperation 40
#define textSeperationSmall 20
#define xMenuOrigin 20
#define yMenuOrigin 80
#define menuButtonPin 0
#define FFButtonPin 5
#define RWButtonPin 3
#define PPButtonPin 6
#define selectButtonPin 7
#define SDCSPin 2
#define misoPin 42       // Custom MISO pin
#define mosiPin 36       // Custom MOSI pin
#define sckPin 37        // Custom SCK pin

extern TFT_eSPI tft;
extern int item;
extern int menu;
extern int maxItem;
extern int lastOn;
extern char menu0[3][10];
extern bool menuPressed;
extern bool FFPressed;
extern bool RWPressed;
extern bool PPPressed;
extern bool selectPressed;
extern bool drawn;
void drawUnselectedText(int x, int y, char text[]);
void drawSelectedText(int x, int y, char text[]);
void itemIncrement();
void buttonStateCheck();
void menuChangeCheck();

#endif