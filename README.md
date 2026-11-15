<div align="center">

# 🥣 Cerealmente

**Dispenser de cereal com Raspberry Pi Pico W, controlado por Wi-Fi ou pelo joystick.**

*Projeto final do curso Embarcatech de Sistemas Embarcados.*

<br>

![Raspberry Pi Pico W](https://img.shields.io/badge/Raspberry_Pi-Pico_W-E8A0BF?style=for-the-badge&logo=raspberrypi&logoColor=white)
![C](https://img.shields.io/badge/C-Pico_SDK-E8A0BF?style=for-the-badge&logo=c&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-build-E8A0BF?style=for-the-badge&logo=cmake&logoColor=white)
![Wi-Fi](https://img.shields.io/badge/Wi--Fi-HTTP-E8A0BF?style=for-the-badge&logo=wifi&logoColor=white)

[Visão geral](#-visão-geral) ·
[Hardware](#-hardware) ·
[Arquitetura](#-arquitetura-do-firmware) ·
[Como compilar](#%EF%B8%8F-como-compilar-e-gravar) ·
[Uso](#-uso)

</div>

<br>

## ✨ Visão geral

O Cerealmente libera cereal em três quantidades (**Pouco**, **Normal** ou **Muito**) usando um servo de rotação contínua. Dá para acionar de dois jeitos:

| | |
|---|---|
| 🌐 **Remoto** | A Pico W sobe um servidor HTTP na porta 80. Pelo navegador você escolhe a quantidade ou para o motor. |
| 🕹️ **Local** | O joystick escolhe a quantidade, o botão **A** confirma e o botão **B** interrompe. |
| 🖥️ **Feedback** | Mensagens no display OLED, animação de seta na matriz WS2812B e música no buzzer enquanto o motor gira. |

## 🔌 Hardware

| Componente | Função |
|---|---|
| Raspberry Pi Pico W / BitDogLab | Microcontrolador RP2040 e Wi-Fi (CYW43) |
| Servo de rotação contínua (DS04-NFC ou similar) | Libera o cereal (PWM) |
| Display OLED 128×64 (I2C) | Mensagens e instruções |
| Matriz de LEDs WS2812B 5×5 | Animação durante a liberação (PIO) |
| Buzzer passivo | Música durante a liberação (PWM) |
| Joystick analógico KY-023 | Seleção da quantidade (ADC) |
| Botões A e B | Confirmar e cancelar |
| Fonte 5 V dedicada | Alimentação do servo |

> 💡 Alimente o servo com uma fonte 5 V separada, ligando o GND dela ao da Pico, para evitar quedas de tensão quando o motor arranca.

## 🧩 Arquitetura do firmware

Cada periférico tem seu próprio módulo, e o `ProjetoFinal.c` só orquestra:

```
Cerealmente/
├── ProjetoFinal.c       # loop principal e máquina de estados
├── Wifi.c / .h          # conexão Wi-Fi + servidor HTTP (lwIP)
├── Motor.c / .h         # PWM do servo (Pouco / Normal / Muito)
├── Joystick.c / .h      # leitura do ADC e navegação
├── Display.c / .h       # OLED via I2C
├── MatrizRGB.c / .h     # WS2812B via PIO
├── frames_rgb.c / .h    # quadros da animação
├── Buzzer.c / .h        # notas musicais via PWM
├── GPIO.c / .h          # botões e LEDs
├── LedRGB.c / .h        # LED RGB comum
├── lwipopts.h           # configuração da pilha TCP/IP
└── CMakeLists.txt
```

## 🛠️ Como compilar e gravar

**Pré-requisitos:** [Pico SDK](https://github.com/raspberrypi/pico-sdk) com `PICO_SDK_PATH` configurado, CMake 3.13+ e o toolchain `arm-none-eabi-gcc`.

```bash
git clone https://github.com/anita211/Cerealmente.git
cd Cerealmente
mkdir build && cd build
cmake ..
make
```

Para gravar, segure **BOOTSEL** ao conectar a Pico W no USB e copie o `.uf2` gerado para o disco que aparecer.

## 🚀 Uso

1. Configure o SSID e a senha da sua rede em `Wifi.c`.
2. Ligue a placa. O IP aparece no monitor serial USB.
3. Acesse `http://<ip-da-pico>/` para controlar pelo navegador **ou** use o joystick e os botões.

## 🙏 Créditos

- Plataforma [BitDogLab](https://github.com/BitDogLab/BitDogLab-C) e documentação oficial do RP2040.
- Programa **Embarcatech** de capacitação em sistemas embarcados.

<div align="center">
<br>
<sub>Feito com 💗 por <a href="https://github.com/anita211">Anita Oliveira</a></sub>
</div>
