#ifndef IXKEYMATRIX_H
#define IXKEYMATRIX_H

#include <Arduino.h>
#include <stdint.h>
#include "config.h"
#include "PCA9555.h"
#include "keymap.h"

#if DEBUG_KEY_NOT_SEND
#define KEY_INIT()
#define KEY_PRESS(x) \
  DBGOUT("sendkey -> KEY_PRESS "); \
  DBGOUT(x); \
  DBGOUT("="); \
  DBGPUTS(keycode_to_txt(x))
#define KEY_RELEASE(x) \
  DBGOUT("sendkey -> KEY_RELEASE "); \
  DBGOUT(x); \
  DBGOUT("="); \
  DBGPUTS(keycode_to_txt(x))
#define KEY_RELEASE_ALL() DBGPUTS("sendkey -> KEY_RELEASE_ALL")
#else
#include <Keyboard.h>
#define KEY_INIT() Keyboard.begin()
#define KEY_PRESS(x) Keyboard.press(x)
#define KEY_RELEASE(x) Keyboard.release(x)
#define KEY_RELEASE_ALL() Keyboard.releaseAll()
#endif

class IxKeyMatrix {
protected:
  PCA9555 ioexpander;

  uint16_t col_mask;

  uint8_t* keymap;
  int keymap_size;

  unsigned long millis_start;

  // bitmap 1:on,0:off
  uint16_t bitmap_input_before[BITMAP_BIT_NUM];  // IO取り込み前回のBitmap
  uint16_t bitmap_raw[BITMAP_BIT_NUM];           // IO取り込み最新のBitmap
  uint16_t bitmap_settle[BITMAP_BIT_NUM];        // キー発行済のBitmap

  // system
  void send_key();
  bool bitmap_is_stable();
  void update_bitmap_raw();
  uint8_t bit_to_key(int bit_no);
public:
  void begin(uint8_t adr, uint8_t* key_map);
  void end();
  void update();
};

#endif  // IXKEYMATRIX_H
