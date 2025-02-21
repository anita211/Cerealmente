#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include "lwip/tcp.h"
#include <string.h>
#include "hardware/pwm.h"

#include "Wifi.h"
#include "Motor.h"
#include "Display.h"

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
    
    // Loop principal: atualiza o estado do motor e mantém o Wi‑Fi ativo
    while (true) {
        cyw43_arch_poll();
        motor_update();
        if (motor_is_active()) {
            //display_show_motor_active();
            display_show_text("Motor ativo");
        } else {
            display_show_welcome();
        }
        sleep_ms(100);
    }
    
    cyw43_arch_deinit();  // Nunca alcançado, pois o loop é infinito
    return 0;
}
