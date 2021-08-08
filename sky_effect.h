#pragma once

#include <FastLED.h>
#include "Arduino.h"

#include "effect.h"
#include "config.h"

#define NUM_STARS 200

namespace 
{
struct star
{
  int intensity;

  int pos;  

  bool dir;
};
}

star stars[ NUM_STARS ];

class sky_effect : public effect
{
  public:  
  sky_effect( CRGB* leds )
  : m_leds( leds )
  {
    init();
  }

  void init()
  {
    for( int i = 0; i < NUM_STARS; i++ )
    {
      stars[i].intensity = random( 255 );
      stars[i].pos = random( config::NUM_LEDS );
      stars[i].dir = ( random( 2 ) == 0 ? true : false );
    } 
  }

  void update()
  {
    for( int i = 0; i < config::NUM_LEDS; ++i )
    {
      m_leds[i] = CRGB::Black;
    } 
    
    for( int i = 0; i < NUM_STARS; ++i )
    {
      if( stars[i].dir )
      {
        if( stars[i].intensity == 255 )
        {
          stars[i].dir = false;

          stars[i].intensity--;
        }

        stars[i].intensity++;
      }
      else
      {
        if( stars[i].intensity == 0 )
        {
          stars[i].dir = true;

          stars[i].intensity++;
        }

        stars[i].intensity--;  
      }
      
      m_leds[ stars[i].pos ] = CRGB( stars[i].intensity,
                                     stars[i].intensity,
                                     stars[i].intensity );                                     
    }

     
  }

  private:

  CRGB* m_leds;
};

 
