/*
  # File
  PCA9555.h

  # Version
  1.0.0

  # Target device
  NXP PCA9555

  # Author
  Suns & Moon Laboratory
  https://www.s-m-l.org
*/
#ifndef PCA9555_H
#define PCA9555_H
#include <Arduino.h>
#include <stdint.h>

class PCA9555 {
private:
  uint8_t DeviceAddress;
public:
  void begin(uint8_t adr, uint16_t dir_init);

  void writeDevice(uint8_t reg, uint8_t *buf, int datasize);
  void readDevice(uint8_t reg, uint8_t *buf, int datasize);

  void output(uint16_t val);
  uint16_t input();
};

#endif
