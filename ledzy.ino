#include "button.h"
#include "light.h"
#include "config.h"

light l1;

void light_on()
{
  if( l1.get_mode() != light::ON )
  {
    l1.on();
  }
  else
  {
    l1.off();
  }
}

void light_off()
{
  l1.off();
}

void shift_light_effect()
{
  l1.mode();
}

button b1( config::B1_PIN, light_on, light_off, DIRECT );
button b2( config::B2_PIN, shift_light_effect, shift_light_effect, CONTINUOUS );

void setup()
{
  Serial.begin( 9600 );

  pinMode( config::B1_PIN, INPUT_PULLUP );
  pinMode( config::B2_PIN, INPUT_PULLUP );

  light_off();
}

void loop()
{
  b1.update();
  b2.update();

  l1.update();
}
