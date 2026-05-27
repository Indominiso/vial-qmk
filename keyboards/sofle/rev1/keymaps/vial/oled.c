#define ANIM_INVERT false
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 100 //Switch to fast animation when over words per minute

#ifdef OLED_ENABLE
// right oled animation stuff
#include "demon.c"

// Defined in keymap.c — tells us when to show the RGB HUD
extern bool              rgb_hud_active;
extern rgb_tweak_mode_t  rgb_tweak_mode;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }

    return rotation;
}

static void render_status(void) {

    oled_write_P(PSTR("LAYER"), false);

    switch (get_highest_layer(layer_state)) {
        case 0: oled_write_P(PSTR("Base "), false); break;
        case 1: oled_write_P(PSTR("Lower"), false); break;
        case 2: oled_write_P(PSTR("Raise"), false); break;
        default: oled_write_P(PSTR("?????"), false);
    }
   
    oled_write_P(PSTR("     "), false);
   
    uint8_t mods = get_mods() | get_oneshot_mods();
   
    oled_write_P(PSTR("MODS "), false);
   
    oled_write_P(PSTR("SFT "), (mods & MOD_MASK_SHIFT) != 0);
    oled_write_P(PSTR(" "),    false);
   
    oled_write_P(PSTR("ALT "), (mods & MOD_MASK_ALT)   != 0);
    oled_write_P(PSTR(" "),    false);
   
    oled_write_P(PSTR("GUI "), (mods & MOD_MASK_GUI)   != 0);
    oled_write_P(PSTR(" "),    false);
   
    oled_write_P(PSTR("CTL "), (mods & MOD_MASK_CTRL)  != 0);
    oled_write_P(PSTR(" "),    false);
   
    oled_write_P(PSTR("     "), false);
   
    led_t led_state = host_keyboard_led_state();
   
    oled_write_P(PSTR("LOCKS"), false);
    oled_write_P(PSTR("CAP  "), led_state.caps_lock);
    oled_write_P(PSTR("NUM  "), led_state.num_lock);
   
    oled_write_P(PSTR("     "), false);
}

#ifdef RGB_MATRIX_ENABLE
// RGB HUD — shown while tweaking with the encoder on layer 2.
static void render_rgb_hud(void) {
    char buf[6];

    oled_write_P(PSTR("EDIT "), false);
    switch (rgb_tweak_mode) {
        case RGB_TW_HUE: oled_write_P(PSTR("HUE  "), false); break;
        case RGB_TW_SAT: oled_write_P(PSTR("SAT  "), false); break;
        case RGB_TW_VAL: oled_write_P(PSTR("VAL  "), false); break;
        case RGB_TW_SPD: oled_write_P(PSTR("SPD  "), false); break;
        case RGB_TW_MOD: oled_write_P(PSTR("MODE "), false); break;
        default:         oled_write_P(PSTR("???? "), false); break;
    }
    oled_write_P(PSTR("     "), false);

    snprintf(buf, sizeof(buf), "H%3d ", rgb_matrix_get_hue());
    oled_write(buf, false);

    snprintf(buf, sizeof(buf), "S%3d ", rgb_matrix_get_sat());
    oled_write(buf, false);

    snprintf(buf, sizeof(buf), "V%3d ", rgb_matrix_get_val());
    oled_write(buf, false);

    oled_write_P(PSTR("     "), false);

    snprintf(buf, sizeof(buf), "Sp%3d", rgb_matrix_get_speed());
    oled_write(buf, false);

    oled_write_P(PSTR("     "), false);

    switch (rgb_matrix_get_mode()) {
        case RGB_MATRIX_SOLID_COLOR:              oled_write_P(PSTR("SOLID"), false); break;
        case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:    oled_write_P(PSTR("REACT"), false); break;

        case RGB_MATRIX_DIGITAL_RAIN:             oled_write_P(PSTR("RAIN "), false); break;
        case RGB_MATRIX_RIVERFLOW:                oled_write_P(PSTR("RIVER"), false); break;
        case RGB_MATRIX_CYCLE_SPIRAL:             oled_write_P(PSTR("SPIRL"), false); break;
        case RGB_MATRIX_CYCLE_PINWHEEL:           oled_write_P(PSTR("PINWH"), false); break;
        case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:   oled_write_P(PSTR("CHEVR"), false); break;
        case RGB_MATRIX_STARLIGHT:                oled_write_P(PSTR("STAR "), false); break;
        case RGB_MATRIX_RAINDROPS:                oled_write_P(PSTR("DROPS"), false); break;
        case RGB_MATRIX_HUE_WAVE:                 oled_write_P(PSTR("HWAVE"), false); break;
        case RGB_MATRIX_SPLASH:                   oled_write_P(PSTR("SPLSH"), false); break;
        case RGB_MATRIX_MULTISPLASH:              oled_write_P(PSTR("MSPLS"), false); break;

        case RGB_MATRIX_SOLID_REACTIVE_CROSS:     oled_write_P(PSTR("CROSS"), false); break;
        case RGB_MATRIX_SOLID_REACTIVE_NEXUS:     oled_write_P(PSTR("NEXUS"), false); break;
        case RGB_MATRIX_SOLID_REACTIVE_WIDE:      oled_write_P(PSTR("WIDE "), false); break;

        case RGB_MATRIX_ALPHAS_MODS:              oled_write_P(PSTR("ALPHA"), false); break;
        case RGB_MATRIX_GRADIENT_UP_DOWN:         oled_write_P(PSTR("GUPDN"), false); break;
        case RGB_MATRIX_GRADIENT_LEFT_RIGHT:      oled_write_P(PSTR("GLR  "), false); break;
        case RGB_MATRIX_BREATHING:                oled_write_P(PSTR("BRETH"), false); break;
        case RGB_MATRIX_BAND_SAT:                 oled_write_P(PSTR("BSAT "), false); break;
        case RGB_MATRIX_BAND_VAL:                 oled_write_P(PSTR("BVAL "), false); break;
        case RGB_MATRIX_DUAL_BEACON:              oled_write_P(PSTR("DBEAC"), false); break;
        case RGB_MATRIX_RAINBOW_BEACON:           oled_write_P(PSTR("RBEAC"), false); break;

        case RGB_MATRIX_JELLYBEAN_RAINDROPS:      oled_write_P(PSTR("JDROP"), false); break;
        case RGB_MATRIX_FLOWER_BLOOMING:          oled_write_P(PSTR("FLOWR"), false); break;
        case RGB_MATRIX_STARLIGHT_DUAL_HUE:       oled_write_P(PSTR("SDHUE"), false); break;
        case RGB_MATRIX_TYPING_HEATMAP:           oled_write_P(PSTR("HEAT "), false); break;

        case RGB_MATRIX_PIXEL_FRACTAL:            oled_write_P(PSTR("FRACT"), false); break;
        case RGB_MATRIX_PIXEL_RAIN:               oled_write_P(PSTR("PRAIN"), false); break;
        case RGB_MATRIX_PIXEL_FLOW:               oled_write_P(PSTR("PFLOW"), false); break;
        case RGB_MATRIX_CYCLE_OUT_IN:             oled_write_P(PSTR("OUTIN"), false); break;
        case RGB_MATRIX_CYCLE_OUT_IN_DUAL:        oled_write_P(PSTR("OINDU"), false); break;
        case RGB_MATRIX_HUE_PENDULUM:             oled_write_P(PSTR("PEND "), false); break;

        default:                                  oled_write_P(PSTR("?????"), false); break;
    }
    oled_write_P(PSTR("     "), false);

    uint8_t cur = 0;
    switch (rgb_tweak_mode) {
        case RGB_TW_HUE: cur = rgb_matrix_get_hue();   break;
        case RGB_TW_SAT: cur = rgb_matrix_get_sat();   break;
        case RGB_TW_VAL: cur = rgb_matrix_get_val();   break;
        case RGB_TW_SPD: cur = rgb_matrix_get_speed(); break;
        case RGB_TW_MOD: cur = rgb_matrix_get_mode();  break;
        default: break;
    }
    uint8_t filled = (uint8_t)((uint16_t)cur * 5 / 255);
    oled_write_P(PSTR("["), false);
    for (uint8_t i = 0; i < 5; i++) {
        oled_write_P(i < filled ? PSTR("#") : PSTR("-"), false);
    }
    oled_write_P(PSTR("]"), false);
}
#endif

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        oled_render_anim();
    } else {
        if (rgb_hud_active) {
            #ifdef RGB_MATRIX_ENABLE
                render_rgb_hud();
            #endif
        } else {
            render_status();
        }
    }
    return false;
}
#endif