#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include "lwip/tcp.h"
#include <string.h>
#include "hardware/pwm.h"

#include "Wifi.h"
#include "Motor.h"
#include "Display.h"
#include "Buzzer.h"
#include "Joystick.h"
#include "GPIO.h"
#include "LedRGB.h"
#include "MatrizRGB.h"

int main() {
    stdio_init_all();
    sleep_ms(10000);
    printf("Iniciando servidor HTTP\n");
    
    // Inicializa e conecta o Wi‑Fi
    wifi_init_and_connect();
    
    // Inicializa a configuração do motor (PWM)
    motor_init();
    
    // Inicia o servidor HTTP
    wifi_start_http_server();

    // Inicia o display
    display_init();
    display_show_welcome();

    // Inicia o buzzer
    pwm_init_buzzer(BUZZER_PIN);

    // Inicia o joystick
    joystick_init();

    // Inicia os LEDs RGB
    led_rgb_init();

    // Inicia GPIO
    gpio_init_all();

    // Inicia a matriz RGB
    matrizRGB_init();

    // Variável para controlar a transição de estado do motor
    bool motor_last_state = false;
    bool active = motor_is_active();
    
    // Loop principal: atualiza o estado do motor e mantém o Wi‑Fi ativo
    while (true) {
        cyw43_arch_poll();
        motor_update();
        active = motor_is_active();
        if (motor_is_active()) {
            display_show_motor_active();
            buzzer_resume();
            buzzer_update_starwars(BUZZER_PIN);
            matrizRGB_step();
            motor_last_state = true;
            if (gpio_get(BUTTON_B_PIN) == 0) {  // Botão B pressionado
                motor_start(MODE_OFF);
            }
        } else {
            buzzer_stop();
            buzzer_update_starwars(BUZZER_PIN);
            matrizClear();
            if (motor_last_state) {
                const char *msg[] = { "Motor parado" };
                display_show_text(msg, 1);
                sleep_ms(2000);
                display_show_welcome();
                motor_last_state = false;
            }

            // Verifica o botão para seleção de modo (apenas quando o motor está parado)
            if (gpio_get(BUTTON_A_PIN) == 0) {  // Botão A pressionado
                int mode = joystick_get_mode();
                switch (mode) {
                    case 0:
                        motor_start(MODE_POUCO);
                        break;
                    case 1:
                        motor_start(MODE_NORMAL);
                        break;
                    case 2:
                        motor_start(MODE_MUITO);
                        break;
                    default:
                        break;
                }
            }

            joystick_update_display();
            led_rgb_update_from_joystick();
        }
        sleep_ms(100);
    }
    
    cyw43_arch_deinit();  // Nunca alcançado, pois o loop é infinito
    return 0;
}
