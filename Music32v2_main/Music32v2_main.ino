#include "functions.h"
#include "AAText.h"


static unsigned long previousMillis = 0;
const unsigned long interval = 1000; // 1000 milliseconds = 1 second

void setup() 
{
  //Serial.begin(115200);
  delay(100);
  calibrateClickwheel();
  previousTime = millis(); // Initialize the previous time
  pinMode(menuButtonPin,INPUT);
  pinMode(FFButtonPin,INPUT);
  pinMode(RWButtonPin,INPUT);
  pinMode(PPButtonPin,INPUT);
  pinMode(selectButtonPin,INPUT);
  pinMode(40,OUTPUT); 
  analogWrite(20,64);
  

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
  tft.setTextWrap(false);

  Wire.begin(15,16);
  if (!codec.begin()) 
  {
    while (1) {}
  }
  codec.setWordLength(16);
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT,I2S_DIN, I2S_MCLK);
  audio.setVolume(5); // 0...21
  //audio.connecttoFS(SD, "last.m4a");

  //rtc.begin();  //Initialize RTC module
  //rtc.setTime(20,37,0); // 24H mode, ex. 6:54:00
  //rtc.setDate(1,11,9,2023); // 0 for Sunday, ex. Saturday, 16.5.2020. setDate(weekday, day, month, yr);


  if(sdFailed == true)
  {
    tft.loadFont(AA_FONT_LARGE);
    drawSelectedText(xMenuOrigin,10,"SD fail");
  }
 readSd();
 delay(500);
}

void loop() 
{

  buttonStateCheck();
  touchCalculationDegrees();
  itemIncrement();
  drawMenu(); 
  audio.loop();

  
  
  
}

void drawMenu() {
  //if (drawn == 0) {
    //drawn = 1;
    switch (menu) {
      case 0:
        drawMenu0();
        break;
      case 1:
        drawMenu1();
        break;
      case 2:
        drawMenu2();
        break;
    }
  //}
}

void drawMenu0() {
  maxItem = 2;
  tft.loadFont(AA_FONT_LARGE);
  for (int i = 0; i <= maxItem; i++) {
    if (i == item) {
      drawSelectedText(xMenuOrigin, yMenuOrigin + (textSeperation * i), menu0[i]);
    } else {
      drawUnselectedText(xMenuOrigin, yMenuOrigin + (textSeperation * i), menu0[i]);
    }
  }
  tft.unloadFont();
}

void drawMenu1() 
{
  
  maxItem = maxfiles - 1;
  tft.loadFont(AA_FONT_SMALL);
  fileNumber = 0;
  int startItem = (item >= maxWordsDisplayTakeOne) ? item - maxWordsDisplayTakeOne : 0;
  while (fileNumber < maxWordsDisplay) {
    int currentFileIndex = startItem + fileNumber;
    if (startItem != prevStartItem) {
      tft.fillRect(xMenuOrigin, yMenuOrigin,240,yMenuOrigin + (textSeperationSmall * maxWordsDisplay),bgColour);
      prevStartItem = startItem;
    }
    tft.setCursor(xMenuOrigin, yMenuOrigin + (textSeperationSmall * fileNumber));
    if (currentFileIndex == item) {
      tft.setTextColor(hlColour, bgColour);
      tft.println(words[currentFileIndex]);
      selectedFileIndex = currentFileIndex;
    } else {
      tft.setTextColor(ulColour, bgColour);
      tft.println(words[currentFileIndex]);
    }
    fileNumber++;
  }
  tft.unloadFont();
}

void drawMenu2() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    int currentTime = audio.getAudioCurrentTime();
    tft.loadFont(AA_FONT_SMALL);
    tft.fillRect(20,280,220,20,bgColour);
    tft.fillRect(20,280,220,20,bgColour);
    tft.setTextColor(hlColour, bgColour);
    char formatted[8];
    formatTime(audio.getAudioFileDuration(), formatted);
    tft.setCursor(160, 280);
    tft.print(formatted);
    formatTime(currentTime, formatted);
    tft.setCursor(20, 280);
    tft.print(formatted);
    tft.setCursor(5, 260);
    tft.print(words[selectedFileIndex]);
    tft.unloadFont();
    previousMillis = currentMillis;
  }

  if(startPlaying == true)
  {
    audio.connecttoFS(SD,words[selectedFileIndex]);
    startPlaying = false;
  }

  
  
}

void clearScreen() 
{
  tft.fillScreen(bgColour);
}

void formatTime(int seconds, char* formattedTime) 
{
    int hours = seconds / 3600;
    int minutes = (seconds / 60) % 60;
    seconds %= 60;
    
    if (hours > 0) {
        snprintf(formattedTime, 8, "%02d:%02d:%02d", hours, minutes, seconds);
    } else {
        snprintf(formattedTime, 8, "%02d:%02d", minutes, seconds);
    }
}
