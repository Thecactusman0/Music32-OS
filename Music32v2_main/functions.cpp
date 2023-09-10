#include "functions.h"
int item;
int menu;
int maxItem;
int lastOn = 0;
char menu0[3][10] = { "Music", "Link", "Settings" };

bool menuPressed; //stop froms button being registered as pressed over and over when held
bool FFPressed;
bool RWPressed;
bool PPPressed;
bool selectPressed;
bool refreshMenu;
bool refreshSelect;
bool drawn;

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

void menuChangeCheck()
{
  if(menuPressed && selectPressed == false)
  {
    switch(menu)
    {
      case 1:
      menu = 0; //If on music screen and menu pressed go to homescreen
      item = 0;
      drawn = 0;
      break;
    }
    
  }

  if(selectPressed && menuPressed == false)
  {
    switch(menu)
    {
      case 0:
      switch(item)
      {
        case 0:
        menu = 1; //if select pressed on music item go to music menu
        item = 0;
        drawn = 0;
        break;
        //Add more homescreen menus here
      }
      break;
    }
    
  }

}

void buttonStateCheck()
{
  if(digitalRead(menuButtonPin) == 0)
  {
    menuPressed = true;
    if(refreshMenu == false)
    {
      tft.fillScreen(bgColour);
      refreshMenu = true;
      drawn = 0;
    }
  }else
  {
    menuPressed = false;
    refreshMenu = false;
  }
  
  if(digitalRead(FFButtonPin) == 0)
  {
    FFPressed = true;
    drawn = 0;
  }else
  {
    FFPressed = false;
  }

  if(digitalRead(RWButtonPin) == 0)
  {
    RWPressed = true;

  }else
  {
    RWPressed = false;
  }

  if(digitalRead(PPButtonPin) == 0)
  {
    PPPressed = true;

  }else
  {
    PPPressed = false;
  }

  if(digitalRead(selectButtonPin) == 0)
  {
    selectPressed = true;
    if(refreshSelect == false)
    {
      drawn = 0;
      tft.fillScreen(bgColour);
      refreshSelect = true;
    }
  }else
  {
    selectPressed = false;
    refreshSelect = false;
  }
  
  
  /*tft.setCursor(10,20);
  tft.print(menuPressed);
  tft.setCursor(10,40);
  tft.print(RWPressed);
  tft.setCursor(10,60);
  tft.print(FFPressed);
  tft.setCursor(30,20);
  tft.print(PPPressed);
  tft.setCursor(30,40);
  tft.print(selectPressed);*/

  
}

void itemIncrement()
{
  
  if(currentInterpolatedSegment() != -1) //If touch wheel is pressed
  {
    if(lastOn == -1) 
    {
      lastOn = currentInterpolatedSegment(); //Reset lastOn variable to prevent incrementing on first touch
      drawn = 0;
    }

    if(currentInterpolatedSegment() == 8 && lastOn == 0) {item--; lastOn = currentInterpolatedSegment(); //Gigantic block of if statements to stop incrementing wrong way when crossing from segment 0-11
    }else if(currentInterpolatedSegment() == 8 && lastOn == 1) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 8 && lastOn == 2) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 8 && lastOn == 3) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 8 && lastOn == 4) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 9 && lastOn == 0) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 9 && lastOn == 1) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 9 && lastOn == 2) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 9 && lastOn == 3) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 9 && lastOn == 4) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 10 && lastOn == 0) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 10 && lastOn == 1) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 10 && lastOn == 2) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 10 && lastOn == 3) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 10 && lastOn == 4) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 11 && lastOn == 0) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 11 && lastOn == 1) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 11 && lastOn == 2) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 11 && lastOn == 3) {item--; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 11 && lastOn == 4) {item--; lastOn = currentInterpolatedSegment();

    }else if(currentInterpolatedSegment() == 0 && lastOn == 8) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 1 && lastOn == 8) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 2 && lastOn == 8) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 3 && lastOn == 8) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 4 && lastOn == 8) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 0 && lastOn == 9) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 1 && lastOn == 9) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 2 && lastOn == 9) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 3 && lastOn == 9) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 4 && lastOn == 9) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 0 && lastOn == 10) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 1 && lastOn == 10) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 2 && lastOn == 10) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 3 && lastOn == 10) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 4 && lastOn == 10) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 0 && lastOn == 11) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 1 && lastOn == 11) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 2 && lastOn == 11) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 3 && lastOn == 11) {item++; lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 4 && lastOn == 11) {item++; lastOn = currentInterpolatedSegment();

    }else
    {
      if (currentInterpolatedSegment() > lastOn) //Clockwise
      {
        item++;
        lastOn = currentInterpolatedSegment();
        drawn = 0;
      } else if (currentInterpolatedSegment() < lastOn) //Anticlockwise
      {
        item--;
        lastOn = currentInterpolatedSegment();
        drawn = 0;
      }
    }
  }else
  {
    lastOn = -1;
  }

  // Update last position for the next loop iteration
  
  if (item > maxItem) {
    item = maxItem -1;
  }

  if (item < 0) {
    item = 0;
  }
  /*tft.setTextColor(ulColour,bgColour);
  tft.setCursor(10,10);
  tft.print(currentInterpolatedSegment());
  tft.setCursor(10,20);
  tft.print(item);
  tft.setCursor(10,30);
  tft.print(lastOn);
  tft.setCursor(10,40);
  tft.print(degrees);*/
}

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