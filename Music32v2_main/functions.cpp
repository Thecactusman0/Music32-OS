#include "functions.h"
int item;
int menu;
int maxItem;
int lastOn = 0;
char menu0[3][10] = { "Music", "Link", "Settings" };
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

void drawSelectedText(int x, int y, char text[])
{
  tft.setTextColor(hlColour,bgColour);
  tft.setCursor(x,y);
  tft.print(text);
}

void drawUnselectedText(int x, int y, char text[])
{
  tft.setTextColor(ulColour,bgColour);
  tft.setCursor(x,y);
  tft.print(text);
}