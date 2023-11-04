


#ifndef SIGN_H
#define SIGN_H


#include <Adafruit_NeoPixel.h>

enum pattern {PAT_INVALID=-1, PAT_OFF=0, PAT_FLOW, PAT_FADE};

extern Adafruit_NeoPixel sign_leds;

extern enum pattern sign_pattern;

#endif
