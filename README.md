# Arduino_Grove

A ready-to-use Arduino program for the [Grove Beginner Kit For Arduino by Seeed](https://wiki.seeedstudio.com/Grove-Beginner-Kit-For-Arduino/),
used for the Arduino practical work (introduction to sensors, actuators and the automation of a
laboratory step).

All the sensors and buttons of the board are already wired (it is a single plate, there is no
cable to connect) and already set up in the code. You just open `Arduino_Grove.ino` and write
your own code in `loop()`, using the functions listed below. You do not need to know how the
sensors are wired or how to start them.

**Small glossary**, for people who do not usually code:
- **Sensor**: a component that measures something (light, sound, temperature...).
- **Actuator**: a component that *does* something (a LED that lights up, a buzzer that beeps...).
- **Pin**: one of the small connectors of the board where a sensor is plugged in.
- **Library**: a piece of code written by someone else, which you install to be able to use a
  sensor easily.
- **Upload**: sending your program from the computer to the Arduino board.
- **`loop()`**: the part of the program that repeats over and over, as long as the board is
  powered. This is where you write the logic of your project.
- **Threshold**: a limit value. When a measurement goes above or below it, the program takes a
  decision (for example "if the light is below 300, turn the LED on").

## Getting started

1. Open `Arduino_Grove.ino` in the Arduino IDE (`sensors.h` appears as a second tab next to it -
   you do not need to touch it).
2. Install the required libraries (menu **Tools → Manage Libraries...**, then search for each
   name below and click Install):
   - **U8g2** by oliver - for the OLED screen
   - **DHT20** by Rob Tillaart - for the temperature/humidity sensor (default; see "Depending on
     your kit" below if yours is different)
   - **Grove - Barometer Sensor BMP280** (Seeed_BMP280) - for the atmospheric pressure
   - **Seeed Arduino LIS3DHTR** - for the accelerometer
3. Select the right board: **Tools → Board → Arduino Uno** (the board of the kit, a Seeeduino
   Lotus, is Uno-compatible), and the right port in **Tools → Port**.
4. Click the "Upload" button (the arrow). The OLED screen should show "Grove Kit / Ready!", and
   the Serial Monitor (open it with the magnifying glass at the top right, set to 115200 baud)
   should print "Grove Kit ready."
5. Write your own logic in `loop()`!

## List of available functions

| Function | Returns | Description |
|---|---|---|
| `setLED(bool on)` | - | Turns the LED on (`true`) or off (`false`) |
| `buzz(frequency, duration_ms)` | - | Plays a sound on the buzzer (does not block the program) |
| `isButtonPressed()` | `bool` | `true` as long as the button is pressed |
| `readPotentiometer()` | `int` (0-1023) | Position of the potentiometer (the knob you turn) |
| `readLight()` | `int` (0-1023) | Ambient light level |
| `readSound()` | `int` (0-1023) | Ambient sound level |
| `readTemperature()` | `float` (°C) | Air temperature |
| `readHumidity()` | `float` (%) | Air humidity |
| `readPressure()` | `float` (hPa) | Atmospheric pressure |
| `readAcceleration(float &x, float &y, float &z)` | - | Fills `x`/`y`/`z` with the acceleration (in g) |
| `displayText(line1, line2="", line3="")` | - | Shows up to 3 lines of text on the OLED screen |
| `displayClear()` | - | Clears the OLED screen |
| `printAllSensors()` | - | Prints all the readings in the Serial Monitor (handy for testing) |

## Example

```cpp
void loop() {
  float t = readTemperature();
  displayText("Temperature:", String(t) + " C");

  if (isButtonPressed()) {
    buzz(1000, 200);
    setLED(true);
  } else {
    setLED(false);
  }
  delay(200);
}
```

## Serial Monitor and Serial Plotter

To *see* what a sensor measures, send the value to the computer with `Serial.println(...)`:

```cpp
void loop() {
  Serial.println(readLight());
  delay(100);
}
```

- **Serial Monitor** (magnifying glass, top right, **115200 baud**): shows the values as text.
- **Serial Plotter** (menu **Tools → Serial Plotter**, **115200 baud**): draws the values as a
  live curve. To plot several curves, print them on the same line, with a label and separated by
  a comma, e.g. `Light:350,Threshold:300`.

Open only one of the two at a time.

## Want to use an AI to write your code?

See the [`PROMPT_AI.md`](PROMPT_AI.md) file: it contains a text to copy-paste into an AI
assistant (ChatGPT, Claude, Gemini...) to explain the rules of the game, plus an example request
and a request that works from a photo of your workflow. This way, the AI only writes code that is
compatible with this project.

## Depending on your kit / if something goes wrong

Seeed has made several versions of this kit over time. If something does not match what is
described here:

- **Temperature/humidity sensor.** Most recent kits have a **DHT20** sensor (plugged in I2C).
  Older kits have a **DHT11** (plugged on the digital pin D3). If `readTemperature()` /
  `readHumidity()` give strange values, or if the program gets stuck at startup, open the
  `sensors.h` tab and replace:
  ```cpp
  #define DHT_TYPE DHT_TYPE_DHT20   // replace with DHT_TYPE_DHT11
  ```
  with `DHT_TYPE_DHT11`, install the **"DHT sensor library" by Adafruit** library (and, if the
  computer asks while compiling, **"Adafruit Unified Sensor"**) instead of "DHT20", then upload
  the program again.

- **Pressure sensor.** This program is made for the **BMP280**. Some more recent kits have an
  SPL07-003 (SPA06-003) sensor instead - if you see the message "BMP280 pressure sensor not
  found" in the Serial Monitor at startup, this is probably your case. The rest of the kit works
  normally; only `readPressure()` is affected. To use it, replace the `Seeed_BMP280.h` library /
  the `BMP280` object in `sensors.h` with Seeed's `SPL07-003` library and its equivalent
  functions.

- **I2C address conflict.** If a sensor never starts, check that no other device on the I2C bus
  uses the same address: OLED screen `0x78`, DHT20 `0x38`, BMP280 `0x77`/`0x76`, accelerometer
  `0x19`.

- **Quick check.** Paste `printAllSensors();` at the very top of `loop()`, then open the Serial
  Monitor (115200 baud): all the readings are displayed live. Handy to check that the board and
  the libraries work, before writing your real logic.

- **No port in Tools → Port.** Unplug and replug the USB cable, try another cable (some are
  charge-only), and ask your instructor.
