/*
 * Copyright 2024 @DreaM117er
 * Copyright 2024 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum custom_keycodes {
  ENC_MODE,
  ENC_LEFT,
  ENC_RIGHT,
};

enum encoder_modes {
  ENC_MODE_SCROLL,
  ENC_MODE_VOLUME,
  ENC_MODE_COUNT
};

static uint8_t encoder_mode = ENC_MODE_SCROLL;

void cycle_encoder_mode(void) {
  encoder_mode = (encoder_mode + 1) % ENC_MODE_COUNT;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
      if (clockwise) {
          tap_code16(ENC_RIGHT);
      } else {
          tap_code16(ENC_LEFT);
      }
  } else if (index == 1) {
      if (clockwise) {
          tap_code(KC_MS_WH_DOWN);
      } else {
          tap_code(KC_MS_WH_UP);
      }
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ENC_MODE:
        if (record->event.pressed) {
            cycle_encoder_mode();
        }
        return false;
    case ENC_LEFT:
        if (record->event.pressed) {
            switch (encoder_mode) {
                case ENC_MODE_VOLUME:
                    tap_code(KC_VOLD);
                    break;
                case ENC_MODE_SCROLL:
                    tap_code(KC_MS_WH_UP);
                    break;
            }
        }
        return false;
    case ENC_RIGHT:
        if (record->event.pressed) {
            switch (encoder_mode) {
                case ENC_MODE_VOLUME:
                    tap_code(KC_VOLU);
                    break;
                case ENC_MODE_SCROLL:
                    tap_code(KC_MS_WH_DOWN);
                    break;
            }
        }
        return false;
    default:
        return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                               KC_Y,           KC_U,   KC_I,     KC_O,     KC_P,     KC_LGUI,
        KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                               KC_H,           KC_J,   KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                               KC_N,           KC_M,   KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
        KC_LCTL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LALT,  LT(1, KC_SPC),  ENC_MODE, XXXXXXX,  LT(2, KC_BSPC), KC_ENT, XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(3)
        ),

    [1] = LAYOUT(
        KC_ESC,   LSFT(KC_1), LSFT(KC_2),   LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),                       LSFT(KC_6),     LSFT(KC_7), LSFT(KC_8),     LSFT(KC_9), LSFT(KC_0), KC_LGUI,
        KC_TAB,   KC_1,       KC_2,         KC_3,       KC_4,       KC_5,                             KC_6,           KC_7,       KC_8,           KC_9,       KC_0,       XXXXXXX,
        KC_LSFT,  XXXXXXX,    LSFT(KC_GRV), KC_GRV,     KC_LBRC,    LSFT(KC_LBRC),                    LSFT(KC_RBRC),  KC_RBRC,    KC_COMM,        KC_DOT,     KC_SLSH,    XXXXXXX,
        KC_LCTL,  XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,      XXXXXXX,  XXXXXXX,  KC_BSPC,        KC_ENT,     LSFT(KC_SCLN),  XXXXXXX,    XXXXXXX,    XXXXXXX
        ),

    [2] = LAYOUT(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MINS,  KC_EQL,   KC_LGUI,
        KC_TAB,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,                       KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_BSLS,  KC_DEL,
        KC_LSFT,  KC_F11,   KC_F12,   XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_LCTL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
        ),

    [3] = LAYOUT(
        KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                       KC_Y,     KC_U,   KC_I,     KC_O,     KC_P,     KC_LGUI,
        KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                       KC_H,     KC_J,   KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                       KC_N,     KC_M,   KC_COMM,  KC_DOT,   KC_SLSH,  XXXXXXX,
        KC_LCTL,  XXXXXXX,  KC_F5,    KC_F3,    KC_LALT,  KC_SPC,  XXXXXXX,  XXXXXXX, KC_BSPC,  KC_ENT, XXXXXXX,  XXXXXXX,  XXXXXXX,  TO(0)
        )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   {
            //Encoder 1
            ENCODER_CCW_CW(ENC_LEFT, ENC_RIGHT),
            //Encoder 2
            ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN),
            },
    [1] =   {
            //Encoder 1
            ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
            //Encoder 2
            ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
            },
    [2] =   {
            //Encoder 1
            ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
            //Encoder 2
            ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
            },
    [3] =   {
            //Encoder 1
            ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
            //Encoder 2
            ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
            },
};
#endif
