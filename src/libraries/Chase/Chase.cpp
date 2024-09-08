#include "Arduino.h"
#include "Chase.h"
#include <FastLED.h>

Chase::Chase(int speed, int numLeds)
{
  _speed = speed;
  _numLeds = numLeds;
}

void Chase::start(CRGB *leds, CRGB::HTMLColorCode onColor, CRGB::HTMLColorCode offColor)
{
  _leds = leds;
  _pdot = 0;
  _onColor = onColor;
  _offColor = offColor;
}

void Chase::advance(int count)
{
  int _dot = count % _numLeds;
  _leds[_dot] = _offColor;
  _pdot = nextDot(count);
  _leds[_pdot] = _onColor;
}

int Chase::nextDot(int count)
{
  return (count + _speed) % _numLeds;
}