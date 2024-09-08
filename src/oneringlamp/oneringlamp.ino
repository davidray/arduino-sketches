#include <Chase.h>
#include <Pacifica.h>
#include <Fire2012.h>
#include <FastLED.h>


#define NUM_LEDS 60
#define DATA_PIN 6
#define DELAY 50
#define NUM_MODES 7
#define CHASE 0
#define BLINK 1
#define SOLID 2
#define PULSE 3
#define PACIFICA 4
#define CHASE_XMAS 5
#define FIRE2012 6
#define MAX_POWER_MILLIAMPS 500
#define LED_TYPE            WS2812B
#define COLOR_ORDER         GRB

const int buttonPin = 11;
const int potPin = A3;

CRGB leds[NUM_LEDS];
uint8_t gBrightness = 250;
int potVal = 0;
int modeChanges = 0;
int mode = CHASE;
int buttonState;
int lastButtonState = LOW;
int count = 0;
unsigned long lastDebounceTime = 0;  // the last time the output pin /Users/dave/code/arduino-sketches/src/oneringlamp/roatatingModes.inowas toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Initialize all the mode classes
Chase chase(15, NUM_LEDS);
Chase chaseXmas(30, NUM_LEDS);
Fire2012 fire2012(NUM_LEDS);
Pacifica pacifica(NUM_LEDS);

void setup() {
  delay( 3000 );
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);

  // Start all the mode classes
  chase.start(leds, CRGB::DarkGoldenrod, CRGB::Black);
  chaseXmas.start(leds, CRGB::Red, CRGB::Green);
  fire2012.start(leds);
  pacifica.start(leds);
}

void loop() {
  checkMode();
  gBrightness = analogRead(potPin) / 4;
  resetBrightnessFactor();
  switch (mode) {
    case CHASE:
      chase.advance(count);
      break;
    case CHASE_XMAS:
      chaseXmas.advance(count);
      break;
    case BLINK:
      blink();
      break;
    case SOLID:
      solid(CRGB::Red);
      break;
    case PULSE:
      pulse();
      break;
    case PACIFICA:
      pacifica.loop();
      break;
    case FIRE2012:
      fire2012.loop();
      break;
    default:
      leds[30] = CRGB::Yellow;
      // mode = SOLID;
      // solid();
  }
  FastLED[0].showLeds(gBrightness * brightnessFactor);
  count++;
  delay(DELAY);
}

void checkMode() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is LOW
      if (buttonState == LOW) {
        modeChanges++;
        mode = getMode();
        setAllLeds(CRGB::Black);
      }
    }
  }
  lastButtonState = reading;
}

void resetBrightnessFactor() {
  if (mode != PULSE) {
    brightnessFactor = 1;
  }
}

int getMode() {
  return modeChanges % NUM_MODES;
}

void solid(CRGB::HTMLColorCode color) {
  setAllLeds(color);
}

void blink(int count) {
  
  if (count%2 == 0) {
    setAllLeds(CRGB::Blue);
  } else {
    setAllLeds(CRGB::Black);
  }
}

void pulse(int count) {
  setAllLeds(CRGB::DarkGoldenrod);
  brightnessAdjustment = ((count%10 > 5) - 10)/10
  
  brightnessFactor = brightnessFactor * brightnessAdjustment
}

void setAllLeds(CRGB::HTMLColorCode color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
}
void purple() {
  setAllLeds(CRGB::Purple);
}
