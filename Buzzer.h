#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Configuração do pino do buzzer
#define BUZZER_PIN 21

// Inicializa o PWM no pino do buzzer
void pwm_init_buzzer(uint pin);

void buzzer_update_starwars(uint pin);

void buzzer_stop(void);

void buzzer_resume(void);
