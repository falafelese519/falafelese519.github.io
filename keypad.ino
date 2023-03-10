/* This example shows basic usage of the NeoTrellis.
  The buttons will light up various colors when pressed.
  The interrupt pin is not used in this example.
*/

#include "Adafruit_NeoTrellis.h"

Adafruit_NeoTrellis trellis;

int inputPass[4] = {0};
int correctPass[4] = {3,2, 1, 0};
int keyCnt = 0;

//define a callback for key presses
TrellisCallback blink(keyEvent evt){
  // Check is the pad pressed?
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    trellis.pixels.setPixelColor(evt.bit.NUM, Wheel(map(evt.bit.NUM, 0, trellis.pixels.numPixels(), 0, 255))); //on rising

    inputPass[keyCnt++] = evt.bit.NUM;
    
    //Serial.println("key pressed step1");
     Serial.println(evt.bit.NUM);

    delay(100);
    
  } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
  // or is the pad released?
    trellis.pixels.setPixelColor(evt.bit.NUM, 0); //off falling
   // Serial.println("key pressed step2");
    delay(100);
  }

  if(keyCnt==4)
  {
    keyCnt = 0;
    for(int i = 0; i < 4; i++)
    {
      if(inputPass[i] != correctPass[i])
      {
        digitalWrite(11, 1); //password incorrect
        Serial.println("wrong password \n"); 
        digitalWrite(10, 0);
        return 0;
      }
    }

    digitalWrite(10, 1); //password correct
    digitalWrite(11, 0);

    //delay(10000);

    //digitalWrite(10, 0); //password correct
    //digitalWrite(11, 1);
        
        
        Serial.println("correct password \n"); 
  }

        
      
     // Turn on/off the neopixels!
  trellis.pixels.show();
  return 0;
}
  



void setup() {
  Serial.begin(115200);
  // while(!Serial) delay(1);
  
  if (!trellis.begin()) {
    Serial.println("Could not start trellis, check wiring?");
    while(1) delay(1);
  } else {
    Serial.println("NeoPixel Trellis started");
  }

  //activate all keys and set callbacks
  for(int i=0; i<NEO_TRELLIS_NUM_KEYS; i++){
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    trellis.registerCallback(i, blink);
  }

  //do a little animation to show we're on
  for (uint16_t i=0; i<trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, Wheel(map(i, 0, trellis.pixels.numPixels(), 0, 255)));
    trellis.pixels.show();
    delay(50);
  }
  for (uint16_t i=0; i<trellis.pixels.numPixels(); i++) {
    trellis.pixels.setPixelColor(i, 0x000000);
    trellis.pixels.show();
    delay(50);
  }

  digitalWrite(11, 1);
  digitalWrite(10, 0);
}

void loop() {
  trellis.read();  // interrupt management does all the work! :)
  
  delay(20); //the trellis has a resolution of around 60hz


  
  return 0;
}
  


/******************************************/

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return trellis.pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return trellis.pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return trellis.pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  return 0;
}
