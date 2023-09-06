#include "functions.h"
#include "touch.h"
#include "AAText.h"





void setup() 
{
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(bgColour);
  tft.setCallback(bgColour); // Switch on color callback for anti-aliased fonts
  delay(1000);
  calibrateClickwheel();
  previousTime = millis(); // Initialize the previous time
}

void loop() 
{
 touchCalculationDegrees();
 itemIncrement();
 drawMenu();
 delay(100); //this will need to go at some point and be replaced, needed for touch to work reliably
}

void itemIncrement()
{
  
  if(currentInterpolatedSegment() != -1)
  {
    if(currentInterpolatedSegment() == 0 && lastOn == 11)
    {
      item++;
      //tft.fillScreen(TFT_BLACK);
      //tft.fillRect(20,80,200,200,TFT_BLACK);
      lastOn = currentInterpolatedSegment();
    }else if(currentInterpolatedSegment() == 11 && lastOn == 0)
    {
      item--;
      //tft.fillScreen(TFT_BLACK);
      //tft.fillRect(20,80,200,200,TFT_BLACK);
      lastOn = currentInterpolatedSegment();
    }else
    {
      if (currentInterpolatedSegment() > lastOn) 
      {
        // Clockwise rotation
        item++;
        //tft.fillScreen(TFT_BLACK);
        //tft.fillRect(20,80,200,200,TFT_BLACK);
        lastOn = currentInterpolatedSegment();
      } else if (currentInterpolatedSegment() < lastOn) 
      {
        // Anti-clockwise rotation
        item--;
        //tft.fillScreen(TFT_BLACK);
        //tft.fillRect(20,80,200,200,TFT_BLACK);
        lastOn = currentInterpolatedSegment();
      }
    }
  }

  // Update last position for the next loop iteration
  
  if (item > maxItem) {
    item = maxItem;
  }

  if (item < 0) {
    item = 0;
  }
  tft.setTextColor(ulColour,bgColour);
  tft.setCursor(10,10);
  tft.print(currentInterpolatedSegment());
  tft.setCursor(10,20);
  tft.print(item);
  tft.setCursor(10,30);
  tft.print(lastOn);
  tft.setCursor(10,40);
  tft.print(degrees);
}

void drawMenu() 
{
  switch (menu) {
    case 0:
      maxItem = 2;
      tft.loadFont(AA_FONT_LARGE);
      //drawSelectedText(xMenuOrigin,yMenuOrigin+(textSeperation),menu0[1]);
      for(int i = 0; i <= maxItem; i++)
      {
        if(i == item)
        {
          drawSelectedText(xMenuOrigin,yMenuOrigin+(textSeperation*i),menu0[i]);

        }else
        {
          drawUnselectedText(xMenuOrigin,yMenuOrigin+(textSeperation*i),menu0[i]);
        }
      }
      tft.unloadFont(); // Remove the font to recover memory used
      break;
  }
}

