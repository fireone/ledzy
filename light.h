#pragma once

#include "Arduino.h"
#include <FastLED.h>
#include <ArduinoSTL.h>

#include "fire_effect.h"
#include "sky_effect.h"
#include "pingpong_effect.h"
#include "fade_filter.h"
#include "sin_filter.h"

#include "config.h"

#define COLOR_ORDER GRB
#define CHIPSET     WS2812B

#define BRIGHTNESS  100

CRGB leds[ config::NUM_LEDS ];

class light
{
public:

  enum LIGHT_MODE
  {
    ON,
    OFF,
    EFFECT
  };  

  light()
  : m_mode( OFF )
  , m_effects()
  , m_prev_effect( -1 )
  , m_current_effect( -1 )
  , m_timer( 0 )
  {        
    FastLED.addLeds<CHIPSET, config::LED_PIN, COLOR_ORDER>( leds, config::NUM_LEDS ).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness( BRIGHTNESS );

    m_effects.push_back( new fire_effect( leds ) );
    m_effects.push_back( new sky_effect( leds ) );
    m_effects.push_back( new pingpong_effect( leds ) );
  }

  void on()
  {
    m_mode = ON;  
    
    Serial.println( "TURN_ON" );

    do_on();
  }

  void off()
  {
    m_mode = OFF;

    Serial.println( "TURN_OFF" );
    
    do_off();
  }

  void mode()
  {
    if( m_mode == ON || m_mode == OFF )
    {
      m_prev_effect = -1;  
    }
    else
    {
      m_prev_effect = m_current_effect;      
    }
    
    m_mode = EFFECT;
    
    m_current_effect++;

    if( m_current_effect == m_effects.size() )
    {
      m_current_effect = 0;
    }

    Serial.println( static_cast<int>( m_current_effect ) ); 
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

  std::vector<effect*> m_effects;
  
  int m_prev_effect;
  int m_current_effect;
  
  int m_timer;

  void do_on()
  {    
    static bool on_entry = true;
    
    if( on_entry )
    {
      on_entry = false;  
    }
  }

  void do_off()
  {    
    static bool on_entry = true;
    
    if( on_entry )
    {
      on_entry = false;  
    }
  }

  void do_effect()
  {    
    static bool on_entry = true;
    
    if( on_entry )
    {
      on_entry = false;  
    }
    
    m_effects[ m_current_effect ]->update();

    FastLED.show();
  }

  void set_all_leds( const CRGB& color )
  {
    for( int i( 0 ); i < config::NUM_X_LEDS; ++i )
    {
      for( int j( 0 ); j < config::NUM_Y_LEDS; ++j )
      { 
        leds[ i * config::NUM_Y_LEDS + j ] = color;
      } 
    }
  }
};
