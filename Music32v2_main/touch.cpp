#include "touch.h"
#include "functions.h"

long int initialReadings[numberOfSegments];
long int previousReadings[numberOfSegments];
long int currentReadings[numberOfSegments];
float degrees;
unsigned long timeNow;

bool isDecreasingAboveRate(int currentValue, int previousValue, double rateThreshold, unsigned long deltaTime) 
{
  double rate = (currentValue - previousValue) / (double)deltaTime;
  
  // Check if the rate of decrease is above the threshold
  return rate < -rateThreshold;
}

int currentInterpolatedSegment()
{
  int intSegment;
  if(degrees >= 0 && degrees < 30){intSegment = 0;}
  if(degrees >= 30 && degrees < 60){intSegment = 1;}
  if(degrees >= 60 && degrees < 90){intSegment = 2;}
  if(degrees >= 90 && degrees < 120){intSegment = 3;}
  if(degrees >= 120 && degrees < 150){intSegment = 4;}
  if(degrees >= 150 && degrees < 180){intSegment = 5;}
  if(degrees >= 180 && degrees < 210){intSegment = 6;}
  if(degrees >= 210 && degrees < 240){intSegment = 7;}
  if(degrees >= 240 && degrees < 270){intSegment = 8;}
  if(degrees >= 270 && degrees < 300){intSegment = 9;}
  if(degrees >= 300 && degrees < 330){intSegment = 10;}
  if(degrees >= 330 && degrees < 360){intSegment = 11;}
  if(degrees == -1){intSegment = -1;}
  return intSegment;
}

void touchCalculationDegrees()
{
  int largestIndex = -1;
  int secondLargestIndex = -1;
  
  if(millis()  >= timeNow + touchDelay)
  {
    timeNow += touchDelay;
  
    for (int i = 0; i < numberOfSegments; i++) 
    {
      currentReadings[i] = touchRead(pins[i]) - initialReadings[i];
      //Serial.print(i);
      //Serial.print(":");
      //Serial.println(currentReadings[i]);
   
      if (currentReadings[i] > Touchthreshold) 
      {
        if (largestIndex == -1 || currentReadings[i] > currentReadings[largestIndex]) 
        {
          secondLargestIndex = largestIndex;
          largestIndex = i;
        } else if (secondLargestIndex == -1 || currentReadings[i] > currentReadings[secondLargestIndex]) 
        {
          secondLargestIndex = i;
        }
      }
    
    }
    if (secondLargestIndex == -1 && largestIndex != -1) //only one value
    {
      degrees = largestIndex * 60.0;
      degrees = applyOffset(degrees,offsetDegrees);
    
    }else if (largestIndex != -1 && secondLargestIndex != -1)
    { 

        int sum = currentReadings[largestIndex]+currentReadings[secondLargestIndex];
        sum = sum/1000;
        int sum2 = currentReadings[largestIndex]/1000;
        degrees = ((float)sum2/(float)sum)*60.0;
        if(largestIndex < secondLargestIndex || largestIndex == 5 && secondLargestIndex == 0)
        {
          int i = degrees - 30;
          i = i*2;
          degrees = degrees - i;
        }
        if(secondLargestIndex == 5 && largestIndex == 0)
        {
          degrees = 30 - degrees;
          degrees = degrees + 30;  
        }
        if (largestIndex > secondLargestIndex) 
        {
          degrees = degrees+(secondLargestIndex*60);  
        } else 
        {
          degrees = degrees+(largestIndex*60);    
        }
        if(secondLargestIndex == 5 && largestIndex == 0 || secondLargestIndex == 0 && largestIndex == 5)
        {
          degrees = degrees + 300; 
        }
          degrees = applyOffset(degrees,offsetDegrees);
       
    }else
    {
      degrees = -1;
    }
  }
  //Serial.print("Degrees: ");
  //Serial.println(degrees);

}

void calibrateClickwheel()// doesnt quite work yet
{
  for (int i = 0; i < numberOfSegments; i++) 
  {
    for(int a = 0; a < numberOfSamples; a++)
    {
      initialReadings[i] = initialReadings[i] + touchRead(pins[i]); //go through and add all the samples together
    }
    initialReadings[i] = (initialReadings[i]/numberOfSamples)-1000; //Average it
  }
}

int applyOffset(int angle, int offset) 
{
    int result = (angle + offset) % 360;
    
    // Ensure the result is positive
    if (result < 0) 
    {
        result += 360;
    }
    
    return result;
}