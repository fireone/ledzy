#pragma once

#include <FastLED.h>
#include "Arduino.h"

#include "effect.h"
#include "config.h"

class pingpong_effect : public effect
{
  public:  
  pingpong_effect( CRGB* leds )
  : m_leds( leds )
  , m_pos( 3 )
  , m_dir( false )
  {
  }

  void update()
  {
    for( int i = 0; i < config::NUM_LEDS; i++)
    {
      m_leds[i] = CRGB::Black;
    } 

    if( m_dir )
    {
      if( m_pos == config::NUM_LEDS - 1 )
      {
        m_dir = false;
        m_pos--;
      }
      else
        m_pos++;
    }
    else
    {
      if( m_pos == 0 )
      {
        m_dir = true;
        m_pos++;
      }
      else
        m_pos--;  
    }

    m_leds[ m_pos ] = CRGB::Orange;
  }

  private:

  CRGB* m_leds;

  int m_pos;

  bool m_dir;
};

 
