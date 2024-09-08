#ifndef Chase_h
#define Chase_h
#include "Arduino.h"
#include <FastLED.h>

class Chase
{
public:
  Chase(int speed, int numLeds);
  void start(CRGB *leds, CRGB::HTMLColorCode onColor, CRGB::HTMLColorCode offColor);
  void advance(int count);

private:
  int _speed;
  int _numLeds;
  int _count;
  int _dot;
  int _pdot;
  CRGB::HTMLColorCode _onColor;
  CRGB::HTMLColorCode _offColor;
  CRGB *_leds;
  int nextDot(int dot);
};
#endif