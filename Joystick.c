#include "Joystick.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "Display.h"  // Para usar display_show_text()

// Faixas de valores para o eixo Y (vertical)
#define UP_THRESHOLD    3000  // Valor acima deste indica movimento para cima
#define DOWN_THRESHOLD  1000  // Valor abaixo deste indica movimento para baixo
// Faixa central para resetar o debounce
#define CENTER_LOW      1500
#define CENTER_HIGH     2500

// Lista de frases para exibição: cada elemento é um array de 4 strings
const char *pouco_text[] = {
    "   Liberar   ",
    "   o cereal  ",
    "             ",
    "  Modo Pouco"
};

const char *normal_text[] = {
    "   Liberar   ",
    "   o cereal  ",
    "             ",
    " Modo Normal "
};

const char *muito_text[] = {
    "   Liberar   ",
    "   o cereal  ",
    "             ",
    "  Modo Muito "
};

static const char **phrases[3] = {
    pouco_text,
    normal_text,
    muito_text
};
static const int num_phrases = 3;
static int current_phrase = 0;

// Flag para evitar múltiplas atualizações enquanto o joystick permanece inclinado
static bool change_triggered = false;

// Função para configurar o ADC e o pino do botão do joystick
void joystick_init(void) {
    adc_init();
    adc_gpio_init(VRY_PIN); // Configura o pino VRY para ADC
    adc_gpio_init(VRX_PIN); // Configura o pino VRX para ADC
}

// Função auxiliar para ler o eixo Y do joystick (VRY)
static uint16_t joystick_read_y(void) {
    adc_select_input(1); // Seleciona o canal ADC 1 (VRY)
    sleep_us(2);         // Pequeno delay para estabilidade
    return adc_read();
}

// Atualiza o display de acordo com o movimento do joystick
void joystick_update_display(void) {
    uint16_t vy = joystick_read_y();

    // Se o joystick for movido para cima e ainda não houve atualização
    if (vy > UP_THRESHOLD && !change_triggered) {
        current_phrase = (current_phrase + 1) % num_phrases;
        display_show_text(phrases[current_phrase], 4);
        change_triggered = true;
    }
    // Se for movido para baixo e ainda não houve atualização
    else if (vy < DOWN_THRESHOLD && !change_triggered) {
        current_phrase = (current_phrase - 1 + num_phrases) % num_phrases;
        display_show_text(phrases[current_phrase], 4);
        change_triggered = true;
    }

    // Se o joystick voltar para a faixa central, reseta o debounce
    if (vy > CENTER_LOW && vy < CENTER_HIGH) {
        change_triggered = false;
    }
}

// Retorna o modo atual (0 para Pouco, 1 para Normal, 2 para Muito)
int joystick_get_mode(void) {
    return current_phrase;
}
