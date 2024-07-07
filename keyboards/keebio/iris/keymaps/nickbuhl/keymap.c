#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"

#define _COLEMAK 0
#define _LOWER 1
#define _RAISE 2
//#define _NUMPAD 3

//#define TAB_NUM LT(NUMPAD,KC_TAB)

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  RAISE,
  //NUMPAD,
  UNAME//,
  //DSK_LFT,
  //DSK_RGT,
  //DSK_WIN,
  //DSK_APP
};

// Key Overrides
// const key_override_t period_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_DQUO);
// const key_override_t comma_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_QUOT);
// const key_override_t lt_key_override     = ko_make_basic(MOD_MASK_SHIFT, KC_LT, KC_GT);
// const key_override_t lcbr_key_override   = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_RCBR);
// const key_override_t lbrc_key_override   = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_RBRC);

// const key_override_t **key_overrides = (const key_override_t *[]){
//   &period_key_override,
//   &comma_key_override,
//   &lt_key_override,
//   &lcbr_key_override,
//   &lbrc_key_override,
//   NULL
// };

//  Using Custom shift keys
//  Pascal Getreuer, 2021-10-30 (updated 2023-01-04) 
const custom_shift_key_t custom_shift_keys[] = {
 {KC_DOT , KC_DQUO},  // Shift . is "
 {KC_COMM, KC_QUOT},  // Shift , is '
 {KC_LT,   KC_GT  },  // Shift < is >
 {KC_LCBR, KC_RCBR},  // Shift { is } 
 {KC_LBRC, KC_RBRC},  // Shift [ is ] 
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
   sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// Using Auto-Shift and adding the above custom shift keys
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
   switch(keycode) {
       case KC_DOT:
       case KC_COMM:
       case KC_LT:
       case KC_LCBR:
       case KC_LBRC:
           return true;
       default:
            return false;
    }
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            register_code16((!shifted) ? KC_DOT : KC_DQUO);
            break;
        case KC_COMM:
            register_code16((!shifted) ? KC_COMM : KC_QUOT);
            break;
        case KC_LT:
            register_code16((!shifted) ? KC_LT : KC_GT);
            break;
        case KC_LCBR:
            register_code16((!shifted) ? KC_LCBR : KC_RCBR);
            break;
        case KC_LBRC:
            register_code16((!shifted) ? KC_LBRC : KC_RBRC);
            break;
        default:
            if (shifted) {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    switch(keycode) {
        case KC_DOT:
            unregister_code16((!shifted) ? KC_DOT : KC_DQUO);
            break;
        case KC_COMM:
            unregister_code16((!shifted) ? KC_COMM : KC_QUOT);
            break;
        case KC_LT:
            unregister_code16((!shifted) ? KC_LT : KC_GT);
            break;
        case KC_LCBR:
            unregister_code16((!shifted) ? KC_LCBR : KC_RCBR);
            break;
        case KC_LBRC:
            unregister_code16((!shifted) ? KC_LBRC : KC_RBRC);
            break;
        default:
            // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
            // The IS_RETRO check isn't really necessary here, always using
            // keycode & 0xFF would be fine.
            unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode);
    }
}

// Hand swap to mirror keyboard and allow for one-hand typing.
// [row][col] maps to [col][row] in keypos_t
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
  {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
  {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
  {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}},
  {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}},
  {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}},
  {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}},
  {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}},
  {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}},
  {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}},
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_CAPS,                            UNAME,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    SH_TT,                              UNAME,   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_TAB,                             KC_RSFT, KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_LCTL, SH_TT,            _______, KC_RALT, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    RAISE,   KC_BSPC, KC_LGUI,                   KC_ENT,   KC_SPC,  LOWER 
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, RGB_SAI, _______, _______, BL_STEP, RGB_TOG,                            BL_TOGG, BL_BRTG, _______, _______, RGB_SAD, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRAVE, KC_BSLS, KC_EQL, KC_MINS, KC_TAB,  _______,                            _______, _______, KC_LCBR, KC_LBRC, KC_LT,   UNAME,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,                            _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, _______, _______, _______,          _______, _______, _______, KC_RALT, KC_RGUI, KC_RCTL, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    XXXXXXX, _______, _______,                  _______,  _______, XXXXXXX
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     RGB_HUI, RGB_SPI, RGB_MOD, RGB_VAI, BL_INC,  _______,                            BL_DEC,  RGB_VAD, RGB_RMOD,RGB_SPD, RGB_HUD, CG_TOGG,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                            _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_F11,  _______,                            _______, KC_F12,  KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_INS,  KC_PSCR, KC_SCRL, KC_PAUS, KC_DEL,  _______, _______,          _______, _______, KC_ESC,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    XXXXXXX, _______,  _______,                   _______, _______, XXXXXXX
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )//,

  // [_NUMPAD] = LAYOUT(
  // //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  // //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //    _______, _______, DSK_WIN, _______, _______, _______,                            _______, KC_LBRC,    KC_7,    KC_8,    KC_9,  KC_EQL,
  // //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //    _______, DSK_LFT, DSK_APP, DSK_RGT, KC_F11,  _______,                             _______, KC_LCBR,    KC_4,    KC_5,    KC_6, KC_MINS,
  // //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //    _______, _______, _______, _______, _______, _______, _______,          _______, _______,   KC_LT,    KC_1,    KC_2,    KC_3, KC_BSLS,
  // //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
  //                                   XXXXXXX, XXXXXXX, _______,                   _______,    KC_0,  XXXXXXX
  //                               // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  // )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_custom_shift_keys(keycode, record)) { return false; }
  
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;

    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;

    // case NUMPAD:
    //   if (record->event.pressed) {
    //     layer_on(_NUMPAD);
    //   } else {
    //     layer_off(_NUMPAD);
    //   }
    //   return false;
    //   break;

    case UNAME:
      if (record->event.pressed) {
          SEND_STRING("buhlnk");
      }
      return false;
      break;

    // case LT(0,KC_NO):
    //   if (record->tap.count && record->event.pressed) {
    //     tap_code(KC_SPACE); // Intercept tap to send space
    //   } else if (record->event.pressed) {
    //     tap_code(KC_ENTER); // Intercept hold function to send enter
    //   }
    //   return false;
    //   break;

    // case DSK_LFT:
    //   if (record->event.pressed) {
    //     SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
    //   }
    //   return false;
    //   break;

    // case DSK_RGT:
    //   if (record->event.pressed) {
    //     SEND_STRING(SS_LCTL(SS_TAP(X_RGHT)));
    //   }
    //   return false;
    //   break;      

    // case DSK_WIN:
    //   if (record->event.pressed) {
    //     SEND_STRING(SS_LCTL(SS_TAP(X_UP)));
    //   }
    //   return false;
    //   break;      

    // case DSK_APP:
    //   if (record->event.pressed) {
    //     SEND_STRING(SS_LCTL(SS_TAP(X_DOWN)));
    //   }
    //   return false;
    //   break;    

  }
  return true;
}
