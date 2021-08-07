#pragma once

#include "filter.h"
#include "config.h"

class sin_filter : public filter
{
  public:  

  // 50-50 inverse for now, make better filter later.
  bool update( CRGB* leds )
  {
    for( int i = 0; i < config::NUM_LEDS; i++)
    {
      if ( i % 2 == 0 )
      {
        leds[i].red   = 255 - leds[i].red;
        leds[i].green = 255 - leds[i].green;
        leds[i].blue  = 255 - leds[i].blue;
      }
    }

    return true;
  }
};

 
