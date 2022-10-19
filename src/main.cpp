#include <Arduino.h>
#include <FastLED.h>

// LED strip array
#define LED_CNT 43
CRGB leds[LED_CNT];

// smoothly cycle through hue values
void rainbow()
{
  // initialized only once
  static int rainbow_h = 0;
  static int rainbow_incr = 1;

  // hue is between 0 & 360 (chromatic circle)
  // keep saturation & value fixed & cycle back & forth between hue values
  CHSV hsv(rainbow_h,255,255);
  CRGB rgb;
  hsv2rgb_rainbow(hsv,rgb);

  for (int ii=0; ii < LED_CNT; ++ii)
  {
    leds[ii] = rgb;
  }

  // go to next hue value & evaluate next direction if hitting one of the value's boundaries
  rainbow_h+=rainbow_incr*1;
  if (rainbow_h == 360) rainbow_incr = -1;
  else if (rainbow_h == 0) rainbow_incr = 1;
}

void snake()
{
  static constexpr const int hue_step=2;
  static int snake_h = 0;
  static int snake_incr = 1;

  for (int ii=0; ii < LED_CNT; ++ii)
  {
    int h=snake_h+ii;
    if (h > 360) h-=h-360;
    CHSV hsv(h,255,255);
    CRGB rgb;
    hsv2rgb_rainbow(hsv,rgb);
    leds[ii] = rgb;
  }

  snake_h+=snake_incr*1;
  if (snake_h == 360) snake_incr = -1*hue_step;
  else if (snake_h == 0) snake_incr = 1*hue_step;
}

// initial setup, executed once
void setup()
{
  // setup led strip pin & type
  FastLED.addLeds<WS2812B, 7, GRB>(leds, LED_CNT);

  // set brightness (value between 0 & 255)
  FastLED.setBrightness(255);
}

// main loop
void loop()
{
  // call the function that updates leds values
  //rainbow();
  snake();
  // commit changes to led strip
  FastLED.show();
  // pauses between calls to loop(), controls the LED animation speed
  delay(200); 
}