#include <Wire.h>
#include <Time.h>
#include <DS1302RTC.h>
#include <LiquidCrystal.h>
#include <godob.h>

godob GD(11,3,2,8,9,4,5,6,7,10);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  GD.begin();
}

void loop() {
  GD.run();
}

