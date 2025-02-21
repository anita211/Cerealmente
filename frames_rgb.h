#ifndef FRAMES_RGB_H
#define FRAMES_RGB_H

#include <stdint.h>

#define MATRIX_ROWS 5
#define MATRIX_COLS 5
#define MATRIX_DEPTH 3
#define NEW_PISKEL_FRAME_COUNT 6

extern const uint8_t frames_rgb[NEW_PISKEL_FRAME_COUNT][MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH];

#endif // FRAMES_RGB_H
