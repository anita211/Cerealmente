#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>

// Inicializa o display OLED via I2C
void display_init(void);

// Exibe um conjunto de linhas de texto no display OLED
// Parâmetros:
//   lines: array de strings a serem exibidas
//   count: número de linhas
void display_show_lines(const char* lines[], int count);

// Controla o scroll do display OLED (true para ativar, false para desativar)
void display_scroll(bool enable);

// Exibe a mensagem de boas-vindas (com scroll e texto)
void display_show_welcome(void);

#endif // DISPLAY_H
