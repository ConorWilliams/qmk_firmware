

#include QMK_KEYBOARD_H

#include "features/achordion.h"
#include "features/custom_shift_keys.h"
#include "features/layer_lock.h"

///////////////////////////////////////////////////////////////////////////////
// Aliases and definitions
///////////////////////////////////////////////////////////////////////////////

enum layers {
    BASE = 0,
    SYM,
    NAV,
    NUM,
};

enum custom_keycodes {
    LY_LOCK = SAFE_RANGE, // Layer lock
    SELLINE,              // Select the current line
    UP_DIR,               // ../
    BDL_CLN,              // ::
    STD_CLN,              // std::
    DOCSTR,               // Python: """docstring"""
    MKGRVS,               // Markdown: ```\n\n```
};

/**
 *  w l y p b   z f o u '
 *  c r s t g   m n e i a
 *  q j v d k   x h ; , .
 */

// Left hand home row
#define HOME_C LT(SYM, KC_C)
#define HOME_R LALT_T(KC_R)
#define HOME_S LSFT_T(KC_S)
#define HOME_T LCTL_T(KC_T)

// Right hand home row
#define HOME_N RCTL_T(KC_N)
#define HOME_E RSFT_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_A LT(SYM, KC_A)

// Pinky's lower gui's
#define PNKY_Q LGUI_T(KC_Q)
#define PNKY_DOT LGUI_T(KC_DOT)

// Thumb keys
#define THMB_TAB KC_TAB
#define THMB_SPC LT(NAV, KC_SPC)
#define THMB_ENT LT(NUM, KC_ENT)
#define THMB_BCK KC_BSPC

///////////////////////////////////////////////////////////////////////////////
// My Keymap
///////////////////////////////////////////////////////////////////////////////

// clang-format off


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x5_2(  
        KC_W,     KC_L,    KC_Y,    KC_P,    KC_B,        KC_Z,    KC_F,    KC_O,    KC_U,  KC_QUOT,
        HOME_C, HOME_R,  HOME_S,  HOME_T,    KC_G,        KC_M,  HOME_N,  HOME_E,  HOME_I,   HOME_A,
        PNKY_Q,   KC_J,    KC_V,    KC_D,    KC_K,        KC_X,    KC_H, KC_SCLN, KC_COMM, PNKY_DOT,

                                THMB_TAB, THMB_SPC,       THMB_ENT, THMB_BCK
    ),

    [SYM] = LAYOUT_split_3x5_2(  
        XXXXXXX, KC_LABK, KC_RABK, KC_BSLS, MKGRVS,       KC_AMPR, BDL_CLN, KC_LBRC, KC_RBRC,  DOCSTR,
        KC_EXLM, KC_MINS, KC_PLUS,  KC_EQL, KC_GRV,       KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_PERC,
        XXXXXXX, KC_SLSH, KC_ASTR, KC_CIRC, UP_DIR,       KC_TILD,  KC_DLR, KC_LCBR, KC_RCBR, XXXXXXX,
        
                                    _______, KC_SPC,       KC_UNDS, _______
    ),
   
    [NAV] = LAYOUT_split_3x5_2(
        C(KC_Z), XXXXXXX, C(KC_A), XXXXXXX,    XXXXXXX,       XXXXXXX, STD_CLN, SELLINE, XXXXXXX, XXXXXXX,
        C(KC_A), KC_LALT, KC_LSFT, KC_LCTL, C(KC_SLSH),       KC_PGUP, KC_LEFT,   KC_UP, KC_RGHT,  KC_DEL,
        KC_LGUI, C(KC_X), C(KC_C), C(KC_V),    XXXXXXX,       KC_PGDN, KC_HOME, KC_DOWN,  KC_END, XXXXXXX,
        
                                     _______,  _______,       LY_LOCK, _______ 
    ),

    [NUM] = LAYOUT_split_3x5_2(
        XXXXXXX,  KC_4,    KC_5,    KC_6,    KC_PLUS,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_0,  KC_1,    KC_2,    KC_3,     KC_DOT,       KC_VOLU, KC_RCTL, KC_RSFT, KC_LALT, XXXXXXX,
        XXXXXXX,  KC_7,    KC_8,    KC_9,    KC_MINS,       KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX, KC_LGUI,
        
                                   _______,  LY_LOCK,       _______, _______ 
    ),
};

// clang-format on

///////////////////////////////////////////////////////////////////////////////
// Custom shift keys (https://getreuer.info/posts/keyboards/custom-shift-keys)
///////////////////////////////////////////////////////////////////////////////

/**
 *  w l y p b   z f o u '
 *  c r s t g   m n e i a
 *  q j v d k   x h ; , .
 */

custom_shift_key_t const custom_shift_keys[] = {
    {KC_SCLN, KC_HASH},  // ; -> #
    {KC_COMM, KC_AT},    // , -> @
    {PNKY_DOT, KC_QUES}, // . -> ?
    {KC_EQL, KC_EQL},    // Don't shift =
    {KC_SLSH, KC_SLSH},  // Don't shift /
};

uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

///////////////////////////////////////////////////////////////////////////////
// Combos (https://docs.qmk.fm/#/feature_combo)
///////////////////////////////////////////////////////////////////////////////

/**
 *  w l y p b   z f o u '
 *  c r s t g   m n e i a
 *  q j v d k   x h ; , .
 */

uint16_t const caps_combo[] PROGMEM = {KC_V, KC_SCLN, COMBO_END}; // Middle fingers
uint16_t const esc_combo[] PROGMEM  = {KC_H, KC_SCLN, COMBO_END}; // RHS index + middle
uint16_t const bsls_combo[] PROGMEM = {KC_V, KC_D, COMBO_END};    // LHS ^

combo_t key_combos[] = {
    COMBO(caps_combo, CW_TOGG), //
    COMBO(esc_combo, KC_ESC),   //
    COMBO(bsls_combo, KC_BSLS), // For latex
};

///////////////////////////////////////////////////////////////////////////////
// Tap-hold configuration (https://docs.qmk.fm/#/tap_hold)
///////////////////////////////////////////////////////////////////////////////

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // Ring and pinky fingers are slower.
        case HOME_C:
        case HOME_R:
        case PNKY_Q:
        case HOME_I:
        case HOME_A:
        case PNKY_DOT:
            return TAPPING_TERM + 15;

        default:
            return TAPPING_TERM;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
    // If you quickly hold a tap-hold key after tapping it, the tap action is
    // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
    // lead to missed triggers in fast typing. Here, returning 0 means we
    // instead want to "force hold" and disable key repeating.
    switch (keycode) {
        case HOME_N:
            return QUICK_TAP_TERM; // Enable key repeating for search.
        default:
            return 0; // Otherwise, force hold and disable key repeating.
    }
}

///////////////////////////////////////////////////////////////////////////////
// Achordion (https://getreuer.info/posts/keyboards/achordion)
///////////////////////////////////////////////////////////////////////////////

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record) {
    // Allow same-hand holds when the other key is on the thumb cluster.
    // This allows for one-hand shift+tab
    uint8_t row = other_record->event.key.row;
    if (row == 3 || row == 7) {
        return true;
    }

    return achordion_opposite_hands(tap_hold_record, other_record);
}

bool achordion_eager_mod(uint8_t mod) {
    switch (mod) {
        case MOD_LSFT:
        case MOD_LCTL:
        case MOD_LALT:
            return true; // Eagerly apply left mods for mousing

        default:
            return false;
    }
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    // Disable achordion for the thumb keys.
    switch (tap_hold_keycode) {
        case THMB_SPC:
        case THMB_ENT:
            return 0;
        default:
            return 800; // Use a timeout of 800 ms.
    }
}

///////////////////////////////////////////////////////////////////////////////
// User macro callbacks (https://docs.qmk.fm/#/feature_macros)
///////////////////////////////////////////////////////////////////////////////

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Order is required
    if (!process_achordion(keycode, record)) {
        return false;
    }
    if (!process_layer_lock(keycode, record, LY_LOCK)) {
        return false;
    }
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }

    if (record->event.pressed) {
        switch (keycode) {
            case UP_DIR:
                SEND_STRING_DELAY("../", TAP_CODE_DELAY);
                return false;
            case STD_CLN:
                SEND_STRING_DELAY("std::", TAP_CODE_DELAY);
                return false;
            case BDL_CLN:
                SEND_STRING_DELAY("::", TAP_CODE_DELAY);
                return false;
            case SELLINE:
                SEND_STRING_DELAY(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)), TAP_CODE_DELAY);
                return false;
            case DOCSTR:
                SEND_STRING("\"\"\"\"\"\"" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
                return false;
            case MKGRVS:
                SEND_STRING("```\n\n```" SS_TAP(X_UP));
                return false;
        }
    }

    return true;
}

void matrix_scan_user(void) {
    achordion_task();
}
