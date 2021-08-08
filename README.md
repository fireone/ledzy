# ledzy

Arduino project used to control the ceiling lights in my home theatre.

![](http://www.fire1.se/wp-content/uploads/2020/11/helbild_taket-1024x683.jpg)

## Depends on

- FastLED

## Runs on

- Arduino due but should run on most arduinos. 
- The file config.h configures timing and  what pins to be used.

## Hardware used

- Arduino due
- Dual lamp switch with springs (Elko Plus 2x6-Pol)
- 1080 WS2812b ECO LEDs mounted in series in a 6x6 grid like pattern.

### Mounting pattern for the LEDs

```
+--+--+--+--+--+
|  |  |  |  |  |
+--+--+--+--+--+
|  |  |  |  |  |
+--+--+--+--+--+
|  |  |  |  |  |
+--+--+--+--+--+
|  |  |  |  |  |
+--+--+--+--+--+
|  |  |  |  |  |
+--+--+--+--+--+
```
