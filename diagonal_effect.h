#ifndef DIAGONAL_EFFECT_H
#define DIAGONAL_EFFECT_H

#include "effect.h"
#include <FastLED.h>

class diagonal_effect : public effect
{
  public:
  diagonal_effect( CRGB color, CRGB* leds )
  : m_color( color )
  , m_leds( leds )
  , m_index( 0 )
  {
  }

  void update()
  {
    for( int i = 0; i < 20; ++i)
    {
      if( m_index >= 180 )
      {
        return;
      }
      
      if( m_index < 90 )
      {
          m_leds[m_index] = m_color;
  
          m_leds[540+89-m_index] = m_color;
      }
      if( ( m_index > 17) && ( m_index < (18 + 90) ) )
      {
          m_leds[180+17-m_index] = m_color;
  
          m_leds[540+89-17+m_index]  = m_color;
      }
      if( ( m_index > 17+18) && ( m_index < (18+18 + 90) ) )
      {
          m_leds[180-36+m_index]  = m_color;
  
          m_leds[540+179-35+90+90-19-m_index] = m_color;
      }
      if( ( m_index > 17+18+18) && ( m_index < (18+18+18 + 90) ) )
      {
          m_leds[360+17+36-m_index]  = m_color;
  
          m_leds[540+269-17-36+m_index]  = m_color;
      }
      if( ( m_index > 17+18+18+18) && ( m_index < (18+18+18+18 + 90) ) )
      {
          m_leds[360-72+m_index]  = m_color;
  
          m_leds[540+359+90+90+90-36+18-17-73-m_index]  = m_color;
      }
      if( ( m_index > 17+18+18+18+18) && ( m_index < (18+18+18+18+18 + 90) ) )
      {
          m_leds[540+17+72-m_index]  = m_color;
  
          m_leds[90+540+180+90+m_index]  = m_color;
      }
    }
    m_index++;
  }

  void reset()
  {
      m_index = 0;
  }

  private:

  CRGB m_color;

  CRGB* m_leds;

  unsigned int m_index;
};

#endif // DIAGONAL_EFFECT_H
