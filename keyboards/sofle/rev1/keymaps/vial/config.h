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
#pragma once

#define MASTER_LEFT // allows you to flip layouts with vial by assigning EEH LEFT or EEH RIGHT to a key 
// #define EE_HANDS // allows you to flip layouts with vial by assigning EEH LEFT or EEH RIGHT to a key 
#define SPLIT_USB_DETECT // fixes non USB side not getting power
#define SPLIT_TRANSPORT_MIRROR // syncs data between the halves so they don't have independent vial layouts
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WPM_ENABLE // makes wpm counter work on both halves, not just the master

#define OLED_TIMEOUT 20000
#define RGB_MATRIX_TIMEOUT 20000
#define RGB_MATRIX_SLEEP // allows RGB to turn off when the computer goes to sleep
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128  // for rgb_matrix

// default rgb effects
#define ENABLE_RGB_MATRIX_SOLID_COLOR
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE   
// cool rgb effects to play around with
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#define ENABLE_RGB_MATRIX_RIVERFLOW
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_STARLIGHT
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_ALPHAS_MODS 
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING 
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_FLOWER_BLOOMING    
#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP 
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL    // fractal geometric pattern, very different from anything you have
#define ENABLE_RGB_MATRIX_PIXEL_RAIN       // individual pixels fall like rain (different from DIGITAL_RAIN)
#define ENABLE_RGB_MATRIX_PIXEL_FLOW       // pixels flow across the board
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN     // rainbow radiates from center outward
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL // same but two centers
#define ENABLE_RGB_MATRIX_HUE_PENDULUM     // hue swings back and forth like a pendulum

// vial stuff
#define VIAL_KEYBOARD_UID { 0x05, 0xCD, 0x9F, 0x8A, 0xF4, 0xDF, 0xDE, 0xB2 }
#define VIAL_UNLOCK_COMBO_ROWS { 0, 5, 3, 8 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0, 0, 0 }