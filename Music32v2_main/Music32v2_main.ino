#include "functions.h"
#include "AAText.h"

#define maxFileDisplay 10


int prevStartItem = 0;

File root;
File file;


const char desiredCharacterSets[][maxWordLength] = { //desired file extensions that you want to sort for
  ".mp3",   
  ".m4a",   
  ".wav"    
};
const int numSets = sizeof(desiredCharacterSets) / maxWordLength;
const int max_display_chars = 24; // Maximum characters to display on the screen before scrolling
int maxfiles;

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
  menuChangeCheck();
  touchCalculationDegrees();
  itemIncrement();
  drawMenu(); 
  audio.loop();


    //audio.connecttoFS(SD,words[selectedFileIndex]);

}


void readSd()
{
  root = SD.open("/");
  file = root.openNextFile();
  int i = 0;
  while (i < maxWords)
  {

    if (!file)
    {
      maxfiles = i;
      break;
    }
    const char* constFileName = file.name(); // Get the const char pointer
    if(file.isDirectory())
    {
      // Check if the file name length is below the specified limit
      if (strlen(constFileName)+1 <= maxWordLength)
      {
        strcpy(words[i], "/");
        strcat(words[i], constFileName);
        i++;
      }
    }
    else if (containsDesiredCharacters(constFileName))
    {
      // Check if the file name length is below the specified limit
      if (strlen(constFileName) <= maxWordLength)
      {
        strcpy(words[i], constFileName);
        i++;
      }
    }
    file = root.openNextFile();

    
  }
  if(i == maxWords)
  {
    maxfiles = i;
  }
}



bool containsDesiredCharacters(const char* word) {

  if (word[0] == '.') { //filter out the words with start with .
    return false;
  }

  for (int i = 0; i < numSets; i++) {
    const char* desiredCharacters = desiredCharacterSets[i];
    int charIndex = 0;

    for (int j = 0; word[j] != '\0'; j++) {
      if (word[j] == desiredCharacters[charIndex]) {
        charIndex++;

        // If the entire desired character set is found in order, accept the word
        if (desiredCharacters[charIndex] == '\0') {
          return true;
        }
      }
    }
  }

  // If none of the specified character sets are found in the word, reject the word
  return false;
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

maxItem = maxfiles - 1; // max amount of items that can be scrolled to
tft.loadFont(AA_FONT_SMALL);
fileNumber = 0; // value to increment to print all the file names


int startItem = (item >= maxWordsDisplayTakeOne) ? item - maxWordsDisplayTakeOne : 0;


while (fileNumber < maxWordsDisplay) // while we can still display it
{
 
    int currentFileIndex = startItem + fileNumber ; //the file that is currently being drawn
    
    
    // Check if startItem has changed and clear the previous text if it has
    if (startItem != prevStartItem) {
      tft.fillScreen(TFT_BLACK);
      prevStartItem = startItem;
    }

    tft.setCursor(xMenuOrigin, yMenuOrigin + (textSeperationSmall * fileNumber)); //set the cursor to a multiple of the file number we are drawing
    if (currentFileIndex == item)
    {
        tft.setTextColor(hlColour, bgColour);
        tft.println(words[currentFileIndex]);
        selectedFileIndex = currentFileIndex;
    }
    else
    {
        tft.setTextColor(ulColour, bgColour);
        tft.println(words[currentFileIndex]);
    }



    fileNumber++;
}

      tft.unloadFont(); // Remove the font to recover memory used
      
    break; 
    }
  }
  drawn = 1; 
}


