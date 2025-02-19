#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include <stdbool.h>

// Inicializa o buzzer para reprodução de áudio
void buzzer_init(void);

// Atualiza a reprodução da música de forma não bloqueante
// Deve ser chamada periodicamente no loop principal
void buzzer_update(void);

// Para a reprodução da música
void buzzer_stop(void);

#endif // BUZZER_H
