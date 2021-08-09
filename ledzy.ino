#include "button.h"
#include "light.h"
#include "config.h"

button* p_button_on_off;
button* p_button_mode;
light*  p_light;

void light_on()
{
  if( p_light->get_mode() != light::ON )
  {
    p_light->on();
  }
  else
  {
    p_light->off();
  }
}

void light_off()
{
  p_light->off();
}

void next_effect()
{
  p_light->mode();
}

void setup()
{
  delay( config::BOOT_DELAY_MS );
  
  Serial.begin( 9600 );

  pinMode( config::B1_PIN, INPUT_PULLUP );
  pinMode( config::B2_PIN, INPUT_PULLUP );

  p_button_on_off = new button( config::B1_PIN, light_on, light_off, DIRECT );
  p_button_mode = new button( config::B2_PIN, next_effect, next_effect, CONTINUOUS );

  p_light = new light();
}

void loop()
{
  p_button_on_off->update();
  p_button_mode->update();
  
  p_light->update();
}
