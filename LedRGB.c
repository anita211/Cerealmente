#include "LedRGB.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

const float DIVIDER_PWM = 16.0;
const uint16_t PERIOD = 4096;
static uint slice_led_b, slice_led_r;

void led_rgb_init(void) {
    // Inicializa o LED azul
    gpio_set_function(LED_B_PIN, GPIO_FUNC_PWM);
    slice_led_b = pwm_gpio_to_slice_num(LED_B_PIN);
    pwm_set_clkdiv(slice_led_b, DIVIDER_PWM);
    pwm_set_wrap(slice_led_b, PERIOD);
    pwm_set_gpio_level(LED_B_PIN, 0);
    pwm_set_enabled(slice_led_b, true);
    
    // Inicializa o LED vermelho
    gpio_set_function(LED_R_PIN, GPIO_FUNC_PWM);
    slice_led_r = pwm_gpio_to_slice_num(LED_R_PIN);
    pwm_set_clkdiv(slice_led_r, DIVIDER_PWM);
    pwm_set_wrap(slice_led_r, PERIOD);
    pwm_set_gpio_level(LED_R_PIN, 0);
    pwm_set_enabled(slice_led_r, true);
}

void led_rgb_update(uint16_t vrx_value, uint16_t vry_value) {
    // Atualiza o LED azul com o valor lido do eixo X e o LED vermelho com o valor lido do eixo Y.
    pwm_set_gpio_level(LED_B_PIN, vrx_value);
    pwm_set_gpio_level(LED_R_PIN, vry_value);
}

void led_rgb_update_from_joystick(void) {
    uint16_t vrx, vry;
    // Assumindo que o pino VRX está conectado ao canal ADC0 e VRY ao ADC1.
    adc_select_input(0);
    sleep_us(2);
    vrx = adc_read();
    
    adc_select_input(1);
    sleep_us(2);
    vry = adc_read();
    
    led_rgb_update(vrx, vry);
}
