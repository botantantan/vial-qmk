#include QMK_KEYBOARD_H

#define DEFAULT 0
#define RAISE   1
#define LOWER   2
#define WORKSPACE 3
#define SHORTCUTS 4


enum custom_keycodes {
    CTRL_SHIFT = SAFE_RANGE,
    ENC_MODE,
    ENC_LEFT,
    ENC_RIGHT,
    PASSWORD,
};

enum encoder_modes {
    ENC_MODE_SCROLL,
    ENC_MODE_VOLUME,
    // ENC_MODE_MOUSE,
    ENC_MODE_COUNT
};

static uint8_t encoder_mode = ENC_MODE_SCROLL;
static uint16_t custom_key_timer;
static bool is_custom_key_pressed;

void cycle_encoder_mode(void);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CTRL_SHIFT:
        if (record->event.pressed) {
            if (get_mods() & MOD_MASK_SHIFT) {
                register_code(KC_LSFT);
            } else {
                register_code(KC_LCTL);
            }
        } else {
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
        }
        return false;
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
                // case ENC_MODE_MOUSE:
                //     tap_code(KC_BTN1);
                //     break;
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
                // case ENC_MODE_MOUSE:
                //     tap_code(KC_BTN2);
                //     break;
            }
        }
        return false;
    case PASSWORD:
        if (record->event.pressed) {
            is_custom_key_pressed = true;
            custom_key_timer = timer_read();
        } else {
            if (is_custom_key_pressed) {
                if (timer_elapsed(custom_key_timer) < TAPPING_TERM) {
                    SEND_STRING("1234qwer");
                } else {
                    register_code(KC_LGUI);
                    unregister_code(KC_LGUI);
                }
                is_custom_key_pressed = false;
            }
        }
        return false;
    default:
        return true;
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    LGUI_T(KC_CAPS),
        LT(LOWER,KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LT(WORKSPACE,KC_QUOT),
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LSFT_T(KC_BSLS),
        KC_LCTL, KC_BTN1, LT(SHORTCUTS,KC_BTN1), KC_LALT, ALT_T(KC_DEL), LGUI_T(KC_ENT), ENC_MODE , LT(SHORTCUTS,KC_RSFT), KC_SPC, LT(RAISE,KC_BSPC), ALT_T(KC_BSLS), KC_BTN2, KC_BTN2, KC_RALT
    ),

    [RAISE] = LAYOUT(
        QK_BOOT, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_LBRC, KC_RBRC, KC_ASTR, KC_EQL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        _______, _______, _______, _______, _______, _______,                   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  _______, _______
    ),

    [LOWER] = LAYOUT(
        KC_TILD, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT
    ),

    [WORKSPACE] = LAYOUT(
        XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [SHORTCUTS] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   LCTL(KC_Q), LCTL(KC_W), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_MPLY, KC_MSTP, KC_BRIU
    )
};

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

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [DEFAULT] =   { ENCODER_CCW_CW(ENC_LEFT, ENC_RIGHT), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [RAISE] =     { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [LOWER] =     { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [WORKSPACE] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [SHORTCUTS] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif

