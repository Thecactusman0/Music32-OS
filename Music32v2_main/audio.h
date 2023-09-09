


#ifndef audio_h
#define audio_h

#include <Arduino.h>

#include "AudioTools.h"
#include "AudioLibs/AudioSourceSD.h"
#include "AudioCodecs/CodecMP3Helix.h"


extern I2SStream i2s;
extern AudioPlayer player;
extern AudioSourceSD source;



#endif