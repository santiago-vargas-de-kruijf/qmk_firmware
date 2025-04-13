/* Copyright 2022 James White <jamesmnw@gmail.com>
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

enum layers {
    _QWERTY,
    _SYMBOL,
    _NAV,
    _FUNC
};


// Left homerow mods
bool is_lgui_held = false;
bool is_lalt_held = false;
bool is_lctrl_held = false;
bool is_lshift_held = false;

// Right homerow mods
bool is_rgui_held = false;
bool is_ralt_held = false;
bool is_rctrl_held = false;
bool is_rshift_held = false;

void matrix_scan_user(void) {
    uint8_t mods = get_mods();

    is_lgui_held   = mods & MOD_BIT(KC_LGUI);
    is_lalt_held   = mods & MOD_BIT(KC_LALT);
    is_lctrl_held  = mods & MOD_BIT(KC_LCTL);
    is_lshift_held = mods & MOD_BIT(KC_LSFT);

    is_rgui_held   = mods & MOD_BIT(KC_RGUI);
    is_ralt_held   = mods & MOD_BIT(KC_RALT);
    is_rctrl_held  = mods & MOD_BIT(KC_RCTL);
    is_rshift_held = mods & MOD_BIT(KC_RSFT);
}



#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}
#endif


static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
    // 'out', 128x32px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x80, 0xf0, 0x3c, 0x3c, 0x70, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x04, 0x04, 0x04, 0xc4, 0xc4, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 
0xfc, 0x38, 0xe0, 0x80, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x80, 0xf0, 0x3c, 0x1c, 0x78, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xc4, 0xc4, 0xcc, 0x7c, 0x30, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x1c, 0x38, 0xe0, 0xe0, 0x38, 0x1c, 0x04, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x30, 0x3e, 0x07, 0x01, 0x00, 0x00, 0x00, 0x04, 0x3c, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
0x01, 0x00, 0x00, 0x03, 0x0e, 0x1c, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x30, 0x3c, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x04, 0x3c, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x03, 0x0e, 0x3c, 0x30, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x3c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  };

    // oled_write_P(qmk_logo, false);
    oled_write_raw_P(qmk_logo, sizeof(qmk_logo));
}


void oled_layer_wpm(void){
     // Show active layer
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Qwerty\n"), false);
            break;
        case _SYMBOL:
            oled_write_P(PSTR("Symbol\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _FUNC:
            oled_write_P(PSTR("Function\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Keyboard status
    led_t led_state = host_keyboard_led_state();
    if(led_state.caps_lock){
        oled_write_P(PSTR("CAPS LOCK\n "), false);
    }

    // Show current WPM
    oled_write_P(PSTR("WPM: "), false);
    char wpm_str[4];
    snprintf(wpm_str, sizeof(wpm_str), "%03d", get_current_wpm());
    oled_write(wpm_str, false);
}

void oled_homerow_mods(void){
    oled_clear();

    if (is_lgui_held) {
        oled_write_ln_P(PSTR("MOD: LEFT GUI  (Z)"), false);
    }
    if (is_lalt_held) {
        oled_write_ln_P(PSTR("MOD: LEFT ALT  (X)"), false);
    }
    if (is_lctrl_held) {
        oled_write_ln_P(PSTR("MOD: LEFT CTRL (C)"), false);
    }
    if (is_lshift_held) {
        oled_write_ln_P(PSTR("MOD: LEFT SHIFT (V)"), false);
    }

    if (is_rgui_held) {
        oled_write_ln_P(PSTR("MOD: RIGHT GUI  (Z)"), false);
    }
    if (is_ralt_held) {
        oled_write_ln_P(PSTR("MOD: RIGHT  (X)"), false);
    }
    if (is_rctrl_held) {
        oled_write_ln_P(PSTR("MOD: RIGHT CTRL (C)"), false);
    }
    if (is_rshift_held) {
        oled_write_ln_P(PSTR("MOD: RIGHT SHIFT (V)"), false);
    }

    if (!is_lgui_held && !is_lalt_held && !is_lctrl_held && !is_lshift_held && !is_rgui_held && !is_ralt_held && !is_rctrl_held && !is_rshift_held) {
        // oled_write_ln_P(PSTR("No MOD held :)"), false);
        oled_layer_wpm();
    }
}


#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_left()) {
        oled_homerow_mods();
    }
     else {
        render_logo();
    }

    return true;
}
#endif

/// Combos
enum combos {
    WE_UP,
    SD_DOWN,
    DF_BACKSPACE,
    MV_CAPSLOCK
};

const uint16_t PROGMEM up[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM down[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM backspace[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM capslock[] = {LSFT_T(KC_V), RSFT_T(KC_M), COMBO_END};


combo_t key_combos[] = {
   [WE_UP] = COMBO(up, KC_UP),
   [SD_DOWN] = COMBO(down, KC_DOWN),
   [DF_BACKSPACE] = COMBO(backspace, KC_BSPC),
   [MV_CAPSLOCK] = COMBO(capslock, KC_CAPS_LOCK)
};


// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * QWERTY
 * ,---------------------------------.     ,----------------------------------.
 * |  Q  |  W   |  E   |  R   |  T   |     |  Y   |  U   |  I   |  O   |  P   |
 * |-----+------+------+------+------|     |------+------+------+------+------|
 * |  A  |  S   |  D   |  F   |  G   |     |  H   |  J   |  K   |  L   |  ;   |
 * |-----+------+------+------+------|     ,------+------+------+------+------|
 * |GUI-Z|ALT-X |CTL-C |SFT-V |  B   |     |  N   |SFT-M | CTL-,| ALT-.| GUI-'|
 * `------------+------+------+------|     |------+------+------+-------------'
 *              | Esc  | Ent  | Tab  |     |BSpc | Spc  | Esc  |
 *              `--------------------'     `--------------------'
 */
[_QWERTY] = LAYOUT_split_3x5_3(
    KC_Q,         KC_W,          KC_E,           KC_R,          KC_T,          KC_Y,          KC_U,           KC_I,            KC_O,           KC_P,
    KC_A,         KC_S,          KC_D,           KC_F,          KC_G,          KC_H,          KC_J,           KC_K,            KC_L,           KC_SCLN,
   MT(MOD_LGUI, KC_Z), MT(MOD_LALT, KC_X), MT(MOD_LCTL, KC_C), MT(MOD_LSFT, KC_V),  KC_B,          KC_N,      MT(MOD_RSFT, KC_M),   MT(MOD_RCTL,KC_COMM), MT(MOD_RALT,KC_DOT), MT(MOD_RGUI,KC_QUOT),
                   KC_ESC,       LT(1, KC_ENT),  LT(3, KC_TAB), KC_BSPC,       LT(2, KC_SPC), KC_ESC
),

/*
 * SYMBOL
 * ,----------------------------------.     ,----------------------------------.
 * |  !  |  @   |  #   |  $   |  %   |     |  7   |  8   |  9   |  -   |  =   |
 * |-----+------+------+------+------|     |------+------+------+------+------|
 * |  ^  |  &   |  *   |  (   |  )   |     |  4   |  5   |  6   |  /   |  \   |
 * |-----+------+------+------+------|     ,------+------+------+------+------|
 * |  `  |  [   |  ]   |  {   |  }   |     |  1   |  2   |  3   |  .   |  '   |
 * `------------+------+------+------|     |------+------+------+-------------'
 *              |      |      |      |     |      |      |  0   |
 *              `--------------------'     `--------------------'
 */
[_SYMBOL] = LAYOUT_split_3x5_3(
    LSFT(KC_1),   LSFT(KC_2),    LSFT(KC_3),     LSFT(KC_4),    LSFT(KC_5),    KC_P7,         KC_P8,          KC_P9,           KC_MINS,        KC_EQL,
    LSFT(KC_6),   LSFT(KC_7),    LSFT(KC_8),     LSFT(KC_9),    LSFT(KC_0),    KC_P4,         KC_P5,          KC_P6,           KC_SLSH,        KC_BSLS,
    KC_GRV,       KC_LBRC,       KC_RBRC,        LSFT(KC_LBRC), LSFT(KC_RBRC), KC_P1,         KC_P2,          KC_P3,           KC_PDOT,        KC_QUOT,
                   KC_TRNS,      KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_P0
),

/*
 * NAVIGATION
 * ,----------------------------------.     ,----------------------------------.
 * |      |      |      |      |      |     |      |      |      |      |      |
 * |-----+------+------+------+------|     |------+------+------+------+------|
 * |      |      |      |      |      |     | Left | Down |  Up  | Right|      |
 * |-----+------+------+------+------|     ,------+------+------+------+------|
 * |      |      |      |      |      |     |RCS-TB|      |      |RCTL-TB|     |
 * `------------+------+------+------|     |------+------+------+-------------'
 *              |      |      |      |     |      |      |      |
 *              `--------------------'     `--------------------'
 */
[_NAV] = LAYOUT_split_3x5_3(
    KC_TRNS,      KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,         KC_TRNS,        KC_TRNS,
    KC_TRNS,      KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_LEFT,       KC_DOWN,        KC_UP,           KC_RGHT,        KC_TRNS,
    KC_TRNS,      KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_TRNS,       RCS(KC_TAB),   KC_TRNS,        KC_TRNS,         RCTL(KC_TAB),   KC_TRNS,
                   KC_TRNS,      KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS
),

/*
 * FUNCTION
 * ,----------------------------------.     ,----------------------------------.
 * |      |      |      |      |      |     |      |      |      |      |      |
 * |-----+------+------+------+------|     |------+------+------+------+------|
 * |      |      |      |      |      |     | F1   | F2   | F3   | F4   | F5   |
 * |-----+------+------+------+------|     ,------+------+------+------+------|
 * |      |      |      |      |      |     |      |      |      |      |      |
 * `------------+------+------+------|     |------+------+------+-------------'
 *              |      |      |      |     |      |      |      |
 *              `--------------------'     `--------------------'
 */
[_FUNC] = LAYOUT_split_3x5_3(
    KC_TRNS,      KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,         KC_TRNS,        KC_TRNS,
    KC_TRNS,      KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_F1,         KC_F2,          KC_F3,           KC_F4,          KC_F5,
    KC_TRNS,      KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,         KC_TRNS,        KC_TRNS,
                   KC_TRNS,      KC_TRNS,        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS
)
};

// RGB Light settings
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _SYMBOL:
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
    case _NAV:
        rgblight_sethsv_noeeprom(HSV_CYAN);
        break;
    case _FUNC:
        rgblight_sethsv_noeeprom(HSV_YELLOW);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv_noeeprom(HSV_BLUE);
        break;
    }
  return state;
}

void keyboard_post_init_user(void) {
    // Set default RGB on startup
    rgblight_enable();
    rgblight_sethsv_noeeprom(HSV_BLUE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
