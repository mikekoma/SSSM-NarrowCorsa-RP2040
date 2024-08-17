#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include <stdint.h>
#include "config.h"

//----------------------------------------------
// PCA9555
//----------------------------------------------
/*
	 R4		0x01
	 R5		0x02
	 R6		0x04
	 LED	0x08
	 C1		0x10
	 C2		0x20
	 C3		0x40
	 C4		0x80

	 C5		0x01
	 C6		0x02
	 C7		0x04
	 C8		0x08
	 L0/R1	0x10
	 R1		0x20
	 R2		0x40
	 R3		0x80
*/

#define PCA9555_ADDR_LEFT 0x20   // in 7bit for Arduino
#define PCA9555_ADDR_RIGHT 0x21  // in 7bit for Arduino

#define P0_0 0x0001U
#define P0_1 0x0002U
#define P0_2 0x0004U
#define P0_3 0x0008U
#define P0_4 0x0010U
#define P0_5 0x0020U
#define P0_6 0x0040U
#define P0_7 0x0080U

#define P1_0 0x0100U
#define P1_1 0x0200U
#define P1_2 0x0400U
#define P1_3 0x0800U
#define P1_4 0x1000U
#define P1_5 0x2000U
#define P1_6 0x4000U
#define P1_7 0x8000U

// IB136E
#define BIT_C8 P0_0
#define BIT_C7 P0_1
#define BIT_R6 P0_2
#define BIT_C6 P0_3
#define BIT_C5 P0_4
#define BIT_C4 P0_5
#define BIT_R5 P0_6
#define BIT_C3 P0_7

#define BIT_C2 P1_0
#define BIT_C1 P1_1
#define BIT_R4 P1_2
#define BIT_R3 P1_3
#define BIT_R2 P1_4
#define BIT_R1 P1_5
#define BIT_NC1 P1_6
#define BIT_NC2 P1_7

#define BIT_DIR_IN (BIT_C1 | BIT_C2 | BIT_C3 | BIT_C4 | BIT_C5 | BIT_C6 | BIT_C7 | BIT_C8)

extern uint16_t row_bits[NUM_MATRIX_ROWS];
extern uint16_t const col_bits[NUM_MATRIX_COLS];

#endif  //BOARD_H
