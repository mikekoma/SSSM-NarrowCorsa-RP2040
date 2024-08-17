#include <arduino.h>
#include "config.h"
#include "board.h"
#include "IxKeyMatrix.h"
#include "keycodes.h"

#if DEBUG_EMULATE_IOEXPANDER
#define OFF_ALL 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
#define ON_1 (0xFFFF ^ BIT_C2), 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
#define ON_2 0xFFFF, (0xFFFF ^ BIT_C2), 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
uint16_t emu_bits[] = {
  //
  OFF_ALL,  //L
  OFF_ALL,  //R
  OFF_ALL,  //L
  ON_1,     //R
  OFF_ALL,  //L
  ON_1,     //R
  OFF_ALL,  //L
  ON_2,     //R
  OFF_ALL,  //L
  ON_2,     //R
  OFF_ALL,  //L
  OFF_ALL,  //R
  OFF_ALL,  //L
  OFF_ALL,  //R
};
int emu_bits_index = 0;
uint16_t emu_bit;

#define IO_BEGIN(x, y) \
  DBGOUT("IO_BEGIN(ADR="); \
  DBGOUT(x); \
  DBGOUT(",DIR="); \
  DBGOUTHEX(y); \
  DBGPUTS(")");
#define IO_OUT(x) \
  DBGOUT("IO_OUT("); \
  DBGOUTHEX(x); \
  DBGOUT(") ");
#define IO_IN() \
  emu_bit = emu_bits[emu_bits_index]; \
  DBGOUT("IO_IN("); \
  DBGOUT(emu_bits_index); \
  DBGOUT(")="); \
  DBGOUTHEX(emu_bit); \
  DBGPUTS(""); \
  emu_bits_index++; \
  if (emu_bits_index >= (sizeof(emu_bits) / sizeof(uint16_t))) emu_bits_index = 0
#else
#define IO_BEGIN(x, y) ioexpander.begin(x, y)
#define IO_OUT(x) ioexpander.output(x)
#define IO_IN() ioexpander.input()
#endif

//====================================================================================
//====================================================================================
// IxKeyMatrix
//====================================================================================
//====================================================================================

//====================================================================================
// begin
//====================================================================================
void IxKeyMatrix::begin(uint8_t adr, uint8_t* key_map) {
  // -----------------------------------------------------
  // IOエクスパンダ初期化
  // -----------------------------------------------------
  IO_BEGIN(adr, BIT_DIR_IN);

  // -----------------------------------------------------
  // マスク生成
  // -----------------------------------------------------
  col_mask = 0;
  for (int i = 0; i < NUM_MATRIX_COLS; i++) {
    col_mask |= col_bits[i];
  }

  // -----------------------------------------------------
  // keymap
  // -----------------------------------------------------
  keymap = key_map;

  // -----------------------------------------------------
  // 変数初期化
  // -----------------------------------------------------
  for (int i = 0; i < BITMAP_BIT_NUM; i++) {
    bitmap_raw[i] = 0;
    bitmap_input_before[i] = 0;
    bitmap_settle[i] = 0;
  }

  millis_start = 0;
}

//====================================================================================
// end
//====================================================================================
void IxKeyMatrix::end() {
  IO_OUT(0xFFFF);
}

//====================================================================================
// update
//====================================================================================
void IxKeyMatrix::update() {
  update_bitmap_raw();

  if (bitmap_is_stable()) {
    send_key();
  }
}

//************************************************************************************
// bit_to_key
//************************************************************************************
uint8_t IxKeyMatrix::bit_to_key(int bit_no) {
  DBGOUT("bit_to_key ");
  DBGOUT(bit_no);
  DBGOUT(" -> ");
  uint8_t key;
  if (bit_no < KEYMAP_SIZE) {
    key = keymap[bit_no];
  } else {
    key = KC_NONE;
  }
  DBGPUTS(key);
  return key;
}

//************************************************************************************
// update_bitmap_raw
//************************************************************************************
// マトリクス駆動して、bitmap_rawを更新する
void IxKeyMatrix::update_bitmap_raw() {
  for (int i = 0; i < NUM_MATRIX_ROWS; i++) {
    //-------------------------------------------
    // drive row
    //-------------------------------------------
    uint16_t bit_out = row_bits[i];  // low active。1ビットのみL
    IO_OUT(bit_out);
    delayMicroseconds(100);
#if DEBUG_CHECK_RAW
    DBGOUTHEX(~bit_out);  // hi active
    DBGOUT(F("->"));
#endif
    //-------------------------------------------
    // read column
    //-------------------------------------------
    uint16_t bits = (~IO_IN()) & col_mask;  // IO_IN()はlow active、bitsはhigh active
    bitmap_raw[i] = bits;                   // IO is low active. bitmap_raw is high active.

#if DEBUG_CHECK_RAW
    DBGOUTHEX(bits);  // hi active
    DBGOUT(F("  "));
#endif
  }

#if DEBUG_CHECK_RAW
  DBGPUTS("");
#endif
}

//************************************************************************************
// bitmap_is_stable
//************************************************************************************
bool IxKeyMatrix::bitmap_is_stable() {
  // 前回のbitmap_rawと変化があるか確認する
  bool changed = false;
  for (int i = 0; i < BITMAP_BIT_NUM; i++) {
    changed |= bitmap_raw[i] ^ bitmap_input_before[i];
    bitmap_input_before[i] = bitmap_raw[i];
  }

  if (changed) {
    millis_start = millis();
    return false;  // 変化有り
  } else if ((millis() - millis_start) < DEBOUNCING_DELAY) {
    return false;  // 変化はないが、安定期間が経過するのを待つ
  }

  return true;  //安定した
}

//************************************************************************************
// send_key
//************************************************************************************
//bitmap_rawの変化からキーを発行する
void IxKeyMatrix::send_key() {
  //------------------------------------------------------------
  // プレス・リリースをキーごとに発行する
  //------------------------------------------------------------
  int raw_no = 0;
  for (int index_row = 0; index_row < NUM_MATRIX_ROWS; index_row++) {
    // ビットの変化あるか？
    uint16_t changed_bits = bitmap_raw[index_row] ^ bitmap_settle[index_row];
    for (int index_col = 0; index_col < NUM_MATRIX_COLS; index_col++) {
      uint16_t bit_mask = col_bits[index_col];
      if (changed_bits & bit_mask)  // ビット変化あればキー発行
      {
        bool is_press = (bool)(bitmap_raw[index_row] & bit_mask);
        uint8_t key_code = bit_to_key(raw_no);

        if (is_press) {
          KEY_PRESS(key_code);  //プレス
        } else {
          KEY_RELEASE(key_code);  //リリース
        }

      }  //changed_bits
      raw_no++;
    }  //index_col loop

    bitmap_settle[index_row] = bitmap_raw[index_row];
  }  //index_row loop
}
