/*********************

Example code for the Adafruit RGB Character LCD Shield and Library

This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <QueueArray.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
int lightPin = 0;  //define a pin for Photo resistor
const String msg = "Collecting Data!";
QueueArray <int> dataQueue;
int total = 0;
const int minimumDataCount = 16;

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  lcd.setBacklight(WHITE);
}

uint8_t i=0;
void loop() {

  int currentLightValue = analogRead(lightPin);
  dataQueue.push(currentLightValue);
  total += currentLightValue;

// Comment these if you're not debugging via a PC.
  Serial.print("Current value: ");// + " Total: " + total + " Count: " + dataQueue.count() + " Average: " + (total/dataQueue.count()));
  Serial.print(currentLightValue);
  Serial.print(" Total: ");
  Serial.print(total);
  Serial.print(" Count: ");
  Serial.print(dataQueue.count());
  Serial.print(" Average: ");
  Serial.println(total/dataQueue.count());
  
  if(dataQueue.count() <= minimumDataCount) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(msg);

    
    for (int i = 0; i < dataQueue.count(); i++) {
      lcd.setCursor(i,1);
      lcd.print("*");
    }
  } else {
    int dataToRemove = dataQueue.pop();
    total -= dataToRemove;
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Avg light level:");
  
    lcd.setCursor(0,1);
    lcd.print(total/dataQueue.count());
  }

  delay(750);
  
}
