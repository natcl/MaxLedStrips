#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    7
#define CLK_PIN   13
#define LED_TYPE    APA102
#define COLOR_ORDER GRB
#define NUM_LEDS    144
CRGB leds[NUM_LEDS];

const int numChannels = NUM_LEDS * 3;

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

char serial_array[NUM_LEDS*3];
int serial_array_length = 0;

void setup() {
  Serial.begin(115200);  
  FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  
  test();
}
  
void loop()
{
  int n = Serial.available();

  // first, check if there's anything available to read
  if (n > 0) 
  {
    // if it's more than needed, read only enough to fill the array
    if (n > numChannels - serial_array_length) n = numChannels - serial_array_length;

    // actually read the data, adding to whatever is already in the array
    Serial.readBytes(serial_array + serial_array_length, n);
    serial_array_length = serial_array_length + n;

    // then check if this filled the array and use the data
    if (serial_array_length >= numChannels)
    {
      for (int i = 0; i < NUM_LEDS ; i++)
      {
        leds[i].r = serial_array[i*3]; 
        leds[i].g = serial_array[i*3+1]; 
        leds[i].b = serial_array[i*3+2];
      }
      FastLED.show();
      serial_array_length = 0;
    }
  }
}

void test() {
  for (int i = 0; i <= NUM_LEDS; i++){
    leds[i].r = random(0,255); 
    leds[i].g = random(0,255); 
    leds[i].b = random(0,255);
    FastLED.show();
    delay(20);
    leds[i].r = 0; 
    leds[i].g = 0; 
    leds[i].b = 0;
    FastLED.show();
  } 
}
