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
#define KC_MAC_HOME LGUI(KC_UP)
#define KC_MAC_END LGUI(KC_DOWN)

#define ___off___	{0,0,0}
#define MG__WHITE	{255,255,255}
#define	MG____RED	{255,0,0}
#define MG__GREEN	{32,159,33}
#define MG___BLUE	{0,181,213}
#define MG_YELLOW	{255,208,0}
#define MG_ORANGE	{255,85,0}
#define MG___PINK	{208,0,255}
#define MG_PURPLE	{50,0,232}

enum my_keycodes {
  RGB_SET_SOLID = SAFE_RANGE,
  RGB_SET_WHITE,
  RGB_SET_PURPLE,
};

enum tap_dance_keycodes {
  TD_M_MUTE,
  TD_ENT_CTRL,
  TD_CMD_CAPS,
  TD_O_MINUS,
  TD_P_EQUALS,
  TD_S_NAV,
  TD_D_NUM,
  TD_F_ADJUST,
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
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    TD(TD_O_MINUS),   TD(TD_P_EQUALS),  KC_BSPC,
       KC_ESC,    KC_A,    TD(TD_S_NAV),    TD(TD_D_NUM),    TD(TD_F_ADJUST),    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    TD(TD_M_MUTE), KC_COMM,  KC_DOT, KC_SLSH, KC_LCTL,
                                          TO(1),  KC_ENT,  TD(TD_CMD_CAPS),     KC_LALT,  KC_SPC, KC_BSPC
  ),

  [_NAV] = LAYOUT_split_3x6_3(
      XXXXXXX, KC_MS_WH_DOWN,    XXXXXXX,   KC_MS_UP,     XXXXXXX,    XXXXXXX,             KC_MS_ACCEL2, XXXXXXX,   KC_UP, XXXXXXX,    KC_PGUP, KC_MAC_HOME,
        TO(0), KC_MS_WH_UP,   KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,    XXXXXXX,             KC_MS_ACCEL1, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDOWN, KC_MAC_END,
      _______, XXXXXXX,          XXXXXXX,    XXXXXXX,     XXXXXXX, KC_MS_BTN2,             KC_MS_ACCEL0, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, _______,
                                                      TO(2), KC_MS_BTN1,  _______,     _______, _______, _______
  ),

  [_NUM] = LAYOUT_split_3x6_3(
     KC_GRAVE, KC_DELETE,      XXXXXXX,     KC_LPRN,     KC_RPRN,    KC_BSLASH,             KC_SLSH,  KC_7, KC_8, KC_9, KC_KP_MINUS,  _______,
        TO(0), KC_MINUS,      KC_EQUAL, KC_LBRACKET, KC_RBRACKET,      XXXXXXX,             KC_ASTR, KC_4, KC_5, KC_6,  KC_KP_PLUS, KC_EQUAL,
      _______, KC_MAC_UNDO, KC_MAC_CUT, KC_MAC_COPY, KC_MAC_PASTE, KC_MAC_REDO,             KC_COMM, KC_1, KC_2, KC_3,      KC_DOT,   TD(TD_ENT_CTRL),
                                                       TO(3), _______,  _______,     _______, _______, KC_0
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
      XXXXXXX, XXXXXXX, XXXXXXX, KC_MAC_SCRN_SHOT, KC_MAC_SCRN_MRKP, XXXXXXX,                      XXXXXXX, KC_MAC_LOCK_SCRN, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, XXXXXXX, RESET,
        TO(0), XXXXXXX, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, XXXXXXX,                      RGB_SET_PURPLE, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, XXXXXXX,
      _______, XXXXXXX, KC_AUDIO_VOL_DOWN, KC_AUDIO_MUTE, KC_AUDIO_VOL_UP, XXXXXXX,                      RGB_SET_WHITE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
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
___off___, MG___PINK, ___off___, ___off___, ___off___, ___off___, 				___off___, MG__GREEN, MG__GREEN, MG__GREEN, ___off___, MG___BLUE,
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
    rgb_matrix_enable();
    rgb_matrix_sethsv_noeeprom(0, 0, 0); // (180, 255, 231) is purple
    rgb_matrix_mode_noeeprom(1);
}

// ====================================================
// RGB matrix
// ====================================================

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

// ====================================================
// Custom keycodes handling, not including Tap Dance
// ====================================================

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

// ====================================================
// Tap Dance stuff, via Oryx template
// ====================================================

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[8]; // Should be the number of Tap Dance routines defined.
uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

// End Tap Dance top boilerplate

void on_dance_m_mute(qk_tap_dance_state_t *state, void *user_data);
void dance_m_mute_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_m_mute_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_m_mute(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_M);
        tap_code16(KC_M);
        tap_code16(KC_M);
    }
    if(state->count > 3) {
        tap_code16(KC_M);
    }
}

void dance_m_mute_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_M); break;
        case SINGLE_HOLD: register_code16(KC_AUDIO_MUTE); break;
        case DOUBLE_TAP: register_code16(KC_M); register_code16(KC_M); break;
        case DOUBLE_HOLD: register_code16(KC_M); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_M); register_code16(KC_M);
    }
}

void dance_m_mute_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_M); break;
        case SINGLE_HOLD: unregister_code16(KC_AUDIO_MUTE); break;
        case DOUBLE_TAP: unregister_code16(KC_M); break;
        case DOUBLE_HOLD: unregister_code16(KC_M); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_M); break;
    }
    dance_state[0].step = 0;
}

void on_dance_ent_ctrl(qk_tap_dance_state_t *state, void *user_data);
void dance_ent_ctrl_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_ent_ctrl_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_ent_ctrl(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ENTER);
        tap_code16(KC_ENTER);
        tap_code16(KC_ENTER);
    }
    if(state->count > 3) {
        tap_code16(KC_ENTER);
    }
}

void dance_ent_ctrl_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_ENTER); break;
        case SINGLE_HOLD: register_code16(KC_LCTL); break;
        case DOUBLE_TAP: register_code16(KC_ENTER); register_code16(KC_ENTER); break;
        case DOUBLE_HOLD: register_code16(KC_ENTER); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ENTER); register_code16(KC_ENTER);
    }
}

void dance_ent_ctrl_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_ENTER); break;
        case SINGLE_HOLD: unregister_code16(KC_LCTL); break;
        case DOUBLE_TAP: unregister_code16(KC_ENTER); break;
        case DOUBLE_HOLD: unregister_code16(KC_ENTER); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ENTER); break;
    }
    dance_state[1].step = 0;
}

void on_dance_cmd_caps(qk_tap_dance_state_t *state, void *user_data);
void dance_cmd_caps_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_cmd_caps_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_cmd_caps(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LGUI);
        tap_code16(KC_LGUI);
        tap_code16(KC_LGUI);
    }
    if(state->count > 3) {
        tap_code16(KC_LGUI);
    }
}

void dance_cmd_caps_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP: register_code16(KC_LGUI); break;
        case SINGLE_HOLD: register_code16(KC_LGUI); break;
        case DOUBLE_TAP: register_code16(KC_LGUI); register_code16(KC_LGUI); break;
        case DOUBLE_HOLD: register_code16(KC_CAPSLOCK); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LGUI); register_code16(KC_LGUI);
    }
}

void dance_cmd_caps_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_LGUI); break;
        case SINGLE_HOLD: unregister_code16(KC_LGUI); break;
        case DOUBLE_TAP: unregister_code16(KC_LGUI); break;
        case DOUBLE_HOLD: unregister_code16(KC_CAPSLOCK); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LGUI); break;
    }
    dance_state[2].step = 0;
}

void on_dance_o_minus(qk_tap_dance_state_t *state, void *user_data);
void dance_o_minus_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_o_minus_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_o_minus(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_O);
        tap_code16(KC_O);
        tap_code16(KC_O);
    }
    if(state->count > 3) {
        tap_code16(KC_O);
    }
}

void dance_o_minus_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case SINGLE_TAP: register_code16(KC_O); break;
        case SINGLE_HOLD: register_code16(KC_MINUS); break;
        case DOUBLE_TAP: register_code16(KC_O); register_code16(KC_O); break;
        case DOUBLE_HOLD: register_code16(LALT(LSFT(KC_MINUS))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_O); register_code16(KC_O);
    }
}

void dance_o_minus_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
        case SINGLE_TAP: unregister_code16(KC_O); break;
        case SINGLE_HOLD: unregister_code16(KC_MINUS); break;
        case DOUBLE_TAP: unregister_code16(KC_O); break;
        case DOUBLE_HOLD: unregister_code16(LALT(LSFT(KC_MINUS))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_O); break;
    }
    dance_state[3].step = 0;
}

void on_dance_p_equals(qk_tap_dance_state_t *state, void *user_data);
void dance_p_equals_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_p_equals_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_p_equals(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_P);
        tap_code16(KC_P);
        tap_code16(KC_P);
    }
    if(state->count > 3) {
        tap_code16(KC_P);
    }
}

void dance_p_equals_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[4].step = dance_step(state);
    switch (dance_state[4].step) {
        case SINGLE_TAP: register_code16(KC_P); break;
        case SINGLE_HOLD: register_code16(KC_EQUAL); break;
        case DOUBLE_TAP: register_code16(KC_P); register_code16(KC_P); break;
        case DOUBLE_HOLD: register_code16(KC_KP_PLUS); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_P); register_code16(KC_P);
    }
}

void dance_p_equals_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[4].step) {
        case SINGLE_TAP: unregister_code16(KC_P); break;
        case SINGLE_HOLD: unregister_code16(KC_EQUAL); break;
        case DOUBLE_TAP: unregister_code16(KC_P); break;
        case DOUBLE_HOLD: unregister_code16(KC_KP_PLUS); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_P); break;
    }
    dance_state[4].step = 0;
}

void on_dance_s_nav(qk_tap_dance_state_t *state, void *user_data);
void dance_s_nav_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_s_nav_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_s_nav(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_S);
        tap_code16(KC_S);
        tap_code16(KC_S);
    }
    if(state->count > 3) {
        tap_code16(KC_S);
    }
}

void dance_s_nav_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[5].step = dance_step(state);
    switch (dance_state[5].step) {
        case SINGLE_TAP: register_code16(KC_S); break;
        case SINGLE_HOLD: layer_move(_NAV); break;
        case DOUBLE_TAP: register_code16(KC_S); register_code16(KC_S); break;
        case DOUBLE_HOLD: register_code16(KC_S); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_S); register_code16(KC_S);
    }
}

void dance_s_nav_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[5].step) {
        case SINGLE_TAP: unregister_code16(KC_S); break;
        case DOUBLE_TAP: unregister_code16(KC_S); break;
        case DOUBLE_HOLD: unregister_code16(KC_S); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_S); break;
    }
    dance_state[5].step = 0;
}

void on_dance_d_num(qk_tap_dance_state_t *state, void *user_data);
void dance_d_num_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_d_num_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_d_num(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_D);
        tap_code16(KC_D);
        tap_code16(KC_D);
    }
    if(state->count > 3) {
        tap_code16(KC_D);
    }
}

void dance_d_num_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[6].step = dance_step(state);
    switch (dance_state[6].step) {
        case SINGLE_TAP: register_code16(KC_D); break;
        case SINGLE_HOLD: layer_move(_NUM); break;
        case DOUBLE_TAP: register_code16(KC_D); register_code16(KC_D); break;
        case DOUBLE_HOLD: register_code16(KC_D); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_D); register_code16(KC_D);
    }
}

void dance_d_num_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[6].step) {
        case SINGLE_TAP: unregister_code16(KC_D); break;
        case DOUBLE_TAP: unregister_code16(KC_D); break;
        case DOUBLE_HOLD: unregister_code16(KC_D); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_D); break;
    }
    dance_state[6].step = 0;
}

void on_dance_f_adjust(qk_tap_dance_state_t *state, void *user_data);
void dance_f_adjust_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_f_adjust_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_f_adjust(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_F);
        tap_code16(KC_F);
        tap_code16(KC_F);
    }
    if(state->count > 3) {
        tap_code16(KC_F);
    }
}

void dance_f_adjust_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[7].step = dance_step(state);
    switch (dance_state[7].step) {
        case SINGLE_TAP: register_code16(KC_F); break;
        case SINGLE_HOLD: layer_move(_ADJUST); break;
        case DOUBLE_TAP: register_code16(KC_F); register_code16(KC_F); break;
        case DOUBLE_HOLD: register_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_F); register_code16(KC_F);
    }
}

void dance_f_adjust_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[7].step) {
        case SINGLE_TAP: unregister_code16(KC_F); break;
        case DOUBLE_TAP: unregister_code16(KC_F); break;
        case DOUBLE_HOLD: unregister_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_F); break;
    }
    dance_state[7].step = 0;
}

// Assign handlers to all Tap Dance actions.

qk_tap_dance_action_t tap_dance_actions[] = {
    /* Keys should match the Tap Dance keycodes */
    [TD_M_MUTE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_m_mute, dance_m_mute_finished, dance_m_mute_reset),
    [TD_ENT_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_ent_ctrl, dance_ent_ctrl_finished, dance_ent_ctrl_reset),
    [TD_CMD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_cmd_caps, dance_cmd_caps_finished, dance_cmd_caps_reset),
    [TD_O_MINUS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_o_minus, dance_o_minus_finished, dance_o_minus_reset),
    [TD_P_EQUALS] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_p_equals, dance_p_equals_finished, dance_p_equals_reset),
    [TD_S_NAV] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_s_nav, dance_s_nav_finished, dance_s_nav_reset),
    [TD_D_NUM] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_d_num, dance_d_num_finished, dance_d_num_reset),
    [TD_F_ADJUST] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_f_adjust, dance_f_adjust_finished, dance_f_adjust_reset),
};
