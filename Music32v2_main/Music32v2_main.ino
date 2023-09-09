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
  pinMode(40,OUTPUT);
  analogWrite(40,64);
}

void loop() 
{
 touchCalculationDegrees();
 itemIncrement();
 drawMenu();
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

