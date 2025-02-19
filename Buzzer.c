#include "Buzzer.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "Notes.h"

// Definindo o pino do buzzer (mesmo valor definido em GPIO.h)
#ifndef BUZZER_PIN
#define BUZZER_PIN 21
#endif

// Variáveis para o estado da música
static uint16_t wrap_div_buzzer = 8;
static uint16_t buzzer_state_index = 0;
static uint32_t buzzer_counter = 0;

typedef enum {
    BUZZER_PLAY_NOTE,
    BUZZER_DURATION_NOTE,
    BUZZER_PLAY_REST,
    BUZZER_DURATION_REST
} buzzer_state_t;

static buzzer_state_t buzzer_state = BUZZER_PLAY_NOTE;

// Toca a nota atual usando PWM
static void play_note(uint16_t note) {
    int slice = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_set_wrap(slice, note);
    pwm_set_gpio_level(BUZZER_PIN, note / wrap_div_buzzer);
    pwm_set_enabled(slice, true);
}

// Silencia o buzzer
static void play_rest(void) {
    int slice = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_set_enabled(slice, false);
}

void buzzer_init(void) {
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    int slice = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_set_enabled(slice, false);
    buzzer_state = BUZZER_PLAY_NOTE;
    buzzer_state_index = 0;
    buzzer_counter = 0;
}

void buzzer_update(void) {
    // Se chegou ao fim da música, reinicia
    if (buzzer_state_index >= SONG_B_LENGTH) {
        buzzer_state_index = 0;
    }
    
    // Obtenha a nota e a duração (ajuste o fator 800 conforme necessário)
    int note = melody[buzzer_state_index];
    int duration = 800 / durations[buzzer_state_index];

    switch(buzzer_state) {
        case BUZZER_PLAY_NOTE:
            play_note(note);
            buzzer_state = BUZZER_DURATION_NOTE;
            buzzer_counter = 0;
            break;
        case BUZZER_DURATION_NOTE:
            if (buzzer_counter++ > duration) {
                buzzer_state = BUZZER_PLAY_REST;
                buzzer_counter = 0;
            }
            break;
        case BUZZER_PLAY_REST:
            play_rest();
            buzzer_state = BUZZER_DURATION_REST;
            buzzer_counter = 0;
            break;
        case BUZZER_DURATION_REST:
            if (buzzer_counter++ > duration) {
                buzzer_state = BUZZER_PLAY_NOTE;
                buzzer_state_index++;
                if (buzzer_state_index >= SONG_B_LENGTH)
                    buzzer_state_index = 0;
                buzzer_counter = 0;
            }
            break;
    }
}

void buzzer_stop(void) {
    int slice = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_set_enabled(slice, false);
    buzzer_state = BUZZER_PLAY_NOTE;
    buzzer_state_index = 0;
    buzzer_counter = 0;
}
