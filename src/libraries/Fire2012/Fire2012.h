#ifndef Fire2_h
#define Fire2_h
#include "Arduino.h"
#include <FastLED.h>

class Fire2012
{
public:
  Fire2012(int numLeds);
  void start(CRGB *leds);
  void loop();

private:
  int _numLeds;
  CRGB *_leds;
};
#endif
