#include "gherkin.h"

extern keymap_config_t keymap_config;

enum gherkin_layers {
  _QWERTY,
  _LAYER1,
  _LAYER2,
  _LAYER3
};	

enum gherkin_keycodes {
  QWERTY,
  LAYER1,
  LAYER2,
  LAYER3
};


enum { 
   TD_Q_ESC,
  // TD_C_LGUI,
  // TD_A_LCTRL,
  // TD_M_RCTRL,
  // TD_V_LALT,
   TD_SPC_ENT,
  // TD_ENT_SHIFT,
  // TD_Z_SHIFT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = {
		{TD(TD_Q_ESC), KC_W, KC_E, KC_R, KC_T, KC_Y}, 
		{KC_U, KC_I, KC_O, KC_P, CTL_T(KC_A), KC_S}, 
		{KC_D, KC_F, KC_G, KC_H, KC_J, KC_K}, 
		{KC_L, TD(TD_SPC_ENT), SFT_T(KC_Z), LT(LAYER3, KC_X), GUI_T(KC_C), ALT_T(KC_V)}, 
		{LT(LAYER1, KC_B), LT(LAYER2, KC_N), CTL_T(KC_M), KC_COMMA, KC_DOT, SFT_T(KC_BSPC)}
},
	[_LAYER1] = {
		{KC_1, KC_2, KC_3, KC_4, KC_5, KC_6}, 
    {KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_GRV}, 
		{KC_SLSH, KC_TAB, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL}, 
		{KC_QUOT, KC_TAB, KC_TRNS, KC_TRNS, GUI_T(KC_BSLS), KC_TRNS}, 
		{KC_TRNS, KC_TRNS, KC_TRNS, S(KC_COMMA), S(KC_DOT), KC_DEL}
},

	[_LAYER2] = {
		{KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC}, 
		{KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS, S(KC_GRV)}, 
		{S(KC_SLSH), KC_ENT, S(KC_LBRC), S(KC_RBRC), S(KC_MINS), S(KC_EQL)}, 
		{S(KC_QUOT), KC_TRNS, KC_TRNS, KC_TRNS, GUI_T(S(KC_BSLS)), KC_TRNS}, 
		{KC_TRNS, KC_TRNS, KC_TRNS, KC_COLN, KC_SCLN, KC_PIPE}
},

	[_LAYER3] = {
		{LCTL(LSFT(KC_ESC)), KC_UP, LALT(KC_TAB), KC_PGUP, KC_TRNS, KC_F1}, 
		{KC_F2, KC_F3, KC_F4, KC_F5, KC_LEFT, KC_DOWN}, 
		{KC_RIGHT, KC_PGDN, KC_TRNS, KC_F6, KC_F7, KC_F8}, 
		{KC_F9, KC_F10, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}, 
		{KC_TRNS, KC_F11, KC_F12, KC_TRNS, MAGIC_HOST_NKRO, RESET}
}

};

qk_tap_dance_action_t tap_dance_actions[] = {

  [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
 // [TD_C_LGUI] = ACTION_TAP_DANCE_DOUBLE(KC_C, KC_LGUI),
 // [TD_A_LCTRL] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_LCTRL),
 // [TD_M_RCTRL] = ACTION_TAP_DANCE_DOUBLE(KC_M, KC_RCTRL),
 // [TD_V_LALT] = ACTION_TAP_DANCE_DOUBLE(KC_V, KC_LALT),
  [TD_SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
 // [TD_ENT_SHIFT] = ACTION_TAP_DANCE_DOUBLE(KC_ENT,KC_RSHIFT),
 // [TD_Z_SHIFT] = ACTION_TAP_DANCE_DOUBLE(KC_Z,KC_LSHIFT)
};


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	keyevent_t event = record->event;
    (void)event;

	switch (id) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LAYER1:
      if (record->event.pressed) {
        layer_on(_LAYER1);
        update_tri_layer(_LAYER1, _LAYER2, _LAYER3);
      } else {
        layer_off(_LAYER1);
        update_tri_layer(_LAYER1, _LAYER2, _LAYER3);
      }
      return false;
      break;
    case LAYER2:
      if (record->event.pressed) {
        layer_on(_LAYER2);
        update_tri_layer(_LAYER1, _LAYER2, _LAYER3);
      } else {
        layer_off(_LAYER2);
        update_tri_layer(_LAYER1, _LAYER2, _LAYER3);
      }
      return false;
      break;
    case LAYER3:
      if (record->event.pressed) {
        layer_on(_LAYER3);
        update_tri_layer(_LAYER1, _LAYER2, _LAYER3);
      } else {
        layer_off(_LAYER3);
        update_tri_layer(_LAYER1, _LAYER2, _LAYER3);
      }
      return false;
      break;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		DDRD |= (1 << 5); PORTD &= ~(1 << 5);
	} else {
		DDRD &= ~(1 << 5); PORTD &= ~(1 << 5);
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRB |= (1 << 0); PORTB &= ~(1 << 0);
	} else {
		DDRB &= ~(1 << 0); PORTB &= ~(1 << 0);
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

}
