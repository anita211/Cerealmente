#include "motor.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/time.h"
#include <stdio.h>

#define MOTOR_PIN 8

// Valores de PWM (contagens)
const uint32_t pulse_stop   = 750;
const uint32_t pulse_pouco  = 900;   // velocidade baixa
const uint32_t pulse_normal = 900;   // velocidade média
const uint32_t pulse_muito  = 1000;  // velocidade alta

// Durações dos modos (em milissegundos)
const uint32_t duration_pouco  = 10000;
const uint32_t duration_normal = 15000;
const uint32_t duration_muito  = 20000;

static volatile motor_mode_t current_mode = MODE_OFF;
static volatile uint32_t motor_end_time = 0;

static uint slice_num, channel;
const float pwm_divider = 250.0f;
const uint32_t pwm_wrap = 9999;

// Funções auxiliares para obter velocidade e duração conforme o modo
static uint32_t get_motor_speed(motor_mode_t mode) {
    switch(mode) {
        case MODE_POUCO:  return pulse_pouco;
        case MODE_NORMAL: return pulse_normal;
        case MODE_MUITO:  return pulse_muito;
        default:          return pulse_stop;
    }
}

static uint32_t get_motor_duration(motor_mode_t mode) {
    switch(mode) {
        case MODE_POUCO:  return duration_pouco;
        case MODE_NORMAL: return duration_normal;
        case MODE_MUITO:  return duration_muito;
        default:          return 0;
    }
}

void motor_init(void) {
    gpio_set_function(MOTOR_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(MOTOR_PIN);
    channel = pwm_gpio_to_channel(MOTOR_PIN);
    pwm_set_clkdiv(slice_num, pwm_divider);
    pwm_set_wrap(slice_num, pwm_wrap);
    pwm_set_enabled(slice_num, true);
}

void motor_start(motor_mode_t mode) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    switch(mode) {
        case MODE_POUCO:
            current_mode = MODE_POUCO;
            motor_end_time = current_time + get_motor_duration(MODE_POUCO);
            printf("Modo: Pouco\n");
            break;
        case MODE_NORMAL:
            current_mode = MODE_NORMAL;
            motor_end_time = current_time + get_motor_duration(MODE_NORMAL);
            printf("Modo: Normal\n");
            break;
        case MODE_MUITO:
            current_mode = MODE_MUITO;
            motor_end_time = current_time + get_motor_duration(MODE_MUITO);
            printf("Modo: Muito\n");
            break;
        case MODE_OFF:
        default:
            current_mode = MODE_OFF;
            printf("Motor parado via comando.\n");
            break;
    }
}

void motor_update(void) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    
    if (current_mode != MODE_OFF) {
        pwm_set_chan_level(slice_num, channel, get_motor_speed(current_mode));
        if (current_time >= motor_end_time) {
            current_mode = MODE_OFF;
            pwm_set_chan_level(slice_num, channel, pulse_stop);
            printf("Tempo de operação esgotado. Motor parado.\n");
        }
    } else {
        pwm_set_chan_level(slice_num, channel, pulse_stop);
    }
}

