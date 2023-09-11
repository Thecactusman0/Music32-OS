#include "functions.h"
#include "AAText.h"
#include "audio.h"
#define maxFileDisplay 10
ES8327 codec(Wire,8,0x18);//wire object,hp_int, address


File root;
File file;
int fileNumber;
int selectedFileNumber;
bool sdFailed;


void setup() 
{

  delay(100);
  calibrateClickwheel();
  previousTime = millis(); // Initialize the previous time
  pinMode(menuButtonPin,INPUT);
  pinMode(FFButtonPin,INPUT);
  pinMode(RWButtonPin,INPUT);
  pinMode(PPButtonPin,INPUT);
  pinMode(selectButtonPin,INPUT);
  pinMode(40,OUTPUT); //Set 25% brightness for filming
  analogWrite(40,64);
  

  SPI.begin(sckPin,misoPin,mosiPin);
  if (!SD.begin(SDCSPin)) 
  {
  sdFailed = true;
  }
  delay(500);
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(bgColour);
  tft.setCallback(bgColour); // Switch on color callback for anti-aliased fonts
  
  Wire.begin(15,16);
  if (!codec.begin()) 
  {
    while (1) {}
  }
  codec.setWordLength(16);
  rtc.begin();  //Initialize RTC module
  rtc.setTime(20,37,0); // 24H mode, ex. 6:54:00
  rtc.setDate(1,11,9,2023); // 0 for Sunday, ex. Saturday, 16.5.2020. setDate(weekday, day, month, yr);


  if(sdFailed == true)
  {
    tft.loadFont(AA_FONT_LARGE);
    drawSelectedText(xMenuOrigin,10,"SD fail");
  }
 
}

void loop() 
{
  buttonStateCheck();
  menuChangeCheck();
  touchCalculationDegrees();
  itemIncrement();
  drawMenu(); 

}




void drawMenu() 
{
  if(drawn == 0)
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
    case 1:
      maxItem = maxFileDisplay;
      tft.loadFont(AA_FONT_SMALL);
      root = SD.open("/");
      file = root.openNextFile();
      tft.setTextColor(hlColour,bgColour);
      fileNumber = 0;
      while(fileNumber < maxFileDisplay)
      {
          if(!file)
          {
            maxItem = fileNumber;
            break;
          }

          tft.setCursor(xMenuOrigin,yMenuOrigin+(textSeperationSmall*fileNumber));
          if(fileNumber == item)
          {
            tft.setTextColor(hlColour,bgColour);
            tft.println(file.name());
            selectedFileNumber = fileNumber;
          }else
          {
            tft.setTextColor(ulColour,bgColour);
            tft.println(file.name());
          }
          file = root.openNextFile();
          fileNumber++;
      }
      
      
      //file.close();
      
      tft.unloadFont(); // Remove the font to recover memory used
      
    break; 
    }
  }
  drawn = 1; 
}


