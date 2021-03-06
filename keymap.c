#include "gh60.h"
#include "action_layer.h"
#include "rgblight.h"

#define _DEFAULT 0
#define _FN 1
#define _WIN 2
#define _WASD 3
#define _SFX 3

//bool esc_led_on;

enum planck_keycodes {
  DEFAULT = SAFE_RANGE
};

enum {
 CT_SE = 0,
 i_TERM,
 CT_EGG,
 CT_FLSH,
 X_TAP_DANCE
};

void dance_iterm_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_ESC);
  } else {
    register_code (KC_LALT);
    register_code (KC_SPC);
  }
}

void dance_iterm_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_ESC);
  } else {
    unregister_code (KC_LALT);
    unregister_code (KC_SPC);
  }
}

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
 [i_TERM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_iterm_finished, dance_iterm_reset)
};

// Fillers to make layering more clear
#define ______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty gui/alt/space/alt/gui
 * ,-----------------------------------------------------------------------------------------.
 * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | fn2 | BS  |
 * |-----------------------------------------------------------------------------------------+
 * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   \    |
 * |-----------------------------------------------------------------------------------------+
 * | fn1     |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
 * |-----------------------------------------------------------------------------------------+
 * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | RShift    | FN  |
 * |-----------------------------------------------------------------------------------------+
 *         |LAlt | LGUI  |               Space                | CTRL  | RAlt |
 *         `-----------------------------------------------------------------'
 */
  [_DEFAULT] = KEYMAP_HHKB( /* Basic QWERTY */
      TD(i_TERM),  KC_1,    KC_2,    KC_3, KC_4, KC_5,   KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_1, KC_BSLS, \
      KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T,   KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,  \
      MO(_FN), KC_A,    KC_S,    KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  \
      OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C, KC_V, KC_B,   KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN), \
      ______,  KC_LALT, KC_LGUI,             KC_SPC,             KC_RALT, KC_LCTL, ______,  ______ \
      ),


  [_WIN] = KEYMAP_HHKB( /* Basic QWERTY */
      KC_ESC,  KC_1,    KC_2,    KC_3, KC_4, KC_5,   KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, KC_1, KC_BSLS, \
      KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T,   KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,  \
      KC_LCTL, KC_A,    KC_S,    KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  \
      OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C, KC_V, KC_B,   KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN), \
      ______,  KC_LGUI, KC_LALT,             KC_SPC,             KC_RALT, KC_RGUI, ______,  ______ \
      ),

/* WASD Layer
 * ,-----------------------------------------------------------------------------------------.
 * |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
 * |-----------------------------------------------------------------------------------------+
 * |        |     | Up  |     |     |     |     |     |     |     |     |     |     |        |
 * |-----------------------------------------------------------------------------------------+
 * |         | Left| Down|Right|     |     |     |     |     |     |     |     |             |
 * |-----------------------------------------------------------------------------------------+
 * |           |     |     |     |     |     |     |     |      |    |     |           |     |
 * |-----------------------------------------------------------------------------------------+
 *         |       |       |                                 |       |       |
 *         `-----------------------------------------------------------------'
 */
  [_FN] = KEYMAP_HHKB( /* Layer 2 */
      ______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_VOLD, KC_VOLU, ______,  KC_DEL, \
      LCTL(KC_TAB),   ______,  ______,  ______, ______, ______, ______, ______, ______, ______, ______, KC_MPRV, KC_MPLY, KC_MNXT,  \
      ______,   ______, ______,  ______,______, ______, ______, KC_DOWN, KC_UP, KC_LEFT, KC_RGHT, KC_GRAVE, ______,   \
      ______,   ______,  KC_BSPC, LCTL(KC_C), ______, ______, ______, ______, ______, ______, S(KC_GRAVE), ______,______,  \
      ______,   ______,  ______,                KC_ENT,                 ______, ______, ______, ______ \
      )
};
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  return MACRO_NONE;
};

enum function_id {
    RGBLED_TOGGLE,
    RGBLED_STEP_MODE,
    RGBLED_INCREASE_HUE,
    RGBLED_DECREASE_HUE,
    RGBLED_INCREASE_SAT,
    RGBLED_DECREASE_SAT,
    RGBLED_INCREASE_VAL,
    RGBLED_DECREASE_VAL
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(RGBLED_TOGGLE),
  [1]  = ACTION_FUNCTION(RGBLED_STEP_MODE),
  [2]  = ACTION_FUNCTION(RGBLED_INCREASE_HUE),
  [3]  = ACTION_FUNCTION(RGBLED_DECREASE_HUE),
  [4]  = ACTION_FUNCTION(RGBLED_INCREASE_SAT),
  [5]  = ACTION_FUNCTION(RGBLED_DECREASE_SAT),
  [6]  = ACTION_FUNCTION(RGBLED_INCREASE_VAL),
  [7]  = ACTION_FUNCTION(RGBLED_DECREASE_VAL)
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
    case RGBLED_TOGGLE:
      if (record->event.pressed) {
        rgblight_toggle();
      }
      break;
    case RGBLED_INCREASE_HUE:
      if (record->event.pressed) {
        rgblight_increase_hue();
      }
      break;
    case RGBLED_DECREASE_HUE:
      if (record->event.pressed) {
        rgblight_decrease_hue();
      }
      break;
    case RGBLED_INCREASE_SAT:
      if (record->event.pressed) {
        rgblight_increase_sat();
      }
      break;
    case RGBLED_DECREASE_SAT:
      if (record->event.pressed) {
        rgblight_decrease_sat();
      }
      break;
    case RGBLED_INCREASE_VAL:
      if (record->event.pressed) {
        rgblight_increase_val();
      }
      break;
    case RGBLED_DECREASE_VAL:
      if (record->event.pressed) {
        rgblight_decrease_val();
      }
      break;
    case RGBLED_STEP_MODE:
      if (record->event.pressed) {
        rgblight_step();
      }
      break;
  }
}

void matrix_scan_user(void) {
    uint32_t layer = layer_state;

    if (layer & (1<<1)) {
        gh60_fn_led_on();
    } else {
        gh60_fn_led_off();
    }

    if (layer & (1<<2)) {
        gh60_wasd_leds_on();
    } else {
        gh60_wasd_leds_off();
    }

    if (layer & (1<<3)) {
        gh60_esc_led_on();
    } else {
        gh60_esc_led_off();
    }
};
