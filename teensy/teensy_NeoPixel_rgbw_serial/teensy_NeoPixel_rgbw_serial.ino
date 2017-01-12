

/*  OctoWS2811 BasicTest.ino - Basic RGB LED Test
  Required Connections
  --------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.

  This test is useful for checking if your LED strips work, and which
  color config (WS2811_RGB, WS2811_GRB, etc) they require.
*/

#include <Adafruit_NeoPixel.h>

const int numLeds = 140;
const int numChannels = numLeds * 3;

byte pin = 17;

Adafruit_NeoPixel leds = Adafruit_NeoPixel(numLeds, pin, NEO_GRBW + NEO_KHZ800);

char serial_array[numChannels];
int serial_array_length = 0;

void setup() {
  Serial.begin(115200);
  leds.begin();
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
      for (int i = 0; i < numLeds ; i++)
        leds.setPixelColor(i, serial_array[i*4], serial_array[i*4+1], serial_array[i*4+2], serial_array[i*4+3]);

      leds.show();
      serial_array_length = 0;
    }
  }
}


void test() {
  for (int i = 0; i < numLeds ; i++){
    leds.setPixelColor(i, random(0,255), random(0,255), random(0,255), random(0,255));
    leds.show();
    delay(20);
    leds.setPixelColor(i, 0, 0, 0, 0);
    leds.show();
  }
}
