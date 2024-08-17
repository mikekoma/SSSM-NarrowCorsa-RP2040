#include "config.h"
#include "keymap.h"

#define _____ KC_NONE

//-------------------------------------------------------------------------
// ここからレイアウトとキーマップの定義
//-------------------------------------------------------------------------

// layout
uint8_t keymap_left[KEYMAP_SIZE] = {
//	1			2			3			4			5		6		7			8
	KC_ESC,		KC_PSCR,	KC_F1,		KC_F2,		KC_F3,	KC_F4,	KC_F5, 	KC_ENT,
	KC_INS,		KC_GRAVE,	KC_1,		  KC_2,		  KC_3,	  KC_4,	  KC_5,		KC_PGUP,	
	KC_GRAVE,	KC_TAB, 	KC_Q,		  KC_W,		  KC_E,	  KC_R,	  KC_T,		KC_PGDN,	
	KC_CAPS,	KC_LCTL,	KC_A,		  KC_S,		  KC_D,	  KC_F,	  KC_G,		KC_DEL,
	KC_HOME,	KC_LSFT,  KC_Z,		  KC_X,		  KC_C,	  KC_V,	  KC_B,		_____,
	KC_END,		KC_LCTL,  KC_LGUI,	KC_LALT,	KC_BS,	KC_SPC,	KC_LSFT,KC_LCTL
};

uint8_t keymap_right[KEYMAP_SIZE] = {
//	1			2			3			4			5			6			7			8			
	KC_F12,		KC_F11,		KC_F10,		KC_F9,		KC_F8,		KC_F7,		KC_F6,		KC_SPC,		
	KC_EQL,		KC_MINS,	KC_0,		  KC_9,		  KC_8,		  KC_7,		  KC_6,		  KC_APP,		
	KC_RBRC,	KC_LBRC,	KC_P,		  KC_O,		  KC_I,		  KC_U,		  KC_Y,		  KC_RGHT,	
	KC_ENT,		KC_QUOT,	KC_SCLN,	KC_L,		  KC_K,		  KC_J,		  KC_H,		  KC_BSLS,	
	KC_UP,		KC_RSFT,	KC_SLSH,	KC_DOT,		KC_COMM,	KC_M,		  KC_N,		  _____,		
	KC_DOWN,	KC_LEFT,	KC_RCTL,	KC_RALT,	KC_RCTL,	KC_ENT,		KC_RSFT,	KC_RCTL	
};

//-------------------------------------------------------------------------
// ここまでレイアウトとキーマップの定義
//-------------------------------------------------------------------------

