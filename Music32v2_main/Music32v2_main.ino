#include "functions.h"
#include "AAText.h"


static unsigned long previousMillis = 0;
const unsigned long interval = 100;  // 1000 milliseconds = 1 second
float percentDone;

void setup() {
  //Serial.begin(115200);
  delay(100);
  calibrateClickwheel();
  timeNow = millis();
  pinMode(menuButtonPin, INPUT);
  pinMode(FFButtonPin, INPUT);
  pinMode(RWButtonPin, INPUT);
  pinMode(PPButtonPin, INPUT);
  pinMode(selectButtonPin, INPUT);
  pinMode(40, OUTPUT);
  analogWrite(20, 64);


  SPI.begin(sckPin, misoPin, mosiPin);
  if (!SD.begin(SDCSPin)) {
    sdFailed = true;
  }
  delay(500);
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(bgColour);
  tft.setCallback(bgColour);  // Switch on color callback for anti-aliased fonts
  tft.setTextWrap(false);

  stext.createSprite(800, 20);
  stext.fillSprite(bgColour);
  stext.setScrollRect(0, 0, 800, 20, bgColour);
  stext.setTextWrap(false);

  ustext.createSprite(220, 20);
  ustext.fillSprite(bgColour);
  ustext.setTextWrap(false);

  graph.createSprite(30, 280);
  graph.fillSprite(bgColour);

  fb.createSprite(240, 320);
  fb.fillSprite(bgColour);
  fb.setTextWrap(false);

  Wire.begin(15, 16);
  if (!codec.begin()) {
    while (1) {}
  }
  codec.setWordLength(16);
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT, I2S_DIN, I2S_MCLK);
  audio.setVolume(13);  // 0...21
  codec.setVolumeOut(vol);

  if (sdFailed == true) {
    tft.loadFont(AA_FONT_LARGE);
    drawSelectedText(xMenuOrigin, 10, "SD fail");
  }
  
  delay(500);
}

void loop() {

  buttonStateCheck();
  touchCalculationDegrees();
  itemIncrement();
  itemChangeActions();
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
  fb.loadFont(AA_FONT_LARGE);
  fb.fillSprite(bgColour);
  for (int i = 0; i <= maxItem; i++) {
    if (i == item) {
      drawSelectedText(xMenuOrigin, yMenuOrigin + (textSeperation * i), menu0[i]);
    } else {
      drawUnselectedText(xMenuOrigin, yMenuOrigin + (textSeperation * i), menu0[i]);
    }
  }
  fb.pushSprite(0, 0);
  fb.unloadFont();
}

void drawMenu1() {

  maxItem = maxfiles - 1;
  fb.loadFont(AA_FONT_SMALL);
  fb.fillSprite(bgColour);
  fileNumber = 0;
  int startItem = (item >= maxWordsDisplayTakeOne) ? item - maxWordsDisplayTakeOne : 0;
  while (fileNumber < maxWordsDisplay) {
    int currentFileIndex = startItem + fileNumber;
    if (startItem != prevStartItem) {
      //tft.fillRect(xMenuOrigin, yMenuOrigin,240,yMenuOrigin + (textSeperationSmall * maxWordsDisplay),bgColour);
      prevStartItem = startItem;
    }

    if (currentFileIndex == item) {

      if (strlen(words[currentFileIndex]) > maxTextLength)  //if the text needs to scroll
      {
        stext.scroll(-1);  // scroll stext 1 pixel right, up/down default is 0
        tcount--;
        if (tcount <= 0) {
          stext.setTextColor(hlColour, bgColour);
          stext.loadFont(AA_FONT_SMALL);
          stext.fillSprite(bgColour);
          stext.setCursor(0, 0);
          stext.print(words[currentFileIndex]);
          stext.print("      ");
          tcount = (stext.getCursorX() - (240 - xMenuOrigin)) + 30;  //by using the cursor position you know where the text ends, even with different fonts. with this find how far the text should scroll
        }
      } else {
        stext.loadFont(AA_FONT_SMALL);
        stext.fillSprite(bgColour);
        stext.setCursor(0,0);
        stext.print(words[currentFileIndex]);
      }
      //stext.pushSprite(xMenuOrigin, yMenuOrigin + (textSeperationSmall * fileNumber));

      stext.pushToSprite(&fb,xMenuOrigin, yMenuOrigin + (textSeperationSmall * fileNumber));
      selectedFileIndex = currentFileIndex;
    } else {
      ustext.setTextColor(ulColour, bgColour);
      ustext.loadFont(AA_FONT_SMALL);
      ustext.fillSprite(bgColour);
      ustext.setCursor(0,0);
      ustext.print(words[currentFileIndex]);
      //ustext.pushSprite(xMenuOrigin, yMenuOrigin + (textSeperationSmall * fileNumber));

      ustext.pushToSprite(&fb,xMenuOrigin, yMenuOrigin + (textSeperationSmall * fileNumber));
    }
    fileNumber++;
  }
  graph.fillSprite(bgColour);
  graph.drawFastVLine(10,0,250,hlColour);
  int gy = map(item,0,maxItem,0,190);
  graph.fillSmoothRoundRect(5,gy,10,60,3,hlColour);
  graph.pushToSprite(&fb,210, 40);
  fb.setTextColor(hlColour, bgColour);
  fb.setCursor(xMenuOrigin,5);
  fb.print("Music");
  fb.drawLine(xMenuOrigin,30,220,30, hlColour);
  fb.pushSprite(0, 0);
  tft.unloadFont();
}

void drawMenu2() {

  if (startPlaying == true) {
    audio.connecttoFS(SD, words[selectedFileIndex]);
    startPlaying = false;
    codec.setVolumeOut(vol);
  }
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    int currentTime = audio.getAudioCurrentTime();
    int totalTime = audio.getAudioFileDuration();
    fb.loadFont(AA_FONT_SMALL);
    fb.fillSprite(bgColour);
    fb.setTextColor(hlColour, bgColour);
    char formatted[8];
    formatTime(totalTime, formatted);
    fb.setCursor(180, 255);
    fb.print(formatted);
    formatTime(currentTime, formatted);
    fb.setCursor(20, 255);
    fb.print(formatted);

    fb.setCursor(5, 280);
    fb.print(words[selectedFileIndex]);
    

    

    if(totalTime != 0)
    {
      percentDone = 100 * currentTime/totalTime;
      percentDone = map(percentDone,0,100,0,190);
    }
    fb.fillSmoothRoundRect(20,230,200,10,5,ulColour);
    fb.fillSmoothCircle(percentDone + 25, 235,10,hlColour);


    
    fb.pushSprite(0, 0);
    fb.pushSprite(0, 0);
    fb.unloadFont();
    previousMillis = currentMillis;   
  }
  
  

  
}


void formatTime(int seconds, char *formattedTime) {
  int hours = seconds / 3600;
  int minutes = (seconds / 60) % 60;
  seconds %= 60;

  if (hours > 0) {
    snprintf(formattedTime, 8, "%02d:%02d:%02d", hours, minutes, seconds);
  } else {
    snprintf(formattedTime, 8, "%02d:%02d", minutes, seconds);
  }
}
