#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "ssd1306_font.h"
#include "ssd1306_i2c.h"

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

// Exibe a mensagem de motor ativo (com scroll e texto)
void display_show_motor_active(void);

void display_show_text(const char *text[], int linhas);

#endif // DISPLAY_H
