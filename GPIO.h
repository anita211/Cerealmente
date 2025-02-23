#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

// Definições dos pinos utilizados
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6
#define LED_PIN      12

// Inicializa todos os pinos de entrada/saída necessários
void gpio_init_all(void);

#endif // GPIO_H
