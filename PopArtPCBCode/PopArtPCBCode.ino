#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(30, 0, NEO_GRB + NEO_KHZ800);

//button stuff
const int buttonPin = 1;
boolean prevButState = false;
boolean currentButState = false;

// finite state machine
int state = 0;

// for state 2
int numGrid = 26;
int numFrames = 3;
int whichFrame = 0;
unsigned long startTime = 0;
unsigned long endTime = 0;
int inter = 1000;

//for state 1
unsigned long startTime2 = 0;
unsigned long endTime2 = 0;
int inter2 = 10;
int brightness = 1;
int flip = 1;
int redVal = 0;
int greenVal = 0;

char index[26]{
  // Insert Index Values Here
       5, 10, 15, 20, 
    1, 6, 11, 16, 21, 26,
    2, 7, 12, 17, 22, 27,
    3, 8, 13, 18, 23, 28,
       9, 14, 19, 24      
};

char colors[6][3]{
  // Create 3 Colors Here
  { 255, 0, 0 },
  { 0, 0, 0},
  { 255, 255, 255 },
  { 0, 0, 255 },
  { 255, 255, 0 },
  { 20, 20, 20 }
};

char frames[3][26]{
  // Create 2 Animation Frames Here
  {
       0, 0, 0, 0, 
    0, 0, 1, 1, 0, 0,
    1, 1, 0, 0, 1, 1,
    2, 2, 1, 1, 2, 2,
       2, 2, 2, 2  
  },
  {
       0, 3, 3, 0, 
    3, 3, 1, 1, 3, 3,
    1, 1, 3, 3, 1, 1,
    2, 2, 1, 1, 2, 2,
       2, 2, 2, 2  
  },
  {
       4, 4, 4, 4, 
    5, 4, 1, 1, 4, 5,
    1, 1, 4, 4, 1, 1,
    2, 2, 1, 1, 2, 2,
       2, 2, 2, 2  
  }
};

void setup() {
  pinMode(buttonPin, INPUT);
  strip.begin();
  strip.show();
  startTime=millis();
  startTime2=millis();
  //strip.setBrightness(30);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentButState = debounce(buttonPin,prevButState);

  if(currentButState == HIGH && prevButState == LOW) {
    strip.clear();
    state = (state+1) % 3;
    if(state == 1) {
      startTime2=millis();
      brightness = 0;
      flip=1;
    }
    if(state == 2) {
      strip.setBrightness(255);
      startTime=millis();
      whichFrame = 0;
    }
  }
  switch (state) {
    case 0:
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i,0,0,0);
      }
    break;
    case 1:
      endTime2 = millis();
      if (endTime2 - startTime2 >= inter2) {
        brightness = brightness+flip;
        if(brightness == 255 || brightness == 0) {
          flip = -flip;
        }
        startTime2 = millis();
      }
      redVal = map(brightness,0,255,255,0);
      greenVal = brightness;
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i,redVal,greenVal,0);
      }
      strip.setBrightness(brightness);
      strip.show();
    break;
    case 2:
      endTime = millis();
      if (endTime - startTime >= inter) {
        whichFrame = (whichFrame+1) % 3;
        startTime = millis();
      }
      
      for( int i = 0; i < numGrid; i++ ) {
        int whichLED = i;
        int whichIndex = index[whichLED];
        int whichColor = frames[whichFrame][whichLED];
  
        int r = colors[whichColor][0];
        int g = colors[whichColor][1];
        int b = colors[whichColor][2];
        strip.setPixelColor(whichIndex,r,g,b);
      }
      strip.show();
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
