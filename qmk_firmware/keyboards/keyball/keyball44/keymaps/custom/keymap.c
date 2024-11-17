/*
Copyright 2023 @takashicompany

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "quantum.h"

enum custom_keycodes {
    KANA = SAFE_RANGE,
    EISUU,
    VIM_ESC,
    INLINE,
    BLOCK,
    GATHER,
    FRAC,
    SQRT,
    LR,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t my_timer;
    switch (keycode) {
        case KANA:
            if(record->event.pressed) {
                layer_on(2);
                tap_code(KC_INT4);
            } else {
                layer_off(2);
            }
        return false;
        case EISUU:
            if (record->event.pressed) {
                layer_on(1);
                tap_code(KC_INT5);
            } else {
                layer_off(1);
            }
        return false;
        case VIM_ESC:
            if (record->event.pressed) {
                my_timer = timer_read();
                register_code(KC_LSFT);
            }else{
                unregister_code(KC_LSFT);
                if (timer_elapsed(my_timer) < TAPPING_TERM) {
                    SEND_STRING(SS_TAP(X_ESC)SS_TAP(X_LANGUAGE_2));
                }
            }
            return false;
            break;
        case INLINE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LANGUAGE_2)"$$"SS_TAP(X_LEFT));
            } else {
            }
            return false;
            break;
        case BLOCK:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LANGUAGE_2)"$$"SS_TAP(X_ENT)"\\begin{aligned}"SS_TAP(X_ENT)SS_TAP(X_ENT)"\\end{aligned}"SS_TAP(X_ENT)"$$"SS_TAP(X_UP)SS_TAP(X_UP));
            } else {
            }
            return false;
            break;
        case GATHER:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LANGUAGE_2)"$$"SS_TAP(X_ENT)"\\begin{gather}"SS_TAP(X_ENT)SS_TAP(X_ENT)"\\end{gather}"SS_TAP(X_ENT)"$$"SS_TAP(X_UP)SS_TAP(X_UP));
            } else {
            }
            return false;
            break;
        case FRAC:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LANGUAGE_2)"\\frac{}{}"SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
            } else {
            }
            return false;
        case SQRT:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LANGUAGE_2)"\\sqrt{}"SS_TAP(X_LEFT));
            } else {
            }
            return false;
            break;
        case LR:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LANGUAGE_2)SS_TAP(X_LEFT)SS_TAP(X_LEFT)"\\left"SS_TAP(X_RIGHT)"\\right"SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT));
            } else {
            }
            return false;
            break;
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_universal(
            KC_TRNS, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_TRNS,
            KC_TRNS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    LT(3, KC_ENT), KC_TRNS,
            VIM_ESC, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMMA,    KC_DOT,   KC_LEFT_BRACKET, KC_TRNS,
            KC_LALT, LGUI_T(KC_DEL),  LCTL_T(KC_BSPC),   EISUU,  LSFT_T(KC_SPACE), LSFT_T(KC_SPACE), KANA,   LSFT_T(KC_SPACE), KC_RIGHT_BRACKET, KC_TRNS
    ),
    [1] = LAYOUT_universal(
            KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_TRNS, 
            KC_TRNS, KC_BACKSLASH,    LSFT(KC_LEFT_BRACKET),    LSFT(KC_RIGHT_BRACKET),    LSFT(KC_6),  LSFT(KC_4),    LSFT(KC_3),    KC_MINUS,    KC_QUOTE,    KC_SEMICOLON,    KC_SLASH, KC_TRNS, 
            MO(5), LSFT(KC_1),    LSFT(KC_COMM),    LSFT(KC_DOT),   KC_EQUAL,    KC_GRAVE,    LSFT(KC_EQUAL),  LSFT(KC_MINUS),  KC_COMM,    KC_DOT,    LSFT(KC_SLASH), KC_TRNS, 
            KC_LALT, LGUI_T(KC_DEL),  LCTL_T(KC_BSPC),   EISUU,  LSFT_T(KC_SPACE), LSFT_T(KC_SPACE), KANA,   LSFT_T(KC_SPACE), MO(5), KC_TRNS
    ),
    [2] = LAYOUT_universal(
            KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_TRNS, 
            KC_TRNS, KC_BACKSLASH,    LSFT(KC_LEFT_BRACKET),    LSFT(KC_RIGHT_BRACKET),    LSFT(KC_6),  LSFT(KC_4),    LSFT(KC_3),    KC_MINUS,    KC_QUOTE,    KC_SEMICOLON, KC_SLASH, KC_TRNS,
            KC_TRNS, LSFT(KC_1),    LSFT(KC_COMM),    LSFT(KC_DOT),   KC_EQUAL,    KC_GRAVE,    LSFT(KC_EQUAL),    LSFT(KC_MINUS),    KC_COMM,    KC_DOT,    LSFT(KC_SLASH), KC_TRNS,
            KC_LALT, LGUI_T(KC_DEL),  LCTL_T(KC_BSPC),   MO(4),  LSFT_T(KC_SPACE), LSFT_T(KC_SPACE), KANA,   LSFT_T(KC_SPACE), MO(5), KC_TRNS
    ),
    [3] = LAYOUT_universal(
            KC_TRNS, KC_F11,    KC_F12,    KC_F13,    KC_F14,    KC_F15,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, KC_TRNS, 
            KC_TRNS, KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_LEFT,    KC_DOWN,    KC_UP,    KC_RIGHT,    KC_ENT, KC_TRNS, 
            KC_TRNS, KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_PRINT_SCREEN,    RCS(KC_P),    LGUI(KC_TAB),    KC_TAB, KC_0, KC_TRNS, 
            KC_LALT, LGUI_T(KC_DEL),  LCTL_T(KC_BSPC),   MO(4),  LSFT_T(KC_SPACE), RALT(KC_LEFT), RALT(KC_RIGHT),  LSFT_T(KC_SPACE), MO(5), KC_TRNS
    ),
    [4] = LAYOUT_universal(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, SQRT, FRAC, GATHER, INLINE, BLOCK, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, LR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_LALT, LGUI_T(KC_DEL),  LCTL_T(KC_BSPC),   MO(4),  LSFT_T(KC_SPACE), RALT(KC_LEFT), RALT(KC_RIGHT),  LSFT_T(KC_SPACE), MO(5), KC_TRNS
    ), 
    [5] = LAYOUT_universal(
      _______  , _______  , _______  , _______  , _______  ,  _______  ,                           _______  , _______  , _______  , _______ , _______ , _______ ,
      _______  , _______  , _______  , _______  , _______  ,  _______  ,                           _______  , _______  , _______  , _______ , _______ , _______ ,
      _______  , _______  , _______  , _______  , _______  ,  _______  ,                           _______  , _______  , _______  , _______ , _______ , _______ ,
      _______  , _______  , _______  ,  _______  , _______  ,     _______  , _______  , _______  , _______  , _______
    ),
    [6] = LAYOUT_universal(
      _______  , _______  , _______  , _______  , _______  ,  _______  ,                           _______  , _______  , _______  , _______ , _______ , _______  , 
      _______  , _______  , _______  , _______  , _______  ,  _______  ,                           _______  , KC_BTN1  , KC_BTN3 , KC_BTN2 ,  _______ , _______  , 
      _______  , _______  , _______  , _______  , _______  ,  _______  ,                           _______  , _______  , _______  , _______ , _______ , _______  , 
      _______  , _______  , _______  ,  _______  , _______  ,     _______  , _______  , _______  , _______  , _______
    ),
};

// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
