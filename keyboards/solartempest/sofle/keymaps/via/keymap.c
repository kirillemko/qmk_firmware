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

#include QMK_KEYBOARD_H
#include <stdio.h> //This is required for OLED sprintf.
#include "encoder.c"
#ifdef OLED_ENABLE
//    #include "snakey_minimal.c" //OLED code for Snakey, without WPM/related animations to save space. If not used, do not use OLED_LOGO in config.h.
    #include "comm.c" //OLED code for Snakey, without WPM/related animations to save space. If not used, do not use OLED_LOGO in config.h.

    void suspend_power_down_user(void) {
        oled_off();
    }
#endif













bool is_alt_tab_active = false; // Super Alt Tab Code
uint16_t alt_tab_timer = 0;
bool lshift_held = false;	// LShift Backspace Delete whole Word Code
bool rshift_held = false;	// RShift Backspace Delete whole Word Code
static uint16_t held_shift = 0;
#ifdef VIA_ENABLE
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = USER00, 	//Alt tab forwards
	  ATABR, 			//Alt tab reverse
	  NMR, 				//Move window to monitor on right
	  NML, 				//Move window to monitor on left
	  SBS, 				//Shift backspace to delete whole word (Swap KC_BPSC with this)
      PM_SCROLL,		//Toggle trackball scrolling mode
      PM_PRECISION		//Toggle trackball precision mode
	};
#else
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
	  ATABF = SAFE_RANGE, //Alt tab forwards
	  ATABR, 			//Alt tab reverse
	  NMR, 				//Move window to monitor on right
	  NML, 				//Move window to monitor on left
	  SBS,				//Shift backspace to delete whole word (Swap KC_BPSC with this)
      PM_SCROLL,		//Toggle trackball scrolling mode
      PM_PRECISION		//Toggle trackball precision mode
	};
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {  //Can skip these layouts to save space when using only VIA.

};




//void matrix_scan_user(void) {
//  if (is_alt_tab_active) {	//Allows for use of super alt tab.
//    if (timer_elapsed(alt_tab_timer) > 1000) {
//      unregister_code(KC_LALT);
//      is_alt_tab_active = false;
//    }
//  }
//}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	#if defined(KEYBOARD_PET) || defined(OLED_LOGO)
		if (record->event.pressed) { //OLED timeout code
			oled_timer = timer_read32();
		}
	#endif

	switch (keycode) { //For keycode overrides
		case ATABF:	//Alt tab forwards
		  if (record->event.pressed) {
			if (!is_alt_tab_active) {
			  is_alt_tab_active = true;
			  register_code(KC_LALT);
			}
			alt_tab_timer = timer_read();
			register_code(KC_TAB);
		  } else {
			unregister_code(KC_TAB);
		  }
		  return true;
		case ATABR:	//Alt tab reverse
		  if (record->event.pressed) {
			if (!is_alt_tab_active) {
			  is_alt_tab_active = true;
			  register_code(KC_LALT);
			}
			alt_tab_timer = timer_read();
			register_code(KC_LSHIFT);
			register_code(KC_TAB);
		  } else {
			unregister_code(KC_LSHIFT);
			unregister_code(KC_TAB);
		  }
		  return true;

		case NMR:	//Move window to next monitor on right
		  if (record->event.pressed) {
			register_code(KC_LSFT);
			register_code(KC_LWIN);
			register_code(KC_RIGHT);
			unregister_code(KC_RIGHT);
			unregister_code(KC_LWIN);
			unregister_code(KC_LSFT);
		  }
		  return true;
		case NML:	//Move window to next monitor on left
		  if (record->event.pressed) {
			register_code(KC_LSFT);
			register_code(KC_LWIN);
			register_code(KC_LEFT);
			unregister_code(KC_LEFT);
			unregister_code(KC_LWIN);
			unregister_code(KC_LSFT);
		  }
		  return true;

		case KC_RSFT: //Shift Backspace to Delete Whole Word. Inspired by Hellsingcoder.
			rshift_held = record->event.pressed;
			held_shift = keycode;
			#ifdef KEYBOARD_PET // KEYBOARD PET STATUS
				if (record->event.pressed) {
					isBarking = true;
				} else {
					isBarking = false;
				}
			#endif
			return true;
		case MOD_LSFT:
//		    if (record->event.pressed) {
//                rgblight_mode_noeeprom(1);
//                rgblight_sethsv_noeeprom_pink();
//            } else {
//                rgblight_reload_from_eeprom();
//            }

//			lshift_held = record->event.pressed;
//			held_shift = keycode;
//			#ifdef KEYBOARD_PET // KEYBOARD PET STATUS
//				if (record->event.pressed) {
//					isBarking = true;
//				} else {
//					isBarking = false;
//				}
//			#endif
			return true;
		case SBS:
			if (record->event.pressed) { //When left shift is held and backspace pressed, one whole word will be deleted (left).
				if (lshift_held) {
					unregister_code(held_shift);
					register_code(KC_LCTL);
					register_code(KC_BSPC);
				} else if (rshift_held) { //When left shift is held and backspace pressed, one whole word will be deleted (right).
					unregister_code(held_shift);
					register_code(KC_LCTL);
					register_code(KC_DEL);
				} else {
					register_code(KC_BSPC);
				}
			} else {
				unregister_code(KC_BSPC);
				unregister_code(KC_DEL);
				unregister_code(KC_LCTL);
				if (lshift_held || rshift_held) {
					register_code(held_shift);
				}
			}
			return false;


		#ifdef KEYBOARD_PET // KEYBOARD PET STATUS
			case KC_LCTL:
			case KC_RCTL:
				if (record->event.pressed) { //Pet sneaks when control held.
					isSneaking = true;
				} else {
					isSneaking = false;
				}
				return true;
			case KC_SPC:
				if (record->event.pressed) { //Pet jumps when enter is pressed.
					isJumping = true;
					showedJump = false;
				} else {
					isJumping = false;
				}
				return true;
		#endif
		}
	return true;
}




#ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {
    case 0:
      rgblight_reload_from_eeprom();
      break;
    case 1:
      rgblight_mode_noeeprom(1);
      rgblight_sethsv_noeeprom_red();
      break;
    case 2:
      rgblight_mode_noeeprom(1);
      rgblight_sethsv_noeeprom_green();
      break;
    case 3:
      rgblight_mode_noeeprom(1);
      rgblight_sethsv_noeeprom_yellow();
      break;
    case 4:
      rgblight_mode_noeeprom(1);
      rgblight_sethsv_noeeprom_blue();
      break;
    }
    return state;
}
#endif // RGBLIGHT_ENABLE

#ifndef NO_ACTION_ONESHOT
void oneshot_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) {
        rgblight_mode_noeeprom(1);
        rgblight_sethsv_noeeprom_pink();
    }
    if (!mods) {
        rgblight_reload_from_eeprom();
    }
}
#endif
