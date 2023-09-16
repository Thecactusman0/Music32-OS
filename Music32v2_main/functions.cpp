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
bool refreshFF;
bool refreshRW;
bool refreshPP;
bool drawn;
bool startPlaying;
int fileNumber;
bool sdFailed;
int selectedFileIndex;
int vol;
const char desiredCharacterSets[][maxWordLength] = { //desired file extensions that you want to sort for
  ".mp3",   
  ".m4a",   
  ".wav"    
};
const int numSets = sizeof(desiredCharacterSets) / maxWordLength;
const int max_display_chars = 24; // Maximum characters to display on the screen before scrolling
int maxfiles;
char words[maxWords][maxWordLength]; // Array to store words
int maxWordsDisplayTakeOne = maxWordsDisplay - 1;
int prevStartItem = 0;

File root;
File file;

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
PCF85063A rtc; 
Audio audio;
ES8327 codec(Wire,8,0x18);//wire object,hp_int, address




void buttonStateCheck()
{
  if(digitalRead(menuButtonPin) == 0)
  {
    menuPressed = true;
    if(refreshMenu == false)
    {
      tft.fillScreen(bgColour);
      refreshMenu = true;
      //drawn = 0;
      switch(menu)
    {
      case 1:
      menu = 0; //If on music screen and menu pressed go to homescreen
      item = 0;
      drawn = 0;
      break;
      case 2:
      audio.stopSong();
      delay(500);
      tft.fillScreen(bgColour);
      menu = 1; 
      item = 0;
      drawn = 0;
      tft.fillScreen(bgColour);
      break;
    }
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
    if(refreshFF == false)
    {
      vol++;
      codec.setVolumeOut(vol);
      refreshFF = true;

    }
  }else
  {
    FFPressed = false;
    refreshFF = false;
  }

  if(digitalRead(RWButtonPin) == 0)
  {
    RWPressed = true;
   if(refreshRW == false)
    {
      vol--;
      codec.setVolumeOut(vol);
      refreshRW = true;

    }
  }else
  {
    RWPressed = false;
    refreshRW = false;
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
      //drawn = 0;
      tft.fillScreen(bgColour);
      refreshSelect = true;
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
      case 1:
      menu = 2; 
      item = 0;
      drawn = 0;
      startPlaying = true;
      break;
    }
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
    item = maxItem ;
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

bool containsDesiredCharacters(const char* word) 
{

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