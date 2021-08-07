#include "button.h"
#include "light.h"

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

button b1( 30, light_on, light_off, DIRECT );
button b2( 31, shift_light_effect, shift_light_effect, CONTINUOUS );

void setup()
{
  Serial.begin(9600);

  pinMode( 30, INPUT_PULLUP );
  pinMode( 31, INPUT_PULLUP );

  light_off();
}

void loop()
{
  b1.update();
  b2.update();

  l1.update();
}
