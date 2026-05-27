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

bool     rgb_hud_active = false;
uint32_t rgb_hud_timer  = 0;
#define  RGB_HUD_TIMEOUT_MS 10000

typedef enum { RGB_TW_HUE, RGB_TW_SAT, RGB_TW_VAL, RGB_TW_SPD, RGB_TW_MOD, RGB_TW_COUNT } rgb_tweak_mode_t;
rgb_tweak_mode_t rgb_tweak_mode = RGB_TW_HUE;

enum custom_keycodes {
    RGB_TW_NEXT = SAFE_RANGE,
};


#include "oled.c"

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
    _______, KC_UNDO,    KC_CUT, KC_COPY,KC_PASTE, XXXXXXX, LCTL(KC_S),     RGB_TW_NEXT, _______, XXXXXXX, _______, XXXXXXX, _______, _______,
                            _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  )
};

#ifdef RGB_MATRIX_ENABLE
// Apply a distinct RGB effect per layer
static void apply_layer_rgb(uint8_t layer) {
    switch (layer) {
        case 1:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(177, 214, 128);
            break;
        case 2:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(217, 214, 128);
            break;
        default:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_RIVERFLOW);
            rgb_matrix_sethsv_noeeprom(197, 214, 128);
            break;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    apply_layer_rgb(get_highest_layer(state));

    return state;
}

void keyboard_post_init_user(void) {
    apply_layer_rgb(0);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == RGB_TW_NEXT && record->event.pressed) {
        rgb_tweak_mode = (rgb_tweak_mode + 1) % RGB_TW_COUNT;
        rgb_hud_active = true;
        rgb_hud_timer  = timer_read32();
    }
    return true;
}
#endif

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state);
    if (index == 0) {
        rgb_hud_active = false;

        switch (layer) {
            case 0: tap_code(clockwise ? KC_VOLU : KC_VOLD); break;
            case 1: tap_code16(clockwise ? LCTL(KC_EQL) : LCTL(KC_MINS)); break;
            case 2: tap_code16(clockwise ? LCTL(KC_Y) : LCTL(KC_Z)); break;
        }
    } else if (index == 1) {
        switch (layer) {
            case 0: tap_code(clockwise ? KC_DOWN : KC_UP); break;
            case 1: tap_code(clockwise ? KC_RGHT : KC_LEFT); break;
            case 2:
                #ifdef RGB_MATRIX_ENABLE
                rgb_hud_active = true;
                rgb_hud_timer  = timer_read32();
                switch (rgb_tweak_mode) {
                    case RGB_TW_HUE: clockwise ? rgb_matrix_increase_hue_noeeprom() : rgb_matrix_decrease_hue_noeeprom(); break;
                    case RGB_TW_SAT: clockwise ? rgb_matrix_increase_sat_noeeprom() : rgb_matrix_decrease_sat_noeeprom(); break;
                    case RGB_TW_VAL: clockwise ? rgb_matrix_increase_val_noeeprom() : rgb_matrix_decrease_val_noeeprom(); break;
                    case RGB_TW_SPD: clockwise ? rgb_matrix_increase_speed_noeeprom() : rgb_matrix_decrease_speed_noeeprom(); break;
                    case RGB_TW_MOD: clockwise ? rgb_matrix_step_noeeprom() : rgb_matrix_step_reverse_noeeprom(); break;
                    default: break;
                }
                #endif
                
                break;
        }
    }
    return false;
}

void housekeeping_task_user(void) {
    if (rgb_hud_active && timer_elapsed32(rgb_hud_timer) > RGB_HUD_TIMEOUT_MS) {
        rgb_hud_active = false;
    }
}