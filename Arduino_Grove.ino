// Arduino_Grove.ino
//
// Starter program for the Arduino practical work, for the Grove Beginner Kit
// For Arduino. All the sensors and buttons of the board are already set up
// for you in the sensors.h file (the other tab next to this one) - you do not
// need to understand how they are wired.
//
// -> Do not touch setup().
// -> Write your code in loop(), using the functions below:
//
//   setLED(bool on)              turns the LED on/off (true/false)
//   buzz(frequency, duration_ms) plays a sound on the buzzer
//   isButtonPressed()            -> true if the button is pressed
//   readPotentiometer()          -> number between 0 and 1023
//   readLight()                  -> number between 0 and 1023 (light)
//   readSound()                  -> number between 0 and 1023 (sound)
//   readTemperature()            -> temperature in degrees C
//   readHumidity()               -> humidity in %
//   readPressure()               -> pressure in hPa
//   readAcceleration(x, y, z)    -> fills x, y, z (acceleration in g)
//   displayText(line1, line2, line3)  -> shows up to 3 lines on the screen
//   displayClear()               -> clears the screen
//   printAllSensors()            -> prints all the readings in the Serial
//                                   Monitor, handy for testing
//
// The full list of functions and help if something goes wrong: see README.md
// Want to ask an AI to write your code? See PROMPT_AI.md

#include "sensors.h"

const int THRESHOLD = 30;       // <-- 1) choose a value, using what you measured in 2a

void setup() {
  initGroveKit();
}

void loop() {
  // ================================
  //   WRITE YOUR CODE HERE
  // ================================
    int light = readLight();
 
  if (light < THRESHOLD) {     // <-- 2) is ">" the right comparison? Or "<" ?
    setLED(true);
  } else {
    setLED(false);
  }
 
  // Plot the light and the threshold together
  Serial.print("Light:");
  Serial.print(light);
  Serial.print(",Threshold:");
  Serial.println(THRESHOLD);
  delay(100);                         // wait 0.1 s
}
