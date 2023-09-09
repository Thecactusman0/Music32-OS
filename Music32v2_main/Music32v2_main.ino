#include "functions.h"
#include "AAText.h"
#include "audio.h"
#include "ES8327.h"

ES8327 codec(Wire,8,0x18);//wire object,hp_int, address


void setup() 
{
  auto config = i2s.defaultConfig(TX_MODE);
  config.pin_mck = 46; 
  config.pin_bck = 45; 
  config.pin_data = 48;
  config.pin_ws = 47; 
  i2s.begin(config);

  SPI.begin(37,42,36); 
  player.begin(0,false);
  player.setBufferSize(1024);
  
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
  calibrateClickwheel();
  previousTime = millis(); // Initialize the previous time
  pinMode(menuButtonPin,INPUT);
  pinMode(FFButtonPin,INPUT);
  pinMode(RWButtonPin,INPUT);
  pinMode(PPButtonPin,INPUT);
  pinMode(selectButtonPin,INPUT);
  pinMode(40,OUTPUT); //Set 25% brightness for filming
  analogWrite(40,64);
}

void loop() 
{
 buttonStateCheck();
 menuChangeCheck();
 touchCalculationDegrees();
 itemIncrement();
 drawMenu();
 player.copy();
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
      player.play();
      tft.setCursor(10,10);
      tft.print(source.toStr());
      if(FFPressed)
      {
        player.next();
      }
    break;
  }
  drawn = 1;
}
}

