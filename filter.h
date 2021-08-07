#pragma once

#include <FastLED.h>

class filter
{
  public:
  virtual ~filter(){};

  virtual bool update( CRGB* leds ) = 0;
 
};

 
