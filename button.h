#pragma once

namespace
{
  enum PRESS_TIMES
  {
    SHORT = 50,
    LONG = 1100
  };
}

enum LONG_PRESS_BEHAVIOUR
{
  DIRECT,
  ON_RELEASE,
  CONTINUOUS,
};

typedef void (* functor) ();

class button
{
  public:
  
  button( int                  pin,
          functor              short_functor,
          functor              long_functor,
          LONG_PRESS_BEHAVIOUR behaviour = ON_RELEASE )
  : m_pin( pin )
  , m_short_functor( short_functor )
  , m_long_functor( long_functor )
  , m_behaviour( behaviour )
  , m_active( false )
  , m_short_active( false )
  , m_long_active( false )
  , m_timer( 0 )
  {
  }

  void update()
  {
    if( digitalRead( m_pin ) == HIGH )
    {
      if( m_active == false )
      {
        m_active = true;
        m_timer = millis();
      }

      if( detect_short() )
      {
        m_short_active = true;
      }
    
      if( detect_long() )
      {
        m_long_active = true;

        do_long_functor( );
      }
    }
  
    else
    {
      if( m_active == true )
      {
        m_active = false;
        
        if( m_long_active == true )
        {
          m_long_active = false;
          m_short_active = false;
        
          do_long_functor( );
        }
        else if( m_short_active == true )
        {
          m_short_active = false;
        
          if( m_short_functor != NULL )
          {
            m_short_functor();
          }
        }
      }
    }
  }

  private:

  int m_pin;
  functor m_short_functor;
  functor m_long_functor;

  LONG_PRESS_BEHAVIOUR m_behaviour;
  
  bool m_active;
  bool m_short_active;
  bool m_long_active;

  long m_timer;  

  bool detect_short()
  {
    return ( millis() - m_timer > SHORT ) &&
           ( m_short_active == false );
  }

  bool detect_long()
  {
    return ( millis() - m_timer > LONG ) &&
           ( m_long_active == false );
  }

  void do_long_functor()
  {
    switch( m_behaviour )
    {
      case DIRECT:
        if( m_active )
        {
          m_long_functor();  
        }
      break;
      
      case ON_RELEASE:
        if( !m_active )
        {
          m_long_functor();
        }
      break;
      
      case CONTINUOUS:
        if( m_active )
        {
          m_long_functor(); 
          
          m_timer = millis();
          m_long_active = false;
        }
      break;
    }
  }
};  
