/*

WARNING: This is written to be deployed on an Arduino Nano ESP 32. That's a 3.3V
device. The Grove LCD Display (at least V4 that I'm using - I understand V5
might be 3.3V compatible) operates at 5V. This is therefore intended to work
with a level shifter. See the README for circuit details. Without the level
shifter you run the risk of damaging your microcontroller, depending on how you
wire up your 5 V supply and LCD display with your Arduino.

*/
#include <Arduino.h>
#include <Wire.h>
#include "rgb_lcd.h"

/************************
 * Variables
 ************************/
// The LCD display
rgb_lcd lcd;

/************************
 * Entry point methods
 ************************/
void setup() {
  // Start the IC2 interface
  Wire.begin();
  // Set up the LCD display (16 characters x 2 rows)
  // Start up the display
  lcd.noCursor();
  lcd.noBlink();
  lcd.begin(16, 2);
  
  // Turn backlight off
  lcd.setRGB(0,0,0);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  
  delay(1000);

}

void loop() {

  static unsigned char r = 255;
  static unsigned char g = 0;
  static unsigned char b = 0;

  // Set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  // Print the current RGB values
  lcd.printf("%03d %03d %03d", r, g, b);
  // Rainbow backlight
  static int segment = 0;
  switch (segment) {
    case 0:
      g = g + 5;
      if (g == 255) segment++;
      break;
    case 1:
      r = r - 5;
      if (r == 0) segment++;
      break;
    case 2:
      b = b + 5;
      if (b == 255) segment++;
      break;
    case 3:
      g = g - 5;
      if (g == 0) segment++;
      break;
    case 4:
      r = r + 5;
      if (r == 255) segment++;
      break;
    case 5:
      b = b - 5;
      if (b == 0) segment = 0;
      break;
    default:
      break;
  }
  lcd.setRGB(r,g,b);
  delay(100);
}
