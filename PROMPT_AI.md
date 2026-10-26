# Asking an AI to write your code

Using an AI is optional, but it saves a lot of time. You can use the assistant of your choice
(ChatGPT, Claude, Gemini, Copilot...). Follow the steps below.

**Tip**: always ask for the **complete file**, never a snippet. A single copy-paste is then
enough to replace everything, with no need to guess what to paste where.

## Steps

1. In the Arduino IDE, open `Arduino_Grove.ino`, click inside it, **Ctrl+A** then **Ctrl+C**.
2. Open your AI assistant in your browser.
3. Copy **Message 1** below and paste it into the AI. Replace the line
   `[PASTE YOUR Arduino_Grove.ino FILE HERE]` with the file copied in step 1 (Ctrl+V over it).
   Send.
4. Describe your idea in a sentence - see the example **Message 2**. For your own laboratory
   process, use **Message 3** and attach the photo of your workflow.
5. The AI answers with the **complete file**. Copy it, go back to the Arduino IDE, **Ctrl+A**
   then **Ctrl+V** in `Arduino_Grove.ino` to replace everything.
6. Upload, test. If it does not work as planned, tell the AI in the same conversation ("the LED
   never turns on", "too fast"...) and ask for the complete file again.

## Message 1 - copy-paste this first

```
Here is my Arduino file (Arduino_Grove.ino) for a practical work, on an Arduino Uno board with
a Grove Beginner Kit sensor kit. All the sensors are already wired and already initialized by
initGroveKit(), which you must NOT modify.

Here is the file as it currently is:

--- START OF FILE ---
[PASTE YOUR Arduino_Grove.ino FILE HERE]
--- END OF FILE ---

Use ONLY the following functions to write my logic. Do not invent other functions, do not add
#include lines, do not modify setup(), and do not use pinMode(), digitalWrite() or analogRead()
directly. Serial.println() / Serial.print() are allowed (the Serial port is already started at
115200 baud, do not call Serial.begin()):

- setLED(bool on): turns the LED on/off
- buzz(frequency, duration_ms): plays a sound on the buzzer (does not block the program)
- isButtonPressed() -> bool: true as long as the button is pressed
- readPotentiometer() -> int (0 to 1023)
- readLight() -> int (0 to 1023)
- readSound() -> int (0 to 1023)
- readTemperature() -> float, in degrees Celsius
- readHumidity() -> float, in percent
- readPressure() -> float, in hPa
- readAcceleration(float &x, float &y, float &z): fills x, y, z with the acceleration (in g)
- displayText(line1, line2 = "", line3 = ""): shows up to 3 lines on the OLED screen
  (16 characters per line, no accents)
- displayClear(): clears the screen
- printAllSensors(): prints all the readings in the Serial Monitor (for testing)

Rules:
1. Change ONLY the content of loop(). If you need global variables or small functions, add them
   just before "void setup()". Do not touch anything else (no new #include, no change in
   setup() or in the top comments).
2. ALWAYS answer with the ENTIRE file, from the very beginning to the very end, in a single
   code block - never just a piece - so that I can select everything and paste it directly in
   the Arduino IDE over my current file.
3. Avoid long delay() calls that block the program, unless I specifically ask for it.
4. Explain in 1 to 2 sentences what the code does, BEFORE the code block (not inside the
   block), so that I can copy the block without having to remove anything.

Wait for my request before writing code. Here is my first request:
```

## Message 2 - example request

```
When I press the button, make the LED blink 3 times, then leave it off. Also play a short beep
at each blink.
```

## Message 3 - request from a photo of your workflow

Attach the photo of your **automated workflow** (the flowchart) to your message, then send
something like this (adapt the part in brackets):

```
The attached photo is the automated workflow of one step of a laboratory process: [describe the
step in one sentence, e.g. "heating a reaction while keeping the temperature around a target"].

I want to SIMULATE this workflow on my Grove Beginner Kit, using only the functions I gave you.

Before the code, give me a short table with, for each box of my workflow:
- which sensor or actuator of the kit stands for it,
- how I can physically trigger it on the kit (e.g. "warm the temperature sensor with your
  finger", "cover the light sensor").
Mention any assumption you made.

Then give me the COMPLETE .ino file. Show the useful values on the OLED screen and in the Serial
Monitor so that I can follow what the program does, and put the thresholds in named constants at
the top so that I can adjust them easily.
```

## If the AI does not follow the rules

Simply answer:

```
Give me the COMPLETE .ino file again, from start to finish, not just a piece. Stay only with the
functions I gave you at the beginning, and do not touch setup().
```

## To go further

Full list of functions: [`README.md`](README.md).
