#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include "config.h"
#include "board.h"
#include "IxKeyMatrix.h"

IxKeyMatrix KeyMatrixLeft;
IxKeyMatrix KeyMatrixRight;

//===============================================================
// setup
//===============================================================
void setup() {
  //-----------------------------------------------
  // Serial
  //-----------------------------------------------
  Serial.begin(115200);

  //-----------------------------------------------
  // I2C
  //-----------------------------------------------
  Wire.begin();
  Wire.setClock(100000);

  //-----------------------------------------------
  // Keyboard
  //-----------------------------------------------
  KEY_INIT();  // USB keyboard

  // Left
  KeyMatrixLeft.begin(PCA9555_ADDR_LEFT, keymap_left);

  // Right
  KeyMatrixRight.begin(PCA9555_ADDR_RIGHT, keymap_right);

  //-----------------------------------------------
  // blink built in LED
  //-----------------------------------------------
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
  }
}

//===============================================================
// loop
//===============================================================
void loop() {
  KeyMatrixLeft.update();
  KeyMatrixRight.update();
}