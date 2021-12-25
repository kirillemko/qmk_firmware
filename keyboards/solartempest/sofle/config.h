/* Copyright
 *   2021 solartempest
 *   2021 QMK
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
#include "config_common.h"

// USB Device descriptor parameter
#define VENDOR_ID       0xFC32
#define PRODUCT_ID      0x1287 //Original is 0x0287 but do not want to load default VIA keymap
#define DEVICE_VER      0x0002
#define MANUFACTURER    KiEM
#define PRODUCT         KiEM_KRBD //VIA version for this PCB is incorrect for the bottom row
#define DESCRIPTION     Kirill Emelianenko keyboard

// Set which side is master
//#define EE_HANDS //Use this instead for EEPROM setting
#define MASTER_LEFT



// Key matrix size
// Rows are doubled-up. Added extra column for rotary encoder VIA mapping.
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

// wiring of each half
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
//#define MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, C7 } //C7 is unused on the MCU. It is needed for the encoder key matrix in via.
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6, C7 }
#define MATRIX_ROW_PINS_RIGHT { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS_RIGHT { F6, F7, B1, B3, B2, B6, C7 } //C7 is unused on the MCU. It is needed for the encoder key matrix in via.
#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 6 //Default is 5

// Encoder support
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODERS_PAD_A_RIGHT { F4 }
#define ENCODERS_PAD_B_RIGHT { F5 }
#define ENCODER_RESOLUTIONS { 2, 2 } //Left encoder seems to have double-output issue but right does not.

#define TAP_CODE_DELAY 10
#define TAPPING_TOGGLE 2 //Tap TT twice to toggle layer
#define TAPPING_TERM 160 //Tapping duration in ms

// Communication between sides
#define SOFT_SERIAL_PIN D2

// Disabled for LTO
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// Disabled to save space
//#define NO_RESET //Save 40 bytes

//#define NO_ACTION_ONESHOT //Save 244 bytes
#define ONESHOT_TAP_TOGGLE 4  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 4000  /* Time (in ms) before the one shot key is released */

// OLED settings
#ifdef OLED_ENABLE
	#define OLED_TIMEOUT 30000 //120000 = 2 minutes in ms.
//	#define OLED_TIMEOUT 5000 //120000 = 2 minutes in ms.
	#define OLED_BRIGHTNESS 80 // Default 100.

	#define SPLIT_OLED_ENABLE //Synx on/off OLED state between halves (+100).
	//#define SPLIT_WPM_ENABLE
    #define SPLIT_MODS_ENABLE
    #define SPLIT_LAYER_STATE_ENABLE
    #define SPLIT_LED_STATE_ENABLE

//	#define OLED_LOGO //Enable to print snakey custom logo on slave side, disable to save space.
#endif

// Combo settings
#ifdef COMBO_ENABLE
	#define COMBO_COUNT 1 //Number of tap combos used
	#define COMBO_TERM 400 //Default combo time is 200ms. This is the time delay allowed between deleting each whole word with shift-backspace.
#endif


// Add RGB underglow
//#define RGBLIGHT_ANIMATIONS

#define RGBLIGHT_EFFECT_BREATHING
// +1kb
//#undef RGBLIGHT_EFFECT_BREATHE_TABLE
//#define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85
//#define RGBLIGHT_EFFECT_BREATHE_MAX    170

//#define RGB_DI_PIN D3
//#define RGBLED_NUM 74
//#define RGBLED_SPLIT {37,37}
//#define RGBLIGHT_ANIMATIONS // Very memory intensive
//#define RGBLIGHT_EFFECT_STATIC_GRADIENT //Firmware size (+262)
//#define RGBLIGHT_LIMIT_VAL 160 //Power draw may exceed 0.6A at max brightness with white colour.
//#define RGBLIGHT_LAYERS
//#define RGBLIGHT_SLEEP
//#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF //Shows lock key lighting status even when RGB is off




//#define RGBLIGHT_LAYERS
//#define RGBLIGHT_MAX_LAYERS 4
//#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF


