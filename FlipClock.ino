/*
Clock-Program with Flip-Digits

This program simulates an old digital clock with flip-digits

It runs on an ESP32 (WROOM-Module)
It runs with a 2,5"-display, resolution 320x240 pixel based on a ST7789-chipset
The display needs to use the color 565-scheme for 16bit-color-adressing.

The display is connected via SPI.
MOSI (SDA) is connected to Port 23
SCLK (SCL) is connected to Port 18
CS is connected to Port 13
DC is connected to Port 14
RST is connected to Port 4

You can change some of these ports, perhaps not all.

The clock needs five push-buttons connected to GND and the port it belongs to

Button 1 : Change Minute-Digit 1 - Port 32
Button 2 : Change Minute-Digit 2 - Port 33
Button 3 : Change Hour-Digit 1 - Port 25
Button 4 : Change Hour-Digit 2 - Port 26
Button 5 : Start Clock - Port 27

Button 6 - Port 15 and Button 7 - Port 16 can be left unconnected, do the same as Button 5

After new start you need to set the time, then press Button 5 to Start the clock

You can change the include-statement for different colors. Put a // in front of the active include and remove
the // in front of your desired color scheme.

The digit-images need much of the flash-memory, so it is possible you need to change the memory-setting.
Use a setting with disable OTA and much program space. (HUGE APP 3MB...)

Enjoy!

Turorius ( https://www.youtube.com/@Tutorius )

*/

#define YPOSD 50
#define XPOS1 0
#define XPOS2 70
#define XPOS3 150
#define XPOS4 220
#define XPOS5 300

#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_I2CDevice.h>
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library


#define TFT_MOSI 23  // (gelb) SDA Pin on ESP32
#define TFT_SCLK 18  // (weiss)SCL Pin on ESP32
#define TFT_CS   13  // (gruen)Chip select control pin
#define TFT_DC   14  // (schwarz) Data Command control pin
#define TFT_RST  4   // (grau) Reset pin (could connect to RST pin)

#define KEY1 32
#define KEY2 33
#define KEY3 25
#define KEY4 26
#define KEY5 27
#define KEY6 15
#define KEY7 16

// Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Color-Includes 
//
// ROT - red with white letters  ; ROTGELB - red with yellow letters
// BLAU - blue with white letters   ; BLAUGELB - blue with yellow letters
// SCHWARZ - dark with white letters   ; SCHWARZGELB - dark with yellow letters
// GELB - yellow with black letters   ; GRUEN - green with white letters
// PINK - magenta with white letters   ; WEISS - white with black letters 

//#include "ROT.h"
//#include "ROTGELB.h"
#include "BLAU.h"
//#include "BLAUGELB.h"
//#include "SCHWARZ.h"
//#include "SCHWARZGELB.h"
//#include "GELB.h"
//#include "GRUEN.h"
//#include "PINK.h"
//#include "WEISS.h"

void setup()
{
  int i,j,k,numdigit;
  int valn[4],valo[4];
  char s[80];
  int xpos[5];
  int seco;
  int keyready;
  int oldkey1,oldkey2,oldkey3,oldkey4,oldkey5,letsfetz;
  unsigned long clocki,clockm,clocks;
  // Serial.begin(115200);
  pinMode(KEY1,INPUT_PULLUP);
  pinMode(KEY2,INPUT_PULLUP);
  pinMode(KEY3,INPUT_PULLUP);
  pinMode(KEY4,INPUT_PULLUP);
  pinMode(KEY5,INPUT_PULLUP);
  pinMode(KEY6,INPUT_PULLUP);
  pinMode(KEY7,INPUT_PULLUP);
  tft.init(240, 320, SPI_MODE2);    // Init ST7789 display 135x240 pixel
  tft.setRotation(3);
  tft.fillScreen(tft.color565(30,30,30));
  xpos[0]=XPOS1;
  xpos[1]=XPOS2;
  xpos[2]=XPOS3;
  xpos[3]=XPOS4;
  xpos[4]=XPOS5;
  do
  {
    for (i=0;i<4;i++)
      tft.drawRGBBitmap(xpos[i],YPOSD,&image1[0],60,120);
    tft.drawRGBBitmap(xpos[4],YPOSD,&image2[0],20,120);
    valn[0]=valn[1]=valn[2]=valn[3]=0;
    valo[0]=valo[1]=valo[2]=valo[3]=0;
    oldkey1=oldkey2=oldkey3=oldkey4=oldkey5=false;
    letsfetz=false;
    do
    {
      keyready=false;
      if (!digitalRead(KEY1))
      {
        if (!oldkey1)
        {
          letsfetz=true;
          oldkey1=true;
          valn[0]++;
          if (valn[0]>9) valn[0]=0;
        }
      }
      else
      {
        oldkey1=false;
      }
      if (!digitalRead(KEY2))
      {
        if (!oldkey2)
        {
          letsfetz=true;
          oldkey2=true;
          valn[1]++;
          if (valn[1]>5) valn[1]=0;
        }
      }
      else
      {
        oldkey2=false;
      }
      if (!digitalRead(KEY3))
      {
        if (!oldkey3)
        {
          letsfetz=true;
          oldkey3=true;
          valn[2]++;
          if (valn[2]>9) valn[2]=0;
        }
      }
      else
      {
        oldkey3=false;
      }
      if (!digitalRead(KEY4))
      {
        if (!oldkey4)
        {
          letsfetz=true;
          oldkey4=true;
          valn[3]++;
          if (valn[3]>2) valn[3]=0;
          if (valn[3]==2)
          {
            if (valn[2]>3) valn[2]=0;
          }
        }
      }
      else
      {
        oldkey4=false;
      }
      if (letsfetz)
      {
        for (i=0;i<4;i++)
          tft.drawRGBBitmap(xpos[3-i],YPOSD,&image1[valn[i]*60*120*8],60,120);
        letsfetz=false;
      }
      if ((!digitalRead(KEY5))||(!digitalRead(KEY6))||(!digitalRead(KEY7)))
      {
        keyready=true;
      }
    } while(!keyready);    
    for (i=0;i<4;i++)
      valo[i]=valn[i];    
    seco=0;
    clockm=clocks=millis();
    do
    {
      clocki=millis();
      if (clocki-clockm>=60000L)
      {
        clockm+=60000L;
      valn[0]++;
      if (valn[0]>9)
      {
        valn[0]=0;
        valn[1]++;
        if (valn[1]>5)
        {
          valn[1]=0;
          valn[2]++;
          if (valn[2]>9)
          {
            valn[2]=0;
            valn[3]++;
          }
          if ((valn[2]==4)&&(valn[3]==2))
          {
            valn[2]=valn[3]=0;
          }
        }
      }
      numdigit=0;
      for (i=0;i<4;i++)
        if (valo[i]!=valn[i]) numdigit++;
      for (i=0;i<8;i++)
      {
        clocki=millis();
        if (clocki-clocks>=600L)
        {
          do
          {
            seco++;
            clocks+=500L;
          } while (clocki-clocks>=500L);
          if (seco>=120) seco-=120;
          tft.drawRGBBitmap(xpos[4],YPOSD,&image2[seco*20*120],20,120);
        }
        if (valo[0]!=valn[0])
        {
          tft.drawRGBBitmap(xpos[3-0],YPOSD,&image1[valo[0]*60*120*8+i*60*120],60,120);
        }
        if (valo[1]!=valn[1])
        {
          if (valo[1]!=5)
            tft.drawRGBBitmap(xpos[3-1],YPOSD,&image1[valo[1]*60*120*8+i*60*120],60,120);
          else
            tft.drawRGBBitmap(xpos[3-1],YPOSD,&image1[(valo[1]+5)*60*120*8+i*60*120],60,120);
        }
        if (valo[2]!=valn[2])
        {
          if ((valo[3]==2)&&(valo[2]==3))
            tft.drawRGBBitmap(xpos[3-2],YPOSD,&image1[12*60*120*8+i*60*120],60,120);
          else
            tft.drawRGBBitmap(xpos[3-2],YPOSD,&image1[valo[2]*60*120*8+i*60*120],60,120);
        }
        if (valo[3]!=valn[3])
        {
          if (valo[3]!=2)
            tft.drawRGBBitmap(xpos[3-3],YPOSD,&image1[valo[3]*60*120*8+i*60*120],60,120);
          else
            tft.drawRGBBitmap(xpos[3-3],YPOSD,&image1[(valo[3]+9)*60*120*8+i*60*120],60,120);
        }
        delay(50*(4-numdigit));
      }
      valo[0]=valn[0];
      valo[1]=valn[1];
      valo[2]=valn[2];
      valo[3]=valn[3];
      }

      if (clocki-clocks>=600L)
      {
        do
        {
          seco++;
          clocks+=500L;
        } while (clocki-clocks>=500L);
        if (seco>=120) seco-=120;
        tft.drawRGBBitmap(xpos[4],YPOSD,&image2[seco*20*120],20,120);
      }
    } while (1==1);
    for (i=0;i<8;i++)
    {
      // tft.drawRGBBitmap(0,0,&image[i*60*120+j*60*120*8],60,120);
    }
  } while(1==1);
}

void loop()
{
}
