#ifndef functions_h
#define functions_h

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include "touch.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "audio.h"
#include "AAText.h"

#define bgColour 0x0000 //background colour
#define hlColour 0xFFFF //colour of highlighted/current selected item
#define ulColour 0x528a //colour of unselected item
#define textSeperation 40
#define textSeperationSmall 20
#define xMenuOrigin 20
#define yMenuOrigin 40
#define menuButtonPin 0
#define FFButtonPin 5
#define RWButtonPin 3
#define PPButtonPin 6
#define selectButtonPin 7
#define SDCSPin 2
#define misoPin 42       // Custom MISO pin
#define mosiPin 36       // Custom MOSI pin
#define sckPin 37        // Custom SCK pin

#define maxWords 100    // Maximum number of words
#define maxWordsDisplay 13 //max amount of words that can be displayed on screen
#define maxWordLength 100 // Maximum length of each word
#define maxTextLength 32

extern TFT_eSPI tft;
extern TFT_eSprite stext;
extern TFT_eSprite ustext;
extern TFT_eSprite graph;
extern TFT_eSprite fb;
extern Audio audio;
extern fs::SDFS SD;
extern ES8327 codec;
extern File root;
extern File file;

extern int maxWordsDisplayTakeOne;
extern int selectedFileIndex;
extern int fileNumber;
extern bool sdFailed;
extern char words[maxWords][maxWordLength]; // Array to store words
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
extern const char desiredCharacterSets[][maxWordLength];
extern const int numSets;
extern const int max_display_chars; // Maximum characters to display on the screen before scrolling
extern int maxfiles;
extern int prevStartItem;
extern bool startPlaying;
extern int vol;
extern bool buzz;
extern int tcount;
extern int startIndex;
extern char currentDir[50];

void drawUnselectedText(int x, int y, char text[]);
void drawSelectedText(int x, int y, char text[]);
void itemIncrement();
void buttonStateCheck();
void menuChangeCheck();
void readSd();
bool containsDesiredCharacters(const char* word);
void itemChangeActions();

#endif