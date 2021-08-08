#pragma once

#include "filter.h"
#include "config.h"

class fade_filter : public filter
{
  public:  

  fade_filter( int steps, bool dir_up )
  : m_steps( steps )
  , m_dir_up( dir_up )
  , m_iterations( 0 )
  , m_step( 0.0 )
  , m_delta( 1.0 / m_steps )
  {
    init();
  }

  bool update( CRGB* leds )
  {
    m_iterations++;
    
    for( int i( 0 ); i < config::NUM_LEDS; ++i )
    {
      fade( leds[ i ] );
    }

    if( m_dir_up )
    {
      m_step += m_delta;
    }
    else
    {
      m_step -= m_delta;
    }
    
    return ( m_iterations == m_steps );
  }

  void reset()
  {
    init();
    
    m_iterations = 0;
  }

  private:

  int m_steps;

  bool m_dir_up;
  
  int m_iterations;

  float m_step;

  float m_delta;

  void init()
  {
    m_dir_up ? m_step = 0.0 : m_step = 1.0;

    m_delta = 1.0 / m_steps;
  }

  void fade( CRGB& color )
  {
    color.red *= m_step;
    color.green *= m_step;
    color.blue *= m_step;  
  }
};

 
