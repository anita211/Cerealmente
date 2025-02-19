#include "pico/stdlib.h"
#include "wifi.h"
#include "motor.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include "lwip/tcp.h"
#include <string.h>
#include "hardware/pwm.h"

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
    
    // Loop principal: atualiza o estado do motor e mantém o Wi‑Fi ativo
    while (true) {
        cyw43_arch_poll();
        motor_update();
        sleep_ms(100);
    }
    
    cyw43_arch_deinit();  // Nunca alcançado, pois o loop é infinito
    return 0;
}
