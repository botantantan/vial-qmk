/*
 * Copyright 2024 @DreaM117er
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

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Main Keyboard Hand*/
#define USE_SERIAL
#define SERIAL_USE_MULTI_TRANSACTION
// #define MASTER_RIGHT
#define EE_HANDS

/* layer count */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

/* tapping term */
#define TAPPING_TERM 200 /* global */

/* One shot key */
#define ONESHOT_TAP_TOGGLE 3  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 2000  /* Time (in ms) before the one shot key is released */

/* Encoder EC-11 */
#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }
#define ENCODER_RESOLUTIONS { 4 }
#define ENCODERS_PAD_A_RIGHT { F5 }
#define ENCODERS_PAD_B_RIGHT { F4 }
#define ENCODER_RESOLUTIONS_RIGHT { 4 }
#define TAP_CODE_DELAY 10

/* Pointing Device Setting*/
#define CIRQUE_PINNACLE_CURVED_OVERLAY
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_RELATIVE_MODE
#define CIRQUE_PINNACLE_TAP_ENABLE
// #define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_ROTATION_90
// #define POINTING_DEVICE_GESTURES_SCROLL_ENABLE

// sensitivity, default 4x, curved overlay min 2x
#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_1X

// experimental buat tau speed nambah ato engga, jawabannya iya
#define SELECT_SOFT_SERIAL_SPEED 0
#define SPLIT_MAX_CONNECTION_ERRORS 5

/* I2C or SPI Setting*/
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN D0
#define I2C1_SDA_PIN D1

#ifdef VIAL_ENABLE
  #define VIAL_TAP_DANCE_ENTRIES 4
  #define VIAL_KEY_OVERRIDE_ENTRIES 0
  #define VIAL_COMBO_ENTRIES 3
#endif

/* memory saving */
#ifndef NO_DEBUG
  #define NO_DEBUG
#endif
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
  #define NO_PRINT
#endif