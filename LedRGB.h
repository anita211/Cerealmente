#ifndef LEDRGB_H
#define LEDRGB_H

#include <stdint.h>

// Definições dos pinos para os LEDs (ajuste conforme seu hardware)
#define LED_R_PIN 11
#define LED_B_PIN 13

// Inicializa os LEDs RGB (neste exemplo, apenas vermelho e azul)
void led_rgb_init(void);

// Atualiza os níveis dos LEDs com os valores informados (por exemplo, lidos do ADC)
void led_rgb_update(uint16_t vrx_value, uint16_t vry_value);

// Função que lê os valores do joystick (VRX e VRY) e atualiza os LEDs
void led_rgb_update_from_joystick(void);

#endif // LEDRGB_H
