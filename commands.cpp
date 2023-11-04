
#include "terminal.h"
#include "sign.h"
#include <stdio.h>
#include <string.h>
#include <Arduino.h>

int brt_Cmd(int argc, char** argv)
{
  char *eptr;
  long int temp;


  if(argc>0)
  {
    temp = strtol(argv[1], &eptr, 0);

    if(*eptr)
    {
      if(!strcmp(argv[1], "on"))
      {
        // maximum brightness
        temp = 255;
      }
      else if(!strcmp(argv[1], "off"))
      {
        // minimum brightness
        temp = 0;
      }
      else
      {
        //end of string not found
        printf("Error while parsing \"%s\" unknown suffix \"%s\"\r\n",argv[1],eptr);
        Serial.println("Error : unable to parse argument");
        return 2;
      }
    }
    if(temp<0)
    {
        //printf("Error : brightness must be greater than zero. got %li\r\n",temp);
        Serial.println("Error : brightness must be greater than zero.");
        return 3;
    }

    if(temp>255)
    {
        //printf("Error : brightness must be less than %li. got %li\r\n",255,temp);
        Serial.println("Error : brightness too high");
        return 4;
    }
    //set brightness
    sign_leds.setBrightness( temp );
  }
  //printf("Brightness : %u\n", FastLED.getBrightness());
  Serial.print("Brightness : ");
  Serial.print(sign_leds.getBrightness());
  Serial.print("\r\n");
  return 0;
}

struct {
  enum pattern val;
  const char *name;
} pat_tbl[] = {
  {PAT_OFF, "off"},
  {PAT_FLOW, "flow"},
  {PAT_FADE, "fade"},
};

int pat_Cmd(int argc, char** argv)
{
  int i;
  enum pattern p;
  if(argc>0)
  {
    p = PAT_INVALID;
    for(i=0; i< sizeof(pat_tbl)/sizeof(pat_tbl[0]); i++)
    {
      if(!strcmp(argv[1], pat_tbl[i].name))
      {
        p = pat_tbl[i].val;
        break;
      }
    }
    if(p == PAT_INVALID)
    {
      Serial.print("Invalid pattern");
    }
    sign_pattern = p;
  }
  Serial.print("Pattern : ");
  Serial.print(sign_pattern);
  Serial.print("\r\n");
  return 0;
}


const CMD_SPEC cmd_tbl[]={
                            {"help", "get help on commands", helpCmd},
                            {"brt", "adjust brightness", brt_Cmd},
                            {"pat", "change LED pattern", pat_Cmd},
                            {NULL, NULL, NULL},
};
