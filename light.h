#pragma once

#include "Arduino.h"
#define FASTLED_INTERNAL
#include <FastLED.h>

#include "fire_effect.h"
#include "sky_effect.h"
#include "pingpong_effect.h"
#include "fade_filter.h"
#include "sin_filter.h"
#include "diagonal_on.h"

#include "config.h"

#define COLOR_ORDER GRB
#define CHIPSET     WS2812B

#define BRIGHTNESS  100

CRGB leds[ config::NUM_LEDS ];

#define NUM_EFFECTS 3

effect* effects[ NUM_EFFECTS ];

class light
{
public:

  enum LIGHT_MODE
  {
    ON = 0,
    OFF,
    EFFECT,
  };  

  light()
  : m_mode( OFF )
  , m_request_mode( OFF )
  , m_on_effect( leds )
  , m_current_effect( -1 )
  , m_timer( 0 )
  {        
    FastLED.addLeds<CHIPSET, config::LED_PIN, COLOR_ORDER>( leds, config::NUM_LEDS ).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness( BRIGHTNESS );

    setup_effects();
  }

  void setup_effects()
  {
    effects[ 0 ] = new fire_effect( leds );
    effects[ 1 ] = new sky_effect( leds );
    effects[ 2 ] = new pingpong_effect( leds );
  }

  void on()
  {
    m_request_mode = ON;  
  }

  void off()
  {
    m_request_mode = OFF;
  }

  void mode()
  {
    m_request_mode = EFFECT;
    
    m_current_effect++;

    if( m_current_effect == NUM_EFFECTS )
    {
      m_current_effect = 0;
    }
  }

  LIGHT_MODE get_mode()
  {
    return m_mode;
  }

  void update()
  {    
    if( millis() - m_timer < config::UPDATE_MS )
    {
      return;
    }

    m_timer = millis();

    switch( m_mode )
    {
      case ON:
        do_on();
      break;

      case OFF:
        do_off();
      break;

      case EFFECT:
        do_effect();
      break;
    }
  }

private:
  
  LIGHT_MODE m_mode;
  LIGHT_MODE m_request_mode;

  diagonal_on m_on_effect;
  
  int m_current_effect;
  
  int m_timer;

  void do_on()
  {    
    static bool on_entry = true;
    
    if( on_entry )
    {
      on_entry = false;  

      m_mode = ON;

      m_on_effect.reset();
    }

    if( m_request_mode == OFF )
    {
      m_mode = OFF;
      on_entry = true;
      m_on_effect.reset();
      return;
    }
    else if( m_request_mode == EFFECT )
    {
      m_mode = EFFECT;
      on_entry = true;
      return;
    }

    m_on_effect.update();
  
    FastLED.show();
  }

  void do_off()
  {    
    static bool on_entry = true;
    
    if( on_entry )
    {
      on_entry = false;  

      m_mode = OFF;

      set_all_leds( CRGB::Black );

      FastLED.show();
    }

    if( m_request_mode == ON )
    {
      m_mode = ON;
      on_entry = true;
      return;
    }
    else if( m_request_mode == EFFECT )
    {
      m_mode = EFFECT;
      on_entry = true;
      return;
    }
  }

  void do_effect()
  {    
    static bool on_entry = true;
    
    if( on_entry )
    {
      on_entry = false;  

      m_mode = EFFECT;
    }

    if( m_request_mode == ON )
    {
      m_mode = ON;
      on_entry = true;
      return;
    }
    else if( m_request_mode == OFF )
    {
      m_mode = OFF;
      on_entry = true;
      return;
    }

    effects[ m_current_effect ]->update();

    FastLED.show();
  }

  void set_all_leds( const CRGB& color )
  {
    for( int i( 0 ); i < config::NUM_LEDS; ++i )
    {
        leds[ i ] = color;
    }
  }
};
