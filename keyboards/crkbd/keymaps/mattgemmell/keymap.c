/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 Elliot Powell <@e11i0t23>
Copyright 2021 Matt Gemmell <@mattgemmell>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_REDO LSFT(LGUI(KC_Z))
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_MAC_LOCK_SCRN LCTL(LGUI(KC_Q))
#define KC_MAC_SCRN_SHOT LGUI(LSFT(KC_3))
#define KC_MAC_SCRN_MRKP LGUI(LSFT(KC_4))

#define ___off___	{RGB_OFF}
#define MG__WHITE	{RGB_WHITE}
#define	MG____RED	{RGB_RED}
#define MG__GREEN	{RGB_GREEN}
#define MG___BLUE	{RGB_BLUE}
#define MG_YELLOW	{RGB_YELLOW}
#define MG_ORANGE	{RGB_ORANGE}
#define MG___PINK	{RGB_PINK}
#define MG_PURPLE	{RGB_PURPLE}

enum my_keycodes {
  RGB_SET_SOLID = SAFE_RANGE,
  RGB_SET_WHITE,
  RGB_SET_PURPLE,
};

enum my_layers {
  _BASE,
  _NAV,
  _NUM,
  _ADJUST,
};

#define BASE TO(_BASE)
#define NAV TO(_NAV)
#define NUM TO(_NUM)
#define ADJUST TO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
       KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_LCTL,
                                          TO(1),  KC_ENT,  KC_LGUI,     KC_LALT,  KC_SPC, KC_BSPC
  ),

  [_NAV] = LAYOUT_split_3x6_3(
      XXXXXXX, KC_MS_WH_DOWN,    XXXXXXX,   KC_MS_UP,     XXXXXXX,    XXXXXXX,             KC_MS_ACCEL2, XXXXXXX,   KC_UP, XXXXXXX,    KC_PGUP, XXXXXXX,
        TO(0), KC_MS_WH_UP,   KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,    XXXXXXX,             KC_MS_ACCEL1, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDOWN, XXXXXXX,
      XXXXXXX, XXXXXXX,          XXXXXXX,    XXXXXXX,     XXXXXXX, KC_MS_BTN2,             KC_MS_ACCEL0, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
                                                      TO(2), KC_MS_BTN1,  _______,     _______, _______, _______
  ),

  [_NUM] = LAYOUT_split_3x6_3(
     KC_GRAVE, KC_DELETE,      XXXXXXX,     KC_LPRN,     KC_RPRN,    KC_BSLASH,             KC_SLSH,  KC_7, KC_8, KC_9, KC_KP_MINUS,  _______,
        TO(0), KC_MINUS,      KC_EQUAL, KC_LBRACKET, KC_RBRACKET,      XXXXXXX,             KC_ASTR, KC_4, KC_5, KC_6,  KC_KP_PLUS, KC_EQUAL,
      XXXXXXX, KC_MAC_UNDO, KC_MAC_CUT, KC_MAC_COPY, KC_MAC_PASTE, KC_MAC_REDO,             KC_COMM, KC_1, KC_2, KC_3,      KC_DOT,   KC_ENT,
                                                       TO(3), _______,  _______,     _______, _______, KC_0
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
      XXXXXXX, XXXXXXX, XXXXXXX, KC_MAC_SCRN_SHOT, KC_MAC_SCRN_MRKP, XXXXXXX,                      XXXXXXX, KC_MAC_LOCK_SCRN, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, XXXXXXX, RESET,
        TO(0), XXXXXXX, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, XXXXXXX,                      RGB_SET_PURPLE, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, XXXXXXX,
      XXXXXXX, XXXXXXX, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP, XXXXXXX,                      RGB_SET_WHITE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                          TO(0), _______,  _______,     _______, _______, _______
  )
};

const uint8_t PROGMEM ledmap[][42][3] = {
/* Starts at layer 1; we don't apply lights to Base (layer 0). */
[_NAV] = {
___off___, MG_ORANGE, ___off___, MG__WHITE, ___off___, ___off___, 				MG__GREEN, ___off___, MG__WHITE, ___off___, MG_ORANGE, ___off___,
MG_PURPLE, MG_ORANGE, MG__WHITE, MG__WHITE, MG__WHITE, ___off___, 				MG_YELLOW, MG__WHITE, MG__WHITE, MG__WHITE, MG_ORANGE, ___off___,
___off___, ___off___, ___off___, ___off___, ___off___, MG___BLUE, 				MG____RED, ___off___, ___off___, ___off___, ___off___, ___off___,
								 MG_ORANGE, MG___BLUE, ___off___, 				___off___, ___off___, ___off___
			},
[_NUM] = {
___off___, ___off___, ___off___, MG_YELLOW, MG_YELLOW, MG___PINK, 				MG___PINK, MG__GREEN, MG__GREEN, MG__GREEN, ___off___, MG____RED,
MG_PURPLE, MG____RED, MG__GREEN, MG_ORANGE, MG_ORANGE, ___off___, 				___off___, MG__GREEN, MG__GREEN, MG__GREEN, ___off___, ___off___,
___off___, ___off___, ___off___, ___off___, ___off___, ___off___, 				___off___, MG__GREEN, MG__GREEN, MG__GREEN, ___off___, MG___BLUE,
						   		 MG__GREEN, ___off___, ___off___, 				___off___, ___off___, MG__GREEN
			},
[_ADJUST] = {
___off___, ___off___, ___off___, MG_ORANGE, MG_ORANGE, ___off___, 				___off___, MG_ORANGE, MG__WHITE, MG__WHITE, ___off___, MG____RED,
MG_PURPLE, ___off___, MG___BLUE, MG___BLUE, MG___BLUE, ___off___, 				MG_PURPLE, MG___PINK, MG_YELLOW, MG_YELLOW, MG_YELLOW, ___off___,
___off___, ___off___, MG_PURPLE, MG_PURPLE, MG_PURPLE, ___off___, 				MG__WHITE, ___off___, ___off___, ___off___, ___off___, ___off___,
						   		 MG_PURPLE, ___off___, ___off___, 				___off___, ___off___, ___off___
			},
};


extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
    //rgbmatrix_sethsv_noeeprom(180, 255, 231); // purple!
    rgb_matrix_sethsv_noeeprom(0, 0, 0);
    rgb_matrix_mode_noeeprom(1);
}

uint8_t ledIndexForKeymapIndex(uint8_t keyIndex) {
	// Turn keyIndex into a row and column within g_led_config.
	// Reference: https://github.com/qmk/qmk_firmware/blob/master/keyboards/crkbd/r2g/r2g.c
	uint8_t row = 0;
	uint8_t col = 0;
	uint8_t keysPerRow = 12; // Specific to crkdb!
	uint8_t keysPerHalf = keysPerRow / 2; // Assumes equal split!

	row = keyIndex / keysPerRow;
	col = keyIndex % keysPerRow;
	if (row == 3) { // Specific to crkbd!
		col += 3; // Compensate for leading three NO_LED entries in g_led_config.
	}

	bool mirror = (col >= keysPerHalf);
	if (mirror) {
		// Normalise row and col per g_led_config structure.
		row += 4;
		col -= keysPerHalf;
		// Mirror column position.
		col = (keysPerHalf - 1) - col;
	}

	return g_led_config.matrix_co[row][col];
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    uint8_t layerNum = get_highest_layer(layer_state);
    if (layerNum == 0) {
        rgb_matrix_set_color_all(0, 0, 0);
        return;
    }

    uint8_t ledIndex = 0;
    uint8_t r, g, b;
    for (uint8_t keyIndex = 0; keyIndex < 42; keyIndex++) { // 0 to 42
        ledIndex = ledIndexForKeymapIndex(keyIndex);

        if (ledIndex >= led_min && ledIndex <= led_max) {
            r = pgm_read_byte(&ledmap[layerNum][keyIndex][0]);
            g = pgm_read_byte(&ledmap[layerNum][keyIndex][1]);
            b = pgm_read_byte(&ledmap[layerNum][keyIndex][2]);

            if (!r && !g && !b) {
                RGB_MATRIX_INDICATOR_SET_COLOR(ledIndex, 0, 0, 0);
            } else {
                RGB_MATRIX_INDICATOR_SET_COLOR(ledIndex, r, g, b);
            }
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_SET_SOLID:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case RGB_SET_WHITE:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(0, 0, 255);
      }
      return false;
    case RGB_SET_PURPLE:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(180, 255, 231);
      }
      return false;
  }
  return true;
}
