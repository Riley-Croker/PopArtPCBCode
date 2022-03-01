#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(30, 0, NEO_GRB + NEO_KHZ800);

const int buttonPin = 1;

boolean prevButState = false;
boolean currentButState = false;

int state = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  strip.begin();
  strip.show();
  strip.setBrightness(30);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentButState = debounce(buttonPin,prevButState);

  if(currentButState == HIGH && prevButState == LOW)
    state = (state+1) % 3;

  switch (state) {
    case 0:
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i,0,0,0);
      }
    break;
    case 1:
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i,255,0,0);
      }
    break;
    case 2:
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i,0,255,0);
      }
    break;
  }

  strip.show();

  prevButState = currentButState; 
}


boolean debounce(int buttonPin, boolean preState)
{
  boolean buttonState = digitalRead(buttonPin);
  if (buttonState != preState)
    delay(50);
  return buttonState;
}
