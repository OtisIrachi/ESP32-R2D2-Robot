//********************************************************************************
// R2D2Matrix.ino
// Blue LED Matrix display demo for the R2D2 Dome information window.
// for ESP32 or ESP8266
//
// by RCI
//********************************************************************************
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define the number of devices we have in the chain and the hardware interface
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

// Create a new instance of the MD_MAX72XX class
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Variables for random pattern generation
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
      // Randomly turn on/off each pixel based on ledDensity percentage
      bool pixelOn = random(100) < ledDensity;
      mx.setPoint(row, col, pixelOn);
      }
    }
}
//********************************************************************************
void setup() 
{
  //Serial.begin(115200);
  //Serial.println("R2D2 Dome Display Starting...");
  
  // Initialize the object
  mx.begin();
  
  // Set the intensity (brightness) of the display (0-15)
  mx.control(MD_MAX72XX::INTENSITY, 1);
  
  // Clear the display
  mx.clear();
  
  // Initialize random seed
  randomSeed(analogRead(0));
  
  //Serial.println("Display initialized. Starting random pattern generation...");
}
//********************************************************************************
void loop() 
{
  unsigned long currentTime = millis();

  // Check if it's time to update the pattern
  if (currentTime - lastUpdate >= updateInterval) 
    {
    displayRandomPattern();
    
    // Update the last update time
    lastUpdate = currentTime;
    
    //Serial.println("Generated new random pattern");
    }
}

//********************************************************************************
