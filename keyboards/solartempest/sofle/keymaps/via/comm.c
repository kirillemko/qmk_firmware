
#ifdef OLED_ENABLE
uint32_t oled_timer = 0; //OLED timeout
	led_t led_usb_state;

	static void print_slave_OLED(void) {

	    oled_set_cursor(0,1);
        oled_write("LAYER", false);

        oled_set_cursor(0,3);
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write("Base ", false);
                break;
            case 1:
                oled_write("1    ", false);
                break;
            case 2:
                oled_write("2    ", false);
                break;
        }


//		oled_set_cursor(0,5);
//		oled_write("LOCK", false);
        oled_set_cursor(0,6);
        oled_write("Caps", led_usb_state.caps_lock);
//		oled_set_cursor(0,7);
//		oled_write("Num", !(led_usb_state.num_lock));
        oled_set_cursor(0,8);
        if( led_usb_state.scroll_lock ){
            oled_write(" Rus ", true);
        } else {
            oled_write("     ", false);
        }

	}

	static void print_master_OLED(void) {
		oled_set_cursor(0,1);
        oled_write("KiEM", false);
        oled_set_cursor(0,2);
        oled_write("Key", false);
        oled_set_cursor(0,3);
        oled_write("Board", false);

        oled_set_cursor(0,10);
        oled_write("CPU", false);

        oled_set_cursor(0,14);
        oled_write("FrMem", false);
	}

	oled_rotation_t oled_init_user(oled_rotation_t rotation) {
		return OLED_ROTATION_270;
	}

	bool oled_task_user(void) {
		led_usb_state = host_keyboard_led_state();

//		if (is_keyboard_master()) { //Drashna's OLED timeout off code for animations
//        			if (timer_elapsed32(oled_timer) > 5000) {
//        				oled_off();
////        				oled_set_brightness(0);
////        				return;
//        			} else {
////        			oled_timer=0;
//                        oled_timer = timer_read32();
//        				oled_on();
////        			    oled_set_brightness(200);
//        			}
//        		}

		if (is_keyboard_master()) {
			print_master_OLED();
		} else {
			print_slave_OLED();
		}
        return true;
	}




#ifdef VIA_ENABLE

    enum external_commands {
        // col | row | text
        command_set_text = 0xD0
    };

	#include "raw_hid.h"


    void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
        uint8_t *command_id   = &(data[0]);
        uint8_t *command_data = &(data[1]);

        if( *command_id != id_set_keyboard_value ){
            return;
        }

//        rgblight_sethsv_noeeprom_yellow();

        switch (command_data[0]) {
            case command_set_text: {
                oled_set_cursor(command_data[1],command_data[2]);
                for( uint8_t i=0; i<command_data[3]; i++){
                    oled_write_char(command_data[4+i], false);
                }
//            	oled_write("asd", false);
                break;
            }
            default: {
                break;
            }
        }
    }
#endif //VIA_ENABLE


#endif
