#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(30, 0, NEO_GRB + NEO_KHZ800);

const int buttonPin = 1;
int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  strip.begin();
  strip.show();
  strip.setBrightness(30);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);

  if(buttonState == 1) 
    strip.setPixelColor(0,0,255,0);
  else
    strip.setPixelColor(0,255,0,0);
  strip.show();
}
