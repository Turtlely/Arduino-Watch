#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_RV1805.h>
#include "bitmaps.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char* numberBitmaps[] = {num0,num1,num2,num3,num4,num5,num6,num7,num8,num9};

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_MIDDLE SCREEN_WIDTH/2
#define SCREEN_QUARTER SCREEN_WIDTH/4

RV1805 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.println("RTC failed to update");
  }
  
  //String currentTime = rtc.stringTime(); //uncomment for real model

  String currentTime = "05:44:21AM"; //uncomment when testing

  drawScreen(currentTime,numberBitmaps);
  updateScreen();
  delay(1000);
}


void updateScreen(){
  display.display();
  display.clearDisplay();
}

void drawScreen(String currentTime, const unsigned char* numberBitmaps[]){
  display.drawCircle(SCREEN_MIDDLE,SCREEN_HEIGHT/3,1,1);
  display.drawCircle(SCREEN_MIDDLE,2*SCREEN_HEIGHT/3,1,1);

  int hour1 = currentTime.substring(0,1).toInt();
  int hour2 = currentTime.substring(1,2).toInt();
  int minute1 = currentTime.substring(3,4).toInt();
  int minute2 = currentTime.substring(4,5).toInt();

  display.drawBitmap(SCREEN_QUARTER-5-22,11, numberBitmaps[hour1],22,41,1);
  display.drawBitmap(SCREEN_QUARTER+5,11, numberBitmaps[hour2],22,41,1);

  display.drawBitmap(3*SCREEN_QUARTER-5-22,11, numberBitmaps[minute1],22,41,1);
  display.drawBitmap(3*SCREEN_QUARTER+5,11, numberBitmaps[minute2],22,41,1);  
}
