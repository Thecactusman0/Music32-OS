#include "functions.h"
int item;
int menu;
int maxItem;
int lastOn = 0;
char menu0[3][10] = { "Music", "Link", "Settings" };
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

void itemIncrement()
{
  
  if(currentInterpolatedSegment() != -1) //If touch wheel is pressed
  {
    if(lastOn == -1) 
    {
      lastOn = currentInterpolatedSegment(); //Reset lastOn variable to prevent incrementing on first touch
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
      } else if (currentInterpolatedSegment() < lastOn) //Anticlockwise
      {
        item--;
        lastOn = currentInterpolatedSegment();
      }
    }
  }else
  {
    lastOn = -1;
  }

  // Update last position for the next loop iteration
  
  if (item > maxItem) {
    item = maxItem;
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