#ifndef touch_h
#define touch_h

#include <Arduino.h>
#define numberOfSegments 6
#define numberOfSamples 5
#define Touchthreshold 7000 //When the the clickwheel is touched
#define offsetDegrees -20
#define touchDelay 1

extern long int initialReadings[numberOfSegments];
extern long int currentReadings[numberOfSegments];
const int pins[numberOfSegments] = { 13, 14, 11, 10, 9, 12 }; //0,1,2,3,4,5
extern float degrees;
extern unsigned long timeNow;


int currentInterpolatedSegment();
bool isDecreasingAboveRate(int currentValue, int previousValue, double rateThreshold, unsigned long deltaTime);
void touchCalculationDegrees();
void calibrateClickwheel();
int applyOffset(int angle, int offset);
#endif