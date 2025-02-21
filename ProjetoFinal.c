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
            motor_last_state = true;
        } else {
            buzzer_stop();
            buzzer_update_starwars(BUZZER_PIN);
            if (motor_last_state) {
                const char *msg[] = { "Motor parado" };
                display_show_text(msg, 1);
                sleep_ms(2000);
                display_show_welcome();
                motor_last_state = false;
            }
            joystick_update_display();
        }
        sleep_ms(100);
    }
    
    cyw43_arch_deinit();  // Nunca alcançado, pois o loop é infinito
    return 0;
}
