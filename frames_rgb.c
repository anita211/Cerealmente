#include <stdint.h>
#include "frames_rgb.h"

#define MATRIX_ROWS 5
#define MATRIX_COLS 5
#define MATRIX_DEPTH 3
#define NEW_PISKEL_FRAME_COUNT 6

const uint8_t frames_rgb[NEW_PISKEL_FRAME_COUNT][MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH] = {
    {
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {63, 215, 71}, {0, 0, 0}},
        {{63, 215, 71}, {63, 215, 71}, {63, 215, 71}, {63, 215, 71}, {63, 215, 71}},
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {63, 215, 71}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {0, 0, 0}, {0, 0, 0}}
    },
    {
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {63, 215, 71}, {0, 0, 0}},
        {{235, 226, 54}, {63, 215, 71}, {63, 215, 71}, {63, 215, 71}, {63, 215, 71}},
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {63, 215, 71}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {0, 0, 0}, {0, 0, 0}}
    },
    {
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {63, 215, 71}, {0, 0, 0}},
        {{235, 226, 54}, {235, 226, 54}, {63, 215, 71}, {63, 215, 71}, {63, 215, 71}},
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {63, 215, 71}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {63, 215, 71}, {0, 0, 0}, {0, 0, 0}}
    },
    {
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {63, 215, 71}, {0, 0, 0}},
        {{235, 226, 54}, {235, 226, 54}, {235, 226, 54}, {63, 215, 71}, {63, 215, 71}},
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {63, 215, 71}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {0, 0, 0}, {0, 0, 0}}
    },
    {
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {235, 226, 54}, {0, 0, 0}},
        {{235, 226, 54}, {235, 226, 54}, {235, 226, 54}, {235, 226, 54}, {63, 215, 71}},
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {235, 226, 54}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {0, 0, 0}, {0, 0, 0}}
    },
    {
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {235, 226, 54}, {0, 0, 0}},
        {{235, 226, 54}, {235, 226, 54}, {235, 226, 54}, {235, 226, 54}, {235, 226, 54}},
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {235, 226, 54}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {235, 226, 54}, {0, 0, 0}, {0, 0, 0}}
    }
};
