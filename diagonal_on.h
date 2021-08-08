#ifndef DIAGONAL_ON_H
#define DIAGONAL_ON_H

#include "effect.h"
#include <FastLED.h>

class diagonal_on : public effect
{
  public:
  diagonal_on( CRGB* leds )
  : m_leds( leds )
  , m_index( 0 )
  {
  }

  void init()
  {
      for( int i = 0; i < 1080; ++i )
      {
          m_leds[i] = CRGB::Black;
      }
  }

  void update()
  {
    for( int i = 0; i < 5; ++i)
    {
      if( m_index >= 180 )
      {
        return;
      }
      
      if( m_index < 90 )
      {
          m_leds[m_index] = CRGB::White;
  
          m_leds[540+89-m_index] = CRGB::White;
      }
      if( ( m_index > 17) && ( m_index < (18 + 90) ) )
      {
          m_leds[180+17-m_index] = CRGB::White;
  
          m_leds[540+89-17+m_index]  = CRGB::White;
      }
      if( ( m_index > 17+18) && ( m_index < (18+18 + 90) ) )
      {
          m_leds[180-36+m_index]  = CRGB::White;
  
          m_leds[540+179-35+90+90-19-m_index] = CRGB::White;
      }
      if( ( m_index > 17+18+18) && ( m_index < (18+18+18 + 90) ) )
      {
          m_leds[360+17+36-m_index]  = CRGB::White;
  
          m_leds[540+269-17-36+m_index]  = CRGB::White;
      }
      if( ( m_index > 17+18+18+18) && ( m_index < (18+18+18+18 + 90) ) )
      {
          m_leds[360-72+m_index]  = CRGB::White;
  
          m_leds[540+359+90+90+90-36+18-17-73-m_index]  = CRGB::White;
      }
      if( ( m_index > 17+18+18+18+18) && ( m_index < (18+18+18+18+18 + 90) ) )
      {
          m_leds[540+17+72-m_index]  = CRGB::White;
  
          m_leds[90+540+180+90+m_index]  = CRGB::White;
      }
    }
    m_index++;
  }

  void reset()
  {
      init();

      m_index = 0;
  }

  private:

  CRGB* m_leds;

  unsigned int m_index;
};

#endif // DIAGONAL_ON_H
