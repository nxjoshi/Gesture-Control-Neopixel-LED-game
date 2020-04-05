#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "paj7620.h"

#define LED_COUNT 60
#define LED_PIN 2

int i = 0;
int j = 0;
int k = 9;
int num;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  uint8_t error = 0;
  Serial.begin(9600);
  Serial.println("\nPAJ7620U2 gesture Game");
  error = paj7620Init();      // initialize Paj7620 registers
  if (error)
  {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  }
  else
  {
    Serial.println("INIT OK");
  }
  Serial.println("Please input your gestures:\n");

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  boxWipe(strip.Color(0, 0, 50));
  randomSeed(analogRead(14));
}

void loop()
{
  uint8_t data = 0, error;

  error = paj7620ReadReg(0x43, 1, &data);       // Read Bank_0_Reg_0x43/0x44 for gesture result.
  if (!error)
  {
    switch (data)                   // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
    {
      case GES_RIGHT_FLAG:
        Serial.println("Right");
        right();
        delay(1000);
        break;
      case GES_LEFT_FLAG:
        Serial.println("Left");
        left();
        delay(1000);
        break;
      case GES_UP_FLAG:
        Serial.println("Up");
        up();
        delay(2000);
        break;
      case GES_DOWN_FLAG:
        Serial.println("Down");
        down();
        delay(1000);
        break;
      case GES_CLOCKWISE_FLAG:
        Serial.println("Clockwise");
        clockwise();
        delay(1000);
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        Serial.println("anti-clockwise");
        anticlockwise();
        delay(1000);
        break;
    }
  }
  delay(100);
}

void left() {
  i = 0;
  j = 0;
  k = 9;
  for (int n = 0; n < 60; n++) {
    strip.setPixelColor(random(60), strip.Color(0, 100, 0));
    strip.show();
    delay(50);
    strip.clear();
    strip.show();
  }
  num = random(60);
  Serial.println(num);
  strip.setPixelColor(num, strip.Color(0, 100, 0));
  strip.show();
}

void right() {
  if (j * 10 + k == num) {
    for (int m = 0; m < 4; m++) {
      for (int n = 0; n < strip.numPixels(); n++) {
        strip.setPixelColor(n, strip.Color(0,  50, 0));
      }
      strip.show();
      delay(500);
      strip.clear();
      strip.show();
      delay(500);
    }
  }
  else {
    for (int m = 0; m < 3; m++) {
      for (int n = 0; n < strip.numPixels(); n++) {
        strip.setPixelColor(n, strip.Color(50,  0, 0));
      }
      strip.show();
      delay(500);
      strip.clear();
      strip.show();
      delay(500);
    }
  }
}

void down() {
  strip.clear();
  if (k > 0) k = k - 1;
  else k = 9;
  strip.setPixelColor(j * 10 + k, strip.Color(0,  0, 50));
  strip.show();
}

void up() {
  strip.clear();
  if (k < 9) k = k + 1;
  else k = 0;
  strip.setPixelColor(j * 10 + k, strip.Color(0,  0, 50));
  strip.show();
}

void clockwise() {
  strip.clear();
  if (j < 5) j = j + 1;
  else j = 0;
  for (i = 0; i < k+1; i++) {
    strip.setPixelColor(j * 10 + i, strip.Color(0,  0, 50));
  }
  strip.show();
}


void anticlockwise() {
  strip.clear();
  if (j > 0) j = j - 1;
  else j = 5;
  for (i = 0; i < k+1; i++) {
    strip.setPixelColor(j * 10 + i, strip.Color(0,  0, 50));
  }
  strip.show();
}

void boxWipe(uint32_t color) {
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 6; i++) {
      strip.setPixelColor(i * 10 + 0, color);
      strip.setPixelColor(i * 10 + 1, color);
      strip.setPixelColor(i * 10 + 2, color);
      strip.setPixelColor(i * 10 + 3, color);
    }
    strip.show();
    delay(100);
    strip.clear();
    for (int i = 0; i < 6; i++) {
      strip.setPixelColor(i * 10 + 4, color);
      strip.setPixelColor(i * 10 + 5, color);
      strip.setPixelColor(i * 10 + 6, color);
    }
    strip.show();
    delay(100);
    strip.clear();
    for (int i = 0; i < 6; i++) {
      strip.setPixelColor(i * 10 + 7, color);
      strip.setPixelColor(i * 10 + 8, color);
    }
    strip.show();
    delay(100);
    strip.clear();
    for (int i = 0; i < 6; i++) {
      strip.setPixelColor(i * 10 + 9, color);
    }
    strip.show();
    delay(100);
    strip.clear();
    for (int i = 0; i < 6; i++) {
      strip.setPixelColor(i * 10 + 7, color);
      strip.setPixelColor(i * 10 + 8, color);
    }
    strip.show();
    delay(100);
    strip.clear();
    for (int i = 0; i < 6; i++) {
      strip.setPixelColor(i * 10 + 4, color);
      strip.setPixelColor(i * 10 + 5, color);
      strip.setPixelColor(i * 10 + 6, color);
    }
    strip.show();
    delay(100);
    strip.clear();
    for (int i = 0; i < 6; i++) {
      strip.setPixelColor(i * 10 + 0, color);
      strip.setPixelColor(i * 10 + 1, color);
      strip.setPixelColor(i * 10 + 2, color);
      strip.setPixelColor(i * 10 + 3, color);
    }
    strip.show();
    delay(100);
    strip.clear();
  }
  strip.clear();
  strip.show();
}
