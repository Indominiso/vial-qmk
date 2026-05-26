/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
 * Modification for Vial support by Drew Petersen
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

// clang-format off

#include QMK_KEYBOARD_H
#include "oled.c"

// Default keymap. This can be changed in Vial. Use oled.c to change beavior that Vial cannot change.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_GRV,
    KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_BSPC,
    KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,   XXXXXXX, KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
                    KC_LGUI, KC_LALT, KC_LCTL,  MO(1), KC_SPC,     KC_ENT,  MO(2), KC_RCTL, KC_RALT, KC_RGUI
  ),

  [1] = LAYOUT(
    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
    KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12,
    _______, KC_EXLM,   KC_AT, KC_HASH,   KC_DLR, KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
    _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, LCTL(KC_0),       _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                            _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
  ),

  [2] = LAYOUT(
    _______, _______, MEH(KC_P),  KC_MPRV, KC_MNXT, KC_MPLY,                      _______, _______, _______, _______, _______, _______,
    _______,  KC_INS,   KC_PSCR,  KC_APP, XXXXXXX, KC_CAPS,                       KC_PGUP, _______,   KC_UP, _______, _______, KC_BSPC,
    _______, KC_LALT,   KC_LCTL, KC_LSFT, XXXXXXX, LCA(KC_F12),                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC,
    _______, KC_UNDO,    KC_CUT, KC_COPY,KC_PASTE, XXXXXXX, LCTL(KC_S),     LCTL(KC_W), _______, XXXXXXX, _______, XXXXXXX, _______, _______,
                            _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  )
};

// const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
//     [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
//     [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
//     [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
// };

// Alt+Tab timeout state
static bool is_alt_tab_active = false;
static uint32_t alt_tab_timer = 0;
#define ALT_TAB_TIMEOUT 1000

void matrix_scan_user(void) {
    if (is_alt_tab_active && timer_elapsed32(alt_tab_timer) > ALT_TAB_TIMEOUT) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state);

    if (index == 0) { 
        switch (layer) {
            case 0: 
                tap_code(clockwise ? KC_VOLU : KC_VOLD);
                break;
            case 1: 
                tap_code16(clockwise ? LCTL(KC_EQL) : LCTL(KC_MINS));
                break;
            case 2: 
                tap_code16(clockwise ? LCTL(KC_Y) : LCTL(KC_Z));
                break;
        }
    } else if (index == 1) { 
        switch (layer) {
            case 0: 
                tap_code(clockwise ? KC_DOWN : KC_UP);
                break;
            case 1: 
                tap_code(clockwise ? KC_RGHT : KC_LEFT);
                break;
            case 2: 
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read32();
                tap_code16(clockwise ? KC_TAB : LSFT(KC_TAB));
                break;
        }
    }
    
    return false;
}

void keyboard_post_init_user(void) {
    rgb_matrix_sethsv_noeeprom(197, 214, 128);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}
