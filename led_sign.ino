//#define FASTLED_FORCE_SOFTWARE_PINS

#include "terminal.h"
#include "sign.h"

#define LED_PIN A0

#define NUM_LEDS (14)

Adafruit_NeoPixel sign_leds(NUM_LEDS , LED_PIN, NEO_GRB + NEO_KHZ800);

static TERM_DAT term;

void setup() {
  
  sign_leds.begin();
  sign_leds.clear();

  //Setup serial
  Serial.begin(9600);
  //initialize terminal things
  terminal_init(&term);
}
uint16_t pos = 0;
enum pattern sign_pattern=PAT_FLOW;
int is_off = 1;

void loop() {

  switch(sign_pattern)
  {
    case PAT_FLOW:
      pos += 250;
      sign_leds.rainbow(pos);
      delay(20);
      break;
    case PAT_FADE:
      pos += 50;
      sign_leds.fill(sign_leds.ColorHSV(pos, 255, 255));
      delay(20);
      break;
    case PAT_OFF:
      if( !is_off)
      {
        is_off = 1;
        sign_leds.fill();
        sign_leds.show();
      }
  }

  if( sign_pattern != PAT_OFF )
  {
    is_off=0;
    sign_leds.show();
  }

  while(Serial.available())
  {
    terminal_proc_char(Serial.read(),&term);
  }

}
