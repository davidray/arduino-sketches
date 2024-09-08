#ifndef Pacifica_h
#define Pacifica_h
#include "Arduino.h"
#include <FastLED.h>

class Pacifica
{
public:
  Pacifica(int numLeds);
  void start(CRGB *leds);
  void loop();

private:
  int _numLeds;
  int _count;
  CRGB *_leds;
  void pacifica_one_layer(CRGBPalette16 &p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff);
  void pacifica_add_whitecaps();
  void pacifica_deepen_colors();
};
#endif