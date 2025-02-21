// Converte um código hexadecimal gerado no site: https://www.piskelapp.com/
// Para decimal em no padrão RGB.
// O código gerado será utilizado para exibir imagens na matriz de leds neopixel.
#include <stdio.h>
#include <stdint.h>  // Inclui definições como uint32_t

#define MATRIX_ROWS 5
#define MATRIX_COLS 5
#define MATRIX_DEPTH 3

#define NEW_PISKEL_FRAME_COUNT 6

/* Piskel data for "New Piskel" */

static const uint32_t new_piskel_data[6][25] = {
    {
    0x00000000, 0x00000000, 0xff47d73f, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0xff47d73f, 0xff47d73f, 0x00000000, 
    0xff47d73f, 0xff47d73f, 0xff47d73f, 0xff47d73f, 0xff47d73f, 
    0x00000000, 0x00000000, 0xff47d73f, 0xff47d73f, 0x00000000, 
    0x00000000, 0x00000000, 0xff47d73f, 0x00000000, 0x00000000
    },
    {
    0x00000000, 0x00000000, 0xff47d73f, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0xff47d73f, 0xff47d73f, 0x00000000, 
    0xff36e2eb, 0xff47d73f, 0xff47d73f, 0xff47d73f, 0xff47d73f, 
    0x00000000, 0x00000000, 0xff47d73f, 0xff47d73f, 0x00000000, 
    0x00000000, 0x00000000, 0xff47d73f, 0x00000000, 0x00000000
    },
    {
    0x00000000, 0x00000000, 0xff47d73f, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0xff47d73f, 0xff47d73f, 0x00000000, 
    0xff36e2eb, 0xff36e2eb, 0xff47d73f, 0xff47d73f, 0xff47d73f, 
    0x00000000, 0x00000000, 0xff47d73f, 0xff47d73f, 0x00000000, 
    0x00000000, 0x00000000, 0xff47d73f, 0x00000000, 0x00000000
    },
    {
    0x00000000, 0x00000000, 0xff36e2eb, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0xff36e2eb, 0xff47d73f, 0x00000000, 
    0xff36e2eb, 0xff36e2eb, 0xff36e2eb, 0xff47d73f, 0xff47d73f, 
    0x00000000, 0x00000000, 0xff36e2eb, 0xff47d73f, 0x00000000, 
    0x00000000, 0x00000000, 0xff36e2eb, 0x00000000, 0x00000000
    },
    {
    0x00000000, 0x00000000, 0xff36e2eb, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0xff36e2eb, 0xff36e2eb, 0x00000000, 
    0xff36e2eb, 0xff36e2eb, 0xff36e2eb, 0xff36e2eb, 0xff47d73f, 
    0x00000000, 0x00000000, 0xff36e2eb, 0xff36e2eb, 0x00000000, 
    0x00000000, 0x00000000, 0xff36e2eb, 0x00000000, 0x00000000
    },
    {
    0x00000000, 0x00000000, 0xff36e2eb, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0xff36e2eb, 0xff36e2eb, 0x00000000, 
    0xff36e2eb, 0xff36e2eb, 0xff36e2eb, 0xff36e2eb, 0xff36e2eb, 
    0x00000000, 0x00000000, 0xff36e2eb, 0xff36e2eb, 0x00000000, 
    0x00000000, 0x00000000, 0xff36e2eb, 0x00000000, 0x00000000
    }
    };   


// Função para converter valores ARGB (0xAARRGGBB) para RGB
void convertToRGB(int argb, int rgb[3]) {
    rgb[0] = argb & 0xFF;          // Blue
    rgb[2] = (argb >> 16) & 0xFF;  // Red
    rgb[1] = (argb >> 8) & 0xFF;   // Green
}

int main() {
    // Criar arquivo de saída
    FILE *file = fopen("frames_rgb.c", "w");
    if (file == NULL) {
        printf("Erro ao criar arquivo frames_rgb.c\n");
        return 1;
    }

    // Escrever o cabeçalho do arquivo
    fprintf(file, "#include <stdint.h>\n\n");
    fprintf(file, "#include <frames_rgb.h>\n\n");
    fprintf(file, "#define MATRIX_ROWS %d\n", MATRIX_ROWS);
    fprintf(file, "#define MATRIX_COLS %d\n", MATRIX_COLS);
    fprintf(file, "#define MATRIX_DEPTH %d\n", MATRIX_DEPTH);
    fprintf(file, "#define NEW_PISKEL_FRAME_COUNT %d\n\n", NEW_PISKEL_FRAME_COUNT);

    fprintf(file, "const uint8_t frames_rgb[NEW_PISKEL_FRAME_COUNT][MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH] = {\n");

    // Converter os frames e salvar no arquivo
    for (int f = 0; f < NEW_PISKEL_FRAME_COUNT; f++) {
        fprintf(file, "    {\n");
        for (int i = 0; i < MATRIX_ROWS; i++) {
            fprintf(file, "        {");
            for (int j = 0; j < MATRIX_COLS; j++) {
                int rgb[3];
                convertToRGB(new_piskel_data[f][i * MATRIX_COLS + j], rgb);
                fprintf(file, "{%d, %d, %d}", rgb[0], rgb[1], rgb[2]);
                if (j < MATRIX_COLS - 1) {
                    fprintf(file, ", ");
                }
            }
            fprintf(file, "}");
            if (i < MATRIX_ROWS - 1) {
                fprintf(file, ",");
            }
            fprintf(file, "\n");
        }
        fprintf(file, "    }");
        if (f < NEW_PISKEL_FRAME_COUNT - 1) {
            fprintf(file, ",");
        }
        fprintf(file, "\n");
    }

    fprintf(file, "};\n");

    // Fechar o arquivo
    fclose(file);

    printf("Arquivo frames_rgb.c gerado com sucesso!\n");

    return 0;
}