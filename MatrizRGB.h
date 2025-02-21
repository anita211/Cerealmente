#ifndef MATRIXRGB_H
#define MATRIXRGB_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "frames_rgb.h"

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PINOS 7

void npInit(uint pin);
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);
void npClear(void);
void npWrite(void);
int getIndex(int x, int y);
void matrizRGB_init(void);
void matrizRGB_step(void);
void matrizRGB(void);
void matrizClear(void);

#endif // MATRIXRGB_H
