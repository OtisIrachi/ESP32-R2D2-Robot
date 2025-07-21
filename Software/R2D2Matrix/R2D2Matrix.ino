//********************************************************************************
// R2D2Matrix.ino
// Blue LED Matrix display demo for the R2D2 Dome information window.
// for ESP32 or ESP8266
//
// by RCI
//********************************************************************************
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1

#ifdef ESP32
#define DATA_PIN  25     
#define CS_PIN    26     
#define CLK_PIN   27
#else
#define DATA_PIN  12     
#define CS_PIN    14     
#define CLK_PIN   13
#endif

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Variables 
int ledDensity = 55; // Percentage chance for each LED to be on (0-100)
unsigned long lastUpdate = 0;
const unsigned long updateInterval = 1000; // 1 second
//********************************************************************************
// Generate and display a truly random pattern
void displayRandomPattern() 
{
  mx.clear();
  
  for (int row = 0; row < 8; row++) 
    {
    for (int col = 0; col < 8; col++) 
      {
      bool pixelOn = random(100) < ledDensity;
      mx.setPoint(row, col, pixelOn);
      }
    }
}
//********************************************************************************
void setup() 
{
  // Init Max7219
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 1);
  mx.clear();
  randomSeed(analogRead(0));
  
}
//********************************************************************************
void loop() 
{
  unsigned long currentTime = millis();

  if (currentTime - lastUpdate >= updateInterval) 
    {
    displayRandomPattern();
    lastUpdate = currentTime;
    }
}

//********************************************************************************
