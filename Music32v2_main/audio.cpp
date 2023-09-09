#include "audio.h"

const char *startFilePath="/";
const char* ext="mp3";

//SdSpiConfig sdcfg(PIN_AUDIO_KIT_SD_CARD_CS, DEDICATED_SPI, SD_SCK_MHZ(10));
//AudioSourceSDFAT source(startFilePat,ext,sdcfg);
AudioSourceSD source(startFilePath,ext,2);
I2SStream i2s;
MP3DecoderHelix decoder;
AudioPlayer player(source, i2s, decoder);

