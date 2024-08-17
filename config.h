#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <stdint.h>

//                           01234567890123456789
#define APP_VERSION_TEXT "SSSM.NarrowCorsa 011"

//===========================================================
// ボード
//===========================================================
/*
    コンパイル設定2
    Board: Seeduino XIAO RP2040
*/

//===========================================================
// debug リリース時は全て0にする
//===========================================================
#define ENABLE_DBGOUT 0 // 1:デバッグ出力有り
#define DEBUG_KEY_NOT_SEND 0 // 1:キーを送信しない
#define DEBUG_EMULATE_IOEXPANDER 0 // 1:IOエクスパンダをエミュレーション
#define DEBUG_CHECK_RAW 0 // IOエクスパンダ動作確認

#if ENABLE_DBGOUT
#define DBGPUTS(x) Serial.println(x)
#define DBGOUT(x) Serial.print(x)
#define DBGOUTHEX(x) Serial.print((x) & 0x0000FFFF, HEX)
#else
#define DBGPUTS(x)
#define DBGOUT(x)
#define DBGOUTHEX(x)
#endif

//===========================================================
// キーボード固有の定義
//===========================================================

//----------------------------------------------
// Matrix
//----------------------------------------------
#define NUM_MATRIX_ROWS 6
#define NUM_MATRIX_COLS 8

//----------------------------------------------
// debouncing
//----------------------------------------------
#define DEBOUNCING_DELAY 5

//----------------------------------------------
// 計算で決まる定数
//----------------------------------------------
#define BITMAP_BIT_NUM (NUM_MATRIX_ROWS * NUM_MATRIX_COLS)  // ビットマップサイズ 片手分
#define KEYMAP_SIZE (NUM_MATRIX_ROWS * NUM_MATRIX_COLS)     // キーマップサイズ 片手分

#endif  // CONFIG_H
