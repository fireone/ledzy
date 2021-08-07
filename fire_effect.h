#pragma once

#include <FastLED.h>
#include "Arduino.h"

#include "effect.h"
#include "config.h"

bool gReverseDirection = false;

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100 
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120


class fire_effect : public effect
{
  public:  
  fire_effect(CRGB* leds )
  : m_leds( leds )
  {
  }

  void update()
  {
    // Array of temperature readings at each simulation cell
    byte heat[ config::NUM_LEDS ];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < config::NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / config::NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k = config::NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < config::NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (config::NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      m_leds[pixelnumber] = color;
    }
  }

  private:

  CRGB* m_leds;

};

 
