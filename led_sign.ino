//#define FASTLED_FORCE_SOFTWARE_PINS

#include "FastLED.h"
#include "terminal.h"

#define LED_PIN A0

#define NUM_LEDS (14)

CRGB leds[NUM_LEDS];

enum pattern {PAT_FLOW=0, PAT_FADE};

static TERM_DAT term;

void setup() {
  //turn all LEDs off
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  
  FastLED.addLeds<WS2812, LED_PIN,GRB>(leds, NUM_LEDS);
  FastLED.setBrightness( 255 ); // out of 255

  //Setup serial
  Serial.begin(9600);
  //initialize terminal things
  terminal_init(&term);
}

int pos = 0;
enum pattern pat=PAT_FLOW;

void loop() {

  switch(pat)
  {
    case PAT_FLOW:
      pos += 1;
      fill_rainbow(leds, NUM_LEDS, pos, max(1, 255 / NUM_LEDS) );
      delay(20);
      break;
    case PAT_FADE:
      pos += 1;
      fill_solid(leds, NUM_LEDS, CHSV(pos, 255, 255));
      delay(50);
      break;
  }
  FastLED.show();

  while(Serial.available())
  {
    terminal_proc_char(Serial.read(),&term);
  }

}
