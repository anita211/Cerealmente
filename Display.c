#include "Display.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include <string.h>

const uint I2C_SDA_PIN = 14;
const uint I2C_SCL_PIN = 15;

// Buffer utilizado para renderizar o frame
static uint8_t buf[SSD1306_BUF_LEN];
// Estrutura que define a área de renderização do display
static struct render_area frame_area;

void display_init(void) {
    stdio_init_all();

    // Inicializa o I2C (utilizando i2c1) com a frequência definida pelo SSD1306_I2C_CLK
    i2c_init(i2c1, SSD1306_I2C_CLK * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    // Inicializa o display SSD1306
    SSD1306_init();

    // Configura a área de renderização para utilizar todo o display
    frame_area.start_col = 0;
    frame_area.end_col = SSD1306_WIDTH - 1;
    frame_area.start_page = 0;
    frame_area.end_page = SSD1306_NUM_PAGES - 1;
    calc_render_area_buflen(&frame_area);

    // Limpa o buffer e renderiza (apaga o display)
    memset(buf, 0, SSD1306_BUF_LEN);
    render(buf, &frame_area);
}

void display_show_lines(const char* lines[], int count) {
    // Limpa o buffer de renderização
    memset(buf, 0, SSD1306_BUF_LEN);
    
    // Escreve cada linha no buffer, começando em x=5 e com espaçamento vertical de 8 pixels
    int y = 0;
    for (int i = 0; i < count; i++) {
        WriteString(buf, 5, y, lines[i]);
        y += 8;
    }
    // Renderiza o buffer na área configurada
    render(buf, &frame_area);
}

void display_scroll(bool enable) {
    SSD1306_scroll(enable);
}

void display_show_welcome(void) {
    // Ativa o scroll, espera 5 segundos e desativa o scroll
    display_scroll(true);
    sleep_ms(5000);
    display_scroll(false);

    // Define as linhas da mensagem de boas-vindas
    const char *welcome_text[] = {
        "   Bem-Vindo ",
        " ao EmbarcaTech ",
        "      2024 ",
        "  SOFTEX/MCTI "
    };
    display_show_lines(welcome_text, 4);
}
