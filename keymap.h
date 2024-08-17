#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdint.h>
#include "config.h"
#include "keycodes.h"

extern uint8_t layout_converter_left[KEYMAP_SIZE];
extern uint8_t layout_converter_right[KEYMAP_SIZE];
extern uint8_t keymap_left[KEYMAP_SIZE];
extern uint8_t keymap_right[KEYMAP_SIZE];

#endif// KEYMAP_H
