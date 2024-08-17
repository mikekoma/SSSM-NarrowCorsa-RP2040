/*
  # File
  PCA9555.cpp

  # Version
  1.0.0

  # Target device
  NXP PCA9555

  # Author
  Suns & Moon Laboratory
  https://www.s-m-l.org
*/
#include <Arduino.h>
#include <Wire.h>
#include "PCA9555.h"

#define REG_INPUT 0x00
#define REG_OUTPUT 0x02
#define REG_POLARITY 0x04
#define REG_CONFIG 0x06

//==========================================================================
// begin
//==========================================================================
// dir_init 1:input, 0:output
void PCA9555::begin(uint8_t adr, uint16_t dir_init) {
  DeviceAddress = adr;

  //-----------------------------------
  // 入出力方向設定
  //-----------------------------------
  uint8_t dat[2];
  dat[0] = dir_init;
  dat[1] = dir_init >> 8;
  writeDevice(REG_CONFIG, dat, 2);

  //-----------------------------------
  // 極性
  //-----------------------------------
#if 0
  dat[0] = 0x00;
  dat[1] = 0x00;
  writeDevice(REG_POLARITY, dat, 2);
#endif
}

//==========================================================================
// writeDevice
//==========================================================================
void PCA9555::writeDevice(uint8_t reg, uint8_t *buf, int datasize) {
  Wire.beginTransmission(DeviceAddress);
  Wire.write(reg);
  for (int i = 0; i < datasize; i++) {
    Wire.write(buf[i]);
  }
  Wire.endTransmission();
}

//==========================================================================
// readDevice
//==========================================================================
void PCA9555::readDevice(uint8_t reg, uint8_t *buf, int datasize) {
  Wire.beginTransmission(DeviceAddress);
  Wire.write(reg);
  //  Wire.endTransmission(false); // continuous
  Wire.endTransmission();  // continuous

  //  Wire.requestFrom(DeviceAddress, datasize, false);
  Wire.requestFrom(DeviceAddress, datasize);

  for (int i = 0; i < datasize; i++) {
    buf[i] = Wire.read();
  }

  Wire.endTransmission(true);
}

//==========================================================================
// output
//==========================================================================
void PCA9555::output(uint16_t val) {
  uint8_t buf[2];
  buf[0] = val;
  buf[1] = val >> 8;
  writeDevice(REG_OUTPUT, buf, sizeof(buf));
}

//==========================================================================
// input
//==========================================================================
uint16_t PCA9555::input() {
  uint8_t buf[2];
  readDevice(REG_INPUT, buf, sizeof(buf));
  uint16_t val;
  val = (((uint16_t)buf[1]) << 8) | buf[0];
  return val;
}
