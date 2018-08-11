/* Utilizes Adafruit Circuit Playground to take in sound levels. 
 * Light levels will indicate whether or not the user is being too
 * loud. 
 * There are three levels: No light, Yellow and Red.
 * No light level means that the sound level is determined to be
 * "quiet" enough. 
 * Yellow light level means that the sound level is a bit above the
 * sound level.
 * Red light level means that it is significantly above what is
 * determined to be loud.
 */
#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>
#include <Wire.h>
#include <SPI.h>

/*GLOBAL VARIABLES*/
//Sound boundaries
int MID_BOUNDARY = 343;
int HIGH_BOUNDARY = 346;
//Constant to set colors
int COLOR_CONSTANT = 255;
//brightness level for the LED lights that give off notifications.
int FLASH_BRIGHTNESS = 125;
int LOW_BRIGHTNESS = 25;

void setup() {
  // setup code here; to run once:
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(LOW_BRIGHTNESS);
  CircuitPlayground.clearPixels();
}

//runs repeatedly to take into account the sound levels.
void loop() { 
  // put your main code here, to run repeatedly:
  int red = 0;
  int green = 0;
  int blue = 0;
  int value = CircuitPlayground.soundSensor();
  if(value>=MID_BOUNDARY && value<=HIGH_BOUNDARY){
    //set red and green to values that would allow us to get yellow color.
    red = COLOR_CONSTANT;
    green = 100;
    blue = 0;
    
  }
  //if sound level is too high, set colors to red
  else if(value > HIGH_BOUNDARY){
    green = 0;
    red = COLOR_CONSTANT;
    blue = 0;
  }
  //if quiet: show green
  else{
    red =0;
    green = 0;
    blue = 0;
  }
  Serial.print("Sound Sensor: ");
  Serial.println(value);
  //flash if red
  if(red==255&&green == 0 && blue == 0){
    CircuitPlayground.setBrightness(FLASH_BRIGHTNESS);
    flash(red, green, blue);
  }
  //set LED pixel colors
  for(int i=0; i<10; i++){
    if(red>0 && green != 100){
      CircuitPlayground.setBrightness(FLASH_BRIGHTNESS);
      
    }
    else if(red>0){
      CircuitPlayground.setBrightness(LOW_BRIGHTNESS);

    }
    CircuitPlayground.strip.setPixelColor(i, red, green, blue);
  }
  CircuitPlayground.strip.show();

  delay(1000);

}
void flash(int red, int green, int blue){
  int i = 0;
  for(i = 0; i < 4; i++){
    red = 255;
    for(int i=0; i<10; i++){
      CircuitPlayground.strip.setPixelColor(i, red, green, blue);
    }
    CircuitPlayground.strip.show();
    delay(100);
    red = 0;
    for(int i=0; i<10; i++){
      CircuitPlayground.strip.setPixelColor(i, red, green, blue);
    }
    CircuitPlayground.strip.show();
    delay(100);
  }
}


