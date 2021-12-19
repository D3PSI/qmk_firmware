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

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = { {0,0,0}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {146,224,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {146,224,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {249,228,255}, {85,203,158}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {249,228,255}, {249,228,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [2] = { {0,0,0}, {85,203,158}, {85,203,158}, {85,203,158}, {85,203,158}, {146,224,255}, {85,203,158}, {85,203,158}, {85,203,158}, {85,203,158}, {146,224,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {249,228,255}, {85,203,158}, {169,120,255}, {169,120,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {14,255,255}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {14,255,255}, {0,0,0}, {0,0,0}, {189,179,255}, {189,179,255}, {0,0,0}, {0,0,0}, {14,255,255}, {0,0,255}, {0,0,255}, {0,0,0}, {249,228,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {146,224,255}, {0,0,0}, {0,0,255}, {243,222,234}, {31,255,255}, {31,255,255}, {0,0,0}, {0,0,0}, {146,224,255}, {146,224,255}, {146,224,255}, {0,0,0}, {146,224,255}, {0,0,0}, {180,255,233}, {31,255,255}, {31,255,255}, {31,255,255}, {0,0,0}, {146,224,255}, {169,120,255}, {169,120,255}, {169,120,255}, {205,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {85,203,158}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,0,0}, {169,120,255}, {146,224,255}, {12,225,241}, {249,228,255}, {0,0,0}, {85,203,158}, {85,203,158}, {85,203,158}, {35,255,255}, {243,222,234}, {134,255,213}, {169,120,255}, {169,120,255}, {169,120,255}, {12,225,241}, {35,255,255}, {0,0,0}, {85,203,158}, {85,203,158}, {85,203,158}, {35,255,255}, {35,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {146,224,255}, {146,224,255}, {105,255,255}, {0,0,0}, {85,203,158}, {85,203,158}, {85,203,158}, {35,255,255}, {134,255,213}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {35,255,255}, {85,203,158}, {35,255,255}, {35,255,255}, {0,0,0} },

    [5] = { {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {154,255,255}, {0,0,0}, {0,0,0}, {134,255,213}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {85,203,158}, {0,0,0}, {0,255,255}, {0,0,0}, {14,255,255}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {35,255,255}, {0,0,0}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {189,179,255}, {0,0,0}, {189,179,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
    //rgbmatrix_sethsv_noeeprom(180, 255, 231); // purple!
    rgb_matrix_sethsv_noeeprom(0, 0, 0);
    rgb_matrix_mode_noeeprom(1);
}

void set_layer_color(int layer) {
  /*for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }*/

    //int ledindex = 14;
    switch (layer) {
        case 1:
          //rgb_matrix_set_color( ledindex, 0xff, 0x00, 0x00 );
          //rgb_matrix_set_color( 41, 0xff, 0x00, 0x00 );
          //rgb_matrix_set_color( 40, 0xff, 0x00, 0x00 );
          //rgb_matrix_set_color( 33, 0xff, 0x00, 0x00 );
          //rgb_matrix_set_color( 44, 0xff, 0xff, 0x00 );
          //rgb_matrix_set_color( 8, 0xff, 0x00, 0xff );
          //rgb_matrix_set_color( 26, 0x00, 0xff, 0xff );
          break;
        case 2:
          //rgb_matrix_set_color( ledindex, 0x00, 0xff, 0x00 );
          break;
        case 3:
          //rgb_matrix_set_color( ledindex, 0x00, 0x00, 0xff );
          break;
       default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE)
          rgb_matrix_set_color_all(0, 0, 0);
        break;
      }

}
/*
void rgb_matrix_indicators_user(void) {
  switch (biton32(layer_state)) {
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}
*/
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    int layerNum = biton32(layer_state);
    int ledindex = 14;
    switch (layerNum) {
        case 1:
          //rgb_matrix_set_color( ledindex, 0xff, 0x00, 0x00 );
          //rgb_matrix_set_color( 41, 0xff, 0x00, 0x00 );
          //rgb_matrix_set_color( 40, 0xff, 0x00, 0x00 );
          //rgb_matrix_set_color( 33, 0xff, 0x00, 0x00 );
          //rgb_matrix_set_color( 44, 0xff, 0xff, 0x00 );
          //rgb_matrix_set_color( 8, 0xff, 0x00, 0xff );
          //rgb_matrix_set_color( 26, 0x00, 0xff, 0xff );

          RGB_MATRIX_INDICATOR_SET_COLOR(ledindex, 255, 0, 0);
          /*RGB_MATRIX_INDICATOR_SET_COLOR(41, 0, 255, 0);
          RGB_MATRIX_INDICATOR_SET_COLOR(40, 0, 0, 255);
          RGB_MATRIX_INDICATOR_SET_COLOR(33, 255, 255, 255);
          RGB_MATRIX_INDICATOR_SET_COLOR(44, 255, 255, 0);
          RGB_MATRIX_INDICATOR_SET_COLOR(8, 255, 0, 255);
          RGB_MATRIX_INDICATOR_SET_COLOR(26, 0, 255, 255);*/
          break;
        case 2:
          //rgb_matrix_set_color( ledindex, 0x00, 0xff, 0x00 );
          RGB_MATRIX_INDICATOR_SET_COLOR(ledindex, 0, 255, 0);
          break;
        case 3:
          //rgb_matrix_set_color( ledindex, 0x00, 0x00, 0xff );
          RGB_MATRIX_INDICATOR_SET_COLOR(ledindex, 0, 0, 255);
          break;
       default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE)
          rgb_matrix_set_color_all(0, 0, 0);
        break;
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
