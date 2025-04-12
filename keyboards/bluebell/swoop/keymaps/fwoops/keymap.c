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

#if __has_include("keymap.h")
#    include "keymap.h"
#endif

/**
 * Put this somewhere at the beginning of the file --
 * Make sure you import only one of animations at a time
 * They all have same function exported, so it won't compile if you
 * include more than one at a time. You can also configure some options
 * before including the animation. Not all animations support them, but some do :P.
 */
#define ANIM_INVERT false
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 45 // Switch to fast animation when over words per minute

#ifdef OLED_ENABLE
#    include "demon.c"
#endif

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(crkbd_logo, false);
}


#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_left()) {
        oled_render_anim();
    } else {
        oled_render_logo();
    }

    return true;
}
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}
#endif


enum layers {
    _QWERTY,
    _SYMBOL,
    _NAV,
    _FUNC
};

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
    LGUI_T(KC_Z), LALT_T(KC_X),  LCTL_T(KC_C),   LSFT_T(KC_V),  KC_B,          KC_N,          RSFT_T(KC_M),   RCTL_T(KC_COMM), RALT_T(KC_DOT), RGUI_T(KC_QUOT),
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
