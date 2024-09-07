#include <FastLED.h>
#define NUM_LEDS 64
#define DATA_PIN 6
#define DELAY 100
#define LAST_MODE 3
#define CHASE 0
#define BLINK 1
#define SOLID 2
#define PULSE 3

const int buttonPin = 12;
const int potPin = A3;

CRGB leds[NUM_LEDS];
uint8_t gBrightness = 250;
int potVal = 0;
int mode = PULSE;
int buttonState;
int lastButtonState = LOW;
int blinkOn = true;
int dot = 0;
double brightnessFactor = 1.0;
double brightnessFactorStep = 0.1;
int brightnessUp = false;

unsigned long lastDebounceTime = 0;  // the last time the output pin /Users/dave/code/arduino-sketches/src/oneringlamp/roatatingModes.inowas toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  delay( 3000 );
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(buttonPin, INPUT);
}

void loop() {
  checkMode();
  gBrightness = analogRead(potPin) / 4;
  resetBrightnessFactor();
  switch (mode) {
    case CHASE:
      chase();
      break;
    case BLINK:
      blink();
      break;
    case SOLID:
      solid();
      break;
    case PULSE:
      pulse();
      break;
    default:
      mode = SOLID;
      solid();
  }
  FastLED[0].showLeds(gBrightness * brightnessFactor);
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

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        mode = bumpMode(mode);
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

int bumpMode(int mode) {
  if (mode < LAST_MODE) {
    return mode + 1;
  }
  return 0;
}

void solid() {
  setAllLeds(CRGB::Red);
}

void blink() {
  if (blinkOn) {
    setAllLeds(CRGB::Blue);
  } else {
    setAllLeds(CRGB::Black);
  }
  blinkOn = !blinkOn;
}

void pulse() {
  setAllLeds(CRGB::DarkGoldenrod);
  if (brightnessUp) {
    brightnessFactor = brightnessFactor + brightnessFactorStep;
  } else {
    brightnessFactor = brightnessFactor - brightnessFactorStep;
  }
  if (brightnessFactor < -0.4) {
    brightnessUp = true;
  } else if (brightnessFactor > 1.0) {
    brightnessUp = false;
  }
}

void setAllLeds(CRGB::HTMLColorCode color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
}
void purple() {
  setAllLeds(CRGB::Purple);
}

void chase() {
  int width = 20;
  int speed = 6;

  int offDot = dot;
  leds[dot] = CRGB::Black;

  for (int i = 0; i < speed; i++) {
    leds[offDot] = CRGB::Black;
    offDot = nextDot(offDot);
    dot = nextDot(dot);
  }

  int onDot = dot;
  for (int i = 0; i < width; i++) {
    leds[onDot] = CRGB::Red;
    onDot = nextDot(onDot);
  }
}

int prevDot(int dot) {
  if (dot > 0) {
    return dot - 1;
  }
  return 59;
}

int nextDot(int dot) {
  if (dot < NUM_LEDS) {
    return dot + 1;
  }
  return 0;
}
