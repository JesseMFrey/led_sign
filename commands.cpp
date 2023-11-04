
#include "terminal.h"
#include <stdio.h>
#include <string.h>
#include <FastLED.h>
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
    FastLED.setBrightness( temp );
  }
  //printf("Brightness : %u\n", FastLED.getBrightness());
  Serial.print("Brightness : ");
  Serial.print(FastLED.getBrightness());
  Serial.print("\r\n");
  return 0;
}


const CMD_SPEC cmd_tbl[]={
                            {"help","get help on commands",helpCmd},
                            {"brt","adjust brightness",brt_Cmd},
};
