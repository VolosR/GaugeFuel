#include <TFT_eSPI.h> 
#include "fuel.h"
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite img = TFT_eSprite(&tft);
TFT_eSprite ln = TFT_eSprite(&tft);

double rad=0.01745;
int angle;

int sx=120;
int sy=120;
int r=122;

float x[360];
float y[360];
float x2[360];
float y2[360];

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;


void setup() {

    pinMode(12,OUTPUT);
    digitalWrite(12,1);

    ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
    ledcAttachPin(5, pwmLedChannelTFT);
    ledcWrite(pwmLedChannelTFT, 100);

    tft.init();
    tft.setRotation(0);
    tft.setSwapBytes(true);
    img.setSwapBytes(true);
    tft.fillScreen(TFT_ORANGE);
    img.createSprite(240, 240);
    img.setTextDatum(4);
    img.setTextColor(TFT_WHITE,TFT_BLACK);

     int i=0;
     int a=136;

     while(a!=44)
  {
   x[i]=r*cos(rad*a)+sx;
   y[i]=r*sin(rad*a)+sy;
   x2[i]=(r-80)*cos(rad*a)+sx;
   y2[i]=(r-80)*sin(rad*a)+sy;
   i++;
   a++;
   if(a==360)
   a=0;
  }

}

//min angle 136 or 137
//max angle 43
// 267


int n=12;
int fuelA=0;
int percent=0;
void loop() {
  fuelA=map(analogRead(13),0,4098,0,260);
 img.fillSprite(TFT_BLACK);
 while(n<fuelA){
  if(n<50)
 img.fillTriangle(x2[n],y2[n],x[n-2],y[n-2],x[n+2],y[n+2],0xf3d0);
 else
 img.fillTriangle(x2[n],y2[n],x[n-2],y[n-2],x[n+2],y[n+2],TFT_WHITE);
 n=n+8;
 }
 n=12;
 img.fillCircle(sx,sy,78,TFT_BLACK);
 percent=map(fuelA,0,260,0,100);
 img.drawString(String(percent),sx,sy,7);
 img.drawString("FUEL",sx,sy+46,4);
 img.drawString("F",sx+62,sy+86,4);
 img.drawString("E",sx-62,sy+86,4);
 img.pushImage(100,186,42,42,fuel);
 img.pushSprite(0,0);

 
/*
 fuelA=fuelA+5;
 if(fuelA>260)
 fuelA=0;
 */
 

}
