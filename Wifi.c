#include "wifi.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/tcp.h"
#include <string.h>
#include <stdio.h>
#include "motor.h"  // Para chamar motor_start() nos comandos HTTP

// Configurações Wi‑Fi
#define WIFI_SSID "iPhone de Anita"
#define WIFI_PASS "1234567890"

// HTML com links para os modos e para parar o motor
#define HTTP_RESPONSE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" \
"<!DOCTYPE html>" \
"<html lang=\"pt\">" \
"<head>" \
"  <meta charset=\"UTF-8\">" \
"  <title>Cerealmente</title>" \
"  <style>" \
"    body { " \
"      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; " \
"      background: linear-gradient(to right, #00c6ff, #0072ff); " \
"      color: #fff; " \
"      margin: 0; " \
"      padding: 0; " \
"    }" \
"    .container { " \
"      text-align: center; " \
"      padding: 50px; " \
"    }" \
"    h1 { " \
"      margin-bottom: 10px; " \
"      font-size: 3em; " \
"    }" \
"    h2 { " \
"      margin-bottom: 30px; " \
"      font-weight: 300; " \
"    }" \
"    a { " \
"      display: inline-block; " \
"      margin: 10px; " \
"      padding: 15px 30px; " \
"      background-color: rgba(0,0,0,0.2); " \
"      color: #fff; " \
"      text-decoration: none; " \
"      font-size: 1.2em; " \
"      border-radius: 8px; " \
"      transition: background-color 0.3s ease; " \
"    }" \
"    a:hover { " \
"      background-color: rgba(0,0,0,0.4); " \
"    }" \
"  </style>" \
"</head>" \
"<body>" \
"  <div class=\"container\">" \
"    <h1>Cerealmente</h1>" \
"    <h2>Selecione um modo para ajustar a quantidade desejada de cereal</h2>" \
"    <a href=\"/motor/pouco\">Pouco</a>" \
"    <a href=\"/motor/normal\">Normal</a>" \
"    <a href=\"/motor/muito\">Muito</a>" \
"    <a href=\"/motor/off\">Parar</a>" \
"  </div>" \
"</body>" \
"</html>\r\n"

// Callback HTTP para processar as requisições
static err_t http_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (p == NULL) {
        tcp_close(tpcb);
        return ERR_OK;
    }
    
    char *request = (char *)p->payload;
    
    // Verifica qual comando foi recebido e chama a função do módulo motor
    if (strstr(request, "GET /motor/pouco")) {
        motor_start(MODE_POUCO);
    } else if (strstr(request, "GET /motor/normal")) {
        motor_start(MODE_NORMAL);
    } else if (strstr(request, "GET /motor/muito")) {
        motor_start(MODE_MUITO);
    } else if (strstr(request, "GET /motor/off")) {
        motor_start(MODE_OFF);
    }
    
    tcp_write(tpcb, HTTP_RESPONSE, strlen(HTTP_RESPONSE), TCP_WRITE_FLAG_COPY);
    tcp_recved(tpcb, p->tot_len);
    pbuf_free(p);
    tcp_close(tpcb);
    
    return ERR_OK;
}

// Callback de nova conexão
static err_t connection_callback(void *arg, struct tcp_pcb *newpcb, err_t err) {
    tcp_recv(newpcb, http_callback);
    return ERR_OK;
}

// Função interna para iniciar o servidor HTTP
static void start_http_server(void) {
    struct tcp_pcb *pcb = tcp_new();
    if (!pcb) {
        printf("Erro ao criar PCB\n");
        return;
    }
    
    if (tcp_bind(pcb, IP_ADDR_ANY, 80) != ERR_OK) {
        printf("Erro ao ligar o servidor na porta 80\n");
        return;
    }
    
    pcb = tcp_listen(pcb);
    tcp_accept(pcb, connection_callback);
    
    printf("Servidor HTTP rodando na porta 80...\n");
}

void wifi_init_and_connect(void) {
    if (cyw43_arch_init()) {
        printf("Erro ao inicializar o Wi‑Fi\n");
        return;
    }
    cyw43_arch_enable_sta_mode();
    printf("Conectando ao Wi‑Fi...\n");
    
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Falha ao conectar ao Wi‑Fi\n");
        return;
    } else {
        printf("Connected.\n");
        uint8_t *ip_address = (uint8_t *)&(cyw43_state.netif[0].ip_addr.addr);
        printf("Endereço IP %d.%d.%d.%d\n", ip_address[0], ip_address[1], ip_address[2], ip_address[3]);
    }
    printf("Wi‑Fi conectado!\n");
    printf("Para selecionar um modo, acesse /motor/pouco, /motor/normal, /motor/muito ou /motor/off\n");
}

void wifi_start_http_server(void) {
    start_http_server();
}
