#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

// Define os pinos usados para o joystick
#define VRX_PIN 26  // Eixo X (ADC)
#define VRY_PIN 27  // Eixo Y (ADC)
#define SW_PIN 22   // Botão do joystick

// Função para inicializar o joystick (configura ADC e botão)
void joystick_init(void);

// Função que atualiza o display de acordo com o movimento do joystick:
// direita, avança para a próxima frase, esquerda, volta para a frase anterior.
void joystick_update_display(void);

#endif // JOYSTICK_H
