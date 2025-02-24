# Cerealmente

Repositório contendo o código-fonte de um **dispenser de cereal** baseado na BitDogLab (Raspberry Pi Pico W). O projeto permite **ativar a liberação de cereal** tanto via **rede Wi-Fi** (HTTP) quanto localmente, usando **joystick** e **botões**. Além disso, exibe mensagens em um **display OLED**, reproduz **som** em um buzzer e mostra **animações** numa matriz de LEDs endereçáveis (WS2812B).

## Visão Geral

O dispenser é formado pelos seguintes componentes principais:

- **Raspberry Pi Pico W / BitDogLab**: Microcontrolador que gerencia toda a lógica, incluindo leitura de sensores (joystick, botões) e controle do motor (servo 360°).  
- **Display OLED** (128×64, I2C): Exibe mensagens ao usuário indicando estado do sistema ou instruções de uso.  
- **Buzzer**: Reproduz uma música (tema de Star Wars) enquanto o cereal está sendo liberado.  
- **Matriz de LEDs WS2812B** (5×5): Mostra uma animação de seta, indicando o acionamento do motor.  
- **Joystick e botões** (A e B): Permitem navegação pelas opções de quantidade de cereal e confirmação/cancelamento da liberação.  
- **Servo Motor 360°**: Responsável por liberar o cereal em três modos: Pouco, Normal ou Muito.  
- **Wi-Fi**: Implementado pelo módulo integrado à Pico W, possibilitando ativar o dispenser via navegador (HTTP).

## Recursos Principais

1. **Controle Remoto (via HTTP)**  
   - O projeto inicia um servidor HTTP na porta 80.  
   - Ao acessar o endereço IP da Pico W, o usuário encontra links para acionar “Pouco”, “Normal”, “Muito” ou “Parar” o dispenser.

2. **Controle Local (Joystick + Botões)**  
   - O joystick seleciona a quantidade de cereal a liberar (Pouco, Normal ou Muito).  
   - O botão A confirma a seleção e aciona o motor.  
   - O botão B interrompe a liberação de cereal a qualquer momento.

3. **Feedback Visual e Sonoro**  
   - **Display OLED** exibe mensagens de boas-vindas, estado do motor e instruções.  
   - **Buzzer** toca uma música enquanto o motor está ativo.  
   - **Matriz de LEDs** apresenta uma animação de seta apontando para baixo durante a liberação.

4. **Organização em Múltiplos Módulos**  
   - **Buzzer.c / Buzzer.h**: Controle de PWM para notas musicais.  
   - **Motor.c / Motor.h**: Gerenciamento de PWM para o servo motor (modos Pouco, Normal, Muito).  
   - **Display.c / Display.h**: Funções para exibir textos no OLED (via I2C).  
   - **Joystick.c / Joystick.h**: Leitura de valores do ADC e gerenciamento de estados do joystick.  
   - **MatrizRGB.c / MatrizRGB.h**: Inicializa e controla a PIO para LEDs NeoPixel.  
   - **Wifi.c / Wifi.h**: Conexão à rede Wi-Fi e servidor HTTP para comandos remotos.  
   - **GPIO.c / GPIO.h**: Configuração de pinos (botões, LED).  
   - **LedRGB.c / LedRGB.h**: Exemplo para LEDs RGB comuns (caso seja usado).  
   - **frames_rgb.c / frames_rgb.h**: Dados de animação para a matriz WS2812B.  

## Estrutura de Pastas (Principais)

```
Ceralmente/
├── Buzzer.c
├── Buzzer.h
├── Display.c
├── Display.h
├── GPIO.c
├── GPIO.h
├── Joystick.c
├── Joystick.h
├── LedRGB.c
├── LedRGB.h
├── MatrizRGB.c
├── MatrizRGB.h
├── Motor.c
├── Motor.h
├── Wifi.c
├── Wifi.h
├── ProjetoFinal.c
├── frames_rgb.c
├── frames_rgb.h
└── ...
```

## Requisitos de Hardware

- Placa **Raspberry Pi Pico W** (ou BitDogLab, que integra o mesmo microcontrolador).  
- **Servo Motor** de rotação contínua (DS04-NFC ou similar).  
- **Display OLED** 128×64 I2C.  
- **Buzzer passivo** (para gerar as notas).  
- **Matriz de LEDs** WS2812B (5×5).  
- **Joystick** analógico (KY-023).  
- **Dois botões** (A e B) com resistores de pull-up se necessário.  
- Fonte de alimentação 5V com corrente suficiente para o servo.

## Compilação e Gravação

1. **Clonar o Repositório**  
   ```bash
   git clone https://github.com/anita211/Ceralmente.git
   cd Ceralmente
   ```

2. **Configurar o SDK da Raspberry Pi Pico**  
   - Garantir que o `PICO_SDK_PATH` esteja definido corretamente no seu sistema.  
   - Instalar CMake (versão 3.13 ou superior) e um compilador compatível (GCC para ARM, etc.).

3. **Compilar**  
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
   Isso gera o arquivo `.uf2` ou `.elf`, dependendo da sua configuração.

4. **Gravar na Pico W**  
   - Conectar a Pico W ao computador enquanto mantém o botão BOOTSEL pressionado.  
   - Aparecerá como um disco USB. Copiar o arquivo `.uf2` para esse disco.  
   - A Pico W irá reiniciar rodando o firmware recém-gravado.

## Executando o Projeto

- **Inicialização**: Ao ligar a placa, o sistema realiza as configurações de Wi-Fi, Display, Buzzer, etc.  
- **Wi-Fi**: A Pico W tenta se conectar à rede cujo SSID e senha estão configurados no código (`Wifi.c`). Verifique e edite caso necessário.  
- **Servidor HTTP**: Depois de conectado, imprime o IP no console serial (`printf`). Acesse `http://<IP-da-Pico>/` no navegador para controlar o dispenser remotamente.  
- **Controle Local**:  
  - Use o **joystick** para navegar entre as opções (Pouco, Normal, Muito).  
  - Pressione **botão A** para confirmar e acionar o motor.  
  - Pressione **botão B** para cancelar/interromper.

## Testes e Depuração

- Através de mensagens `printf` em USB Serial, é possível monitorar o estado do sistema (ex.: mensagens de debug, IP adquirido, modo do motor).  
- É recomendável alimentar o servo motor com uma fonte 5V dedicada (conectando GND com o da Pico) para evitar quedas de tensão durante o acionamento.

## Licença

O código-fonte é disponibilizado **sem garantia** de funcionamento para quaisquer fins específicos. Consulte o arquivo de licença (caso exista um LICENSE.md) ou aplique a licença do seu interesse. Caso contrário, assuma uso livre para fins de estudo/educação.

## Créditos e Referências

- **BitDogLab** e **Raspberry Pi Pico W** para a plataforma de hardware.  
- Comunidade **Embarcados** e **Documentação oficial do RP2040** para suporte e exemplos.  
- Código e exemplos inspirados em [Exemplos da BitDogLab](https://github.com/BitDogLab/BitDogLab-C).  

## Contato

Caso tenha dúvidas ou sugestões de melhoria, entre em contato via [GitHub Issues](https://github.com/anita211/Ceralmente/issues) ou abra um **Pull Request**. 

Boa diversão com o **Cerealmente**!
