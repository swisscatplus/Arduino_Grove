// sensors.h
//
// All the wiring and configuration of the Grove Beginner Kit sensors lives in
// this file. You normally do NOT need to touch it during the practical:
// write your code in the Arduino_Grove.ino tab instead, and just use the
// functions listed below.
//
// All the sensors are already wired on the board (it is a single plate,
// no cables to add). Here is where each one is connected:
//
//   Sensor / module                Type      Pin / I2C address
//   ------------------------------ --------- ---------------------------
//   LED                            Digital   D4
//   Buzzer (speaker)               Digital   D5
//   Button                         Digital   D6
//   Rotary potentiometer           Analog    A0
//   Light sensor                   Analog    A6
//   Sound sensor                   Analog    A2
//   Temperature & humidity         I2C/Dig.  DHT20 (I2C 0x38) or DHT11 (D3) - see DHT_TYPE below
//   Air pressure (BMP280)          I2C       0x77 (0x76 as a fallback)
//   3-axis accelerometer           I2C       0x19
//   OLED display 0.96"             I2C       0x78
//
// Libraries to install (Arduino IDE > Tools > Manage Libraries...):
//   - "U8g2" by oliver
//   - "DHT20" by Rob Tillaart           (only if DHT_TYPE == DHT_TYPE_DHT20, the default)
//   - "DHT sensor library" by Adafruit  (only if DHT_TYPE == DHT_TYPE_DHT11)
//   - "Grove - Barometer Sensor BMP280" (Seeed_BMP280)
//   - "Seeed Arduino LIS3DHTR"
//
// For the full list of functions and help if something goes wrong: see README.md

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Wire.h>
#include <U8x8lib.h>
#include "Seeed_BMP280.h"
#include "LIS3DHTR.h"

// ---------------------------------------------------------------------------
// Kit version: most recent kits have a DHT20 sensor (I2C).
// Older kits have a DHT11 sensor (a single digital pin, D3).
// If the temperature/humidity values look wrong, or if the DHT20 never
// starts, replace the line below with DHT_TYPE_DHT11 and upload again.
// ---------------------------------------------------------------------------
#define DHT_TYPE_DHT20 0
#define DHT_TYPE_DHT11 1
#define DHT_TYPE DHT_TYPE_DHT20

#if DHT_TYPE == DHT_TYPE_DHT20
  #include <DHT20.h>
#else
  #include <DHT.h>
  #define DHT11_PIN 3
#endif

// ---------------------------------------------------------------------------
// Pin definitions
// ---------------------------------------------------------------------------
#define LED_PIN     4
#define BUZZER_PIN  5
#define BUTTON_PIN  6
#define POT_PIN     A0
#define LIGHT_PIN   A6
#define SOUND_PIN   A2

// ---------------------------------------------------------------------------
// Global objects for each sensor / actuator
// ---------------------------------------------------------------------------
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);
BMP280 bmp280;
LIS3DHTR<TwoWire> lis3dhtr;

#if DHT_TYPE == DHT_TYPE_DHT20
  DHT20 dht20;
#else
  DHT dht11(DHT11_PIN, DHT11);
#endif

// ---------------------------------------------------------------------------
// Initialization - call it once in setup(). Starts the Serial port (115200
// baud) and initializes every sensor and the screen, so that the rest of the
// program can simply read/write without worrying about the wiring.
// ---------------------------------------------------------------------------
void initGroveKit() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  Wire.begin();

  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);

#if DHT_TYPE == DHT_TYPE_DHT20
  dht20.begin();
#else
  dht11.begin();
#endif

  if (!bmp280.init()) {
    Serial.println(F("Warning: BMP280 pressure sensor not found."));
  }

  lis3dhtr.begin(Wire, 0x19);
  delay(100);
  lis3dhtr.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  lis3dhtr.setFullScaleRange(LIS3DHTR_RANGE_2G);

  u8x8.clear();
  u8x8.drawString(0, 0, "Grove Kit");
  u8x8.drawString(0, 2, "Ready!");

  Serial.println(F("Grove Kit ready. Write your code in loop()!"));
}

// ---------------------------------------------------------------------------
// LED / Buzzer / Button
// ---------------------------------------------------------------------------

// Turns the LED on (true) or off (false).
void setLED(bool on) {
  digitalWrite(LED_PIN, on ? HIGH : LOW);
}

// Plays a sound on the buzzer. Does not block the program: the sound plays
// "in the background" for durationMs milliseconds.
void buzz(unsigned int freqHz, unsigned int durationMs) {
  tone(BUZZER_PIN, freqHz, durationMs);
}

// Returns true as long as the button is pressed.
bool isButtonPressed() {
  return digitalRead(BUTTON_PIN) == HIGH;
}

// ---------------------------------------------------------------------------
// Analog sensors (value between 0 and 1023)
// ---------------------------------------------------------------------------

// Position of the potentiometer (the round knob you turn).
int readPotentiometer() {
  return analogRead(POT_PIN);
}

// Ambient light level.
int readLight() {
  return analogRead(LIGHT_PIN);
}

// Ambient sound level.
int readSound() {
  return analogRead(SOUND_PIN);
}

// ---------------------------------------------------------------------------
// Environment: temperature, humidity, pressure
// ---------------------------------------------------------------------------

// Air temperature, in degrees Celsius.
float readTemperature() {
#if DHT_TYPE == DHT_TYPE_DHT20
  dht20.read();
  return dht20.getTemperature();
#else
  return dht11.readTemperature();
#endif
}

// Relative air humidity, in percent.
float readHumidity() {
#if DHT_TYPE == DHT_TYPE_DHT20
  dht20.read();
  return dht20.getHumidity();
#else
  return dht11.readHumidity();
#endif
}

// Atmospheric pressure, in hPa (hectopascals).
float readPressure() {
  return bmp280.getPressure() / 100.0; // Pa -> hPa
}

// ---------------------------------------------------------------------------
// Motion: acceleration on 3 axes, in g
// ---------------------------------------------------------------------------

// Fills x, y and z with the acceleration measured on each axis (in g).
// Example:
//   float x, y, z;
//   readAcceleration(x, y, z);
void readAcceleration(float &x, float &y, float &z) {
  x = lis3dhtr.getAccelerationX();
  y = lis3dhtr.getAccelerationY();
  z = lis3dhtr.getAccelerationZ();
}

// ---------------------------------------------------------------------------
// OLED display (128x64 pixels = 16 characters x 8 rows)
// ---------------------------------------------------------------------------

// Clears the screen.
void displayClear() {
  u8x8.clear();
}

// Writes one line of text on the given row, padded with spaces up to 16
// characters so that the previous text is overwritten without having to clear
// the whole screen (clearing at every loop() makes the screen flicker).
void drawLine(uint8_t row, const String &text) {
  String padded = text;
  while (padded.length() < 16) padded += ' ';
  char buf[17];
  padded.toCharArray(buf, 17); // keeps at most 16 characters
  u8x8.drawString(0, row, buf);
}

// Displays up to 3 lines of text on the screen. line2 and line3 are optional.
// Example: displayText("Hello", "line 2");
// Note: the small OLED font does not handle accents or special characters.
void displayText(String line1, String line2 = "", String line3 = "") {
  drawLine(0, line1);
  drawLine(2, line2);
  drawLine(4, line3);
}

// ---------------------------------------------------------------------------
// Debugging help - prints all the sensor readings on the Serial port in a
// single call. It is not called automatically: paste it in loop() to quickly
// check that everything works.
// ---------------------------------------------------------------------------
void printAllSensors() {
  Serial.println(F("---- Grove Kit sensor readings ----"));

  Serial.print(F("Button: "));
  Serial.println(isButtonPressed() ? "pressed" : "released");

  Serial.print(F("Potentiometer: "));
  Serial.println(readPotentiometer());

  Serial.print(F("Light: "));
  Serial.println(readLight());

  Serial.print(F("Sound: "));
  Serial.println(readSound());

  Serial.print(F("Temperature (C): "));
  Serial.println(readTemperature());

  Serial.print(F("Humidity (%): "));
  Serial.println(readHumidity());

  Serial.print(F("Pressure (hPa): "));
  Serial.println(readPressure());

  float ax, ay, az;
  readAcceleration(ax, ay, az);
  Serial.print(F("Acceleration (g): x="));
  Serial.print(ax);
  Serial.print(F(" y="));
  Serial.print(ay);
  Serial.print(F(" z="));
  Serial.println(az);

  Serial.println();
}

#endif // SENSORS_H
