#include <Arduino.h>
#include <stdint.h>
#include "config.h"
#include "board.h"

// drive row bits
// lo active
uint16_t row_bits[NUM_MATRIX_ROWS] = {
  (uint16_t)(~BIT_R1), (uint16_t)(~BIT_R2), (uint16_t)(~BIT_R3), (uint16_t)(~BIT_R4), (uint16_t)(~BIT_R5), (uint16_t)(~BIT_R6)
};

uint16_t const col_bits[NUM_MATRIX_COLS] = {
  BIT_C1,
  BIT_C2,
  BIT_C3,
  BIT_C4,
  BIT_C5,
  BIT_C6,
  BIT_C7,
  BIT_C8
};
