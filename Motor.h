#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include <stdbool.h>

// Enum para os modos de operação do motor
typedef enum {
    MODE_OFF = 0,
    MODE_POUCO,
    MODE_NORMAL,
    MODE_MUITO
} motor_mode_t;

// Inicializa a configuração de PWM para o motor
void motor_init(void);

// Inicia o motor no modo especificado e configura o tempo de operação
void motor_start(motor_mode_t mode);

// Atualiza o estado do motor (deve ser chamada periodicamente)
void motor_update(void);

// Retorna 'true' se o motor estiver ligado (liberando cereal) ou 'false' se estiver parado.
bool motor_is_active(void);

#endif // MOTOR_H
