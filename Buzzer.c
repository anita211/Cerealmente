 #include "Buzzer.h"

// Notas musicais para a música tema de Star Wars
const uint star_wars_notes[] = {
    330, 330, 330, 262, 392, 523, 330, 262,
    392, 523, 330, 659, 659, 659, 698, 523,
    415, 349, 330, 262, 392, 523, 330, 262,
    392, 523, 330, 659, 659, 659, 698, 523,
    415, 349, 330, 523, 494, 440, 392, 330,
    659, 784, 659, 523, 494, 440, 392, 330,
    659, 659, 330, 784, 880, 698, 784, 659,
    523, 494, 440, 392, 659, 784, 659, 523,
    494, 440, 392, 330, 659, 523, 659, 262,
    330, 294, 247, 262, 220, 262, 330, 262,
    330, 294, 247, 262, 330, 392, 523, 440,
    349, 330, 659, 784, 659, 523, 494, 440,
    392, 659, 784, 659, 523, 494, 440, 392
};

// Duração das notas em milissegundos
const uint note_duration[] = {
    500, 500, 500, 350, 150, 300, 500, 350,
    150, 300, 500, 500, 500, 500, 350, 150,
    300, 500, 500, 350, 150, 300, 500, 350,
    150, 300, 650, 500, 150, 300, 500, 350,
    150, 300, 500, 150, 300, 500, 350, 150,
    300, 650, 500, 350, 150, 300, 500, 350,
    150, 300, 500, 500, 500, 500, 350, 150,
    300, 500, 500, 350, 150, 300, 500, 350,
    150, 300, 500, 350, 150, 300, 500, 500,
    350, 150, 300, 500, 500, 350, 150, 300,
};

// Variáveis internas para a máquina de estados da música
static uint note_index = 0;
static uint32_t note_start_time = 0;
static bool note_active = false;   // Indica se uma nota (ou descanso) está em andamento
static bool gap_started = false;   // Indica se a pausa entre notas já começou
static uint32_t gap_start_time = 0;
static bool buzzer_enabled = true;
 
 // Inicializa o PWM no pino do buzzer
 void pwm_init_buzzer(uint pin) {
     gpio_set_function(pin, GPIO_FUNC_PWM);
     uint slice_num = pwm_gpio_to_slice_num(pin);
     pwm_config config = pwm_get_default_config();
     pwm_config_set_clkdiv(&config, 4.0f); // Ajusta divisor de clock
     pwm_init(slice_num, &config, true);
     pwm_set_gpio_level(pin, 0); // Desliga o PWM inicialmente
 }
 
 /*
 // Toca uma nota com a frequência e duração especificadas
 void play_tone(uint pin, uint frequency, uint duration_ms) {
     uint slice_num = pwm_gpio_to_slice_num(pin);
     uint32_t clock_freq = clock_get_hz(clk_sys);
     uint32_t top = clock_freq / frequency - 1;
 
     pwm_set_wrap(slice_num, top);
     pwm_set_gpio_level(pin, top / 2); // 50% de duty cycle
 
     sleep_ms(duration_ms);
 
     pwm_set_gpio_level(pin, 0); // Desliga o som após a duração
     sleep_ms(50); // Pausa entre notas
 }
 
 // Função principal para tocar a música
 void play_star_wars(uint pin) {
     for (int i = 0; i < sizeof(star_wars_notes) / sizeof(star_wars_notes[0]); i++) {
         if (star_wars_notes[i] == 0) {
             sleep_ms(note_duration[i]);
         } else {
             play_tone(pin, star_wars_notes[i], note_duration[i]);
         }
     }
 }
*/

// Função de atualização não bloqueante para tocar a música Star Wars.
// Essa função deve ser chamada periodicamente (por exemplo, no loop principal).
void buzzer_update_starwars(uint pin) {
    // Se a reprodução estiver desabilitada, garanta que o PWM esteja desligado e retorne.
    if (!buzzer_enabled) {
        uint slice_num = pwm_gpio_to_slice_num(pin);
        pwm_set_enabled(slice_num, false);
        return;
    }

    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    int total_notes = sizeof(star_wars_notes) / sizeof(star_wars_notes[0]);

    if (!note_active) {
        // Inicia a reprodução da nota atual
        if (note_index < total_notes) {
            note_start_time = current_time;
            note_active = true;
            // Se a nota for diferente de 0, toca a frequência; senão, é um descanso.
            if (star_wars_notes[note_index] != 0) {
                uint slice_num = pwm_gpio_to_slice_num(pin);
                uint32_t clock_freq = clock_get_hz(clk_sys);
                uint32_t top = clock_freq / star_wars_notes[note_index] - 1;
                pwm_set_wrap(slice_num, top);
                pwm_set_gpio_level(pin, top / 2); // Duty cycle de 50%
                pwm_set_enabled(slice_num, true);
            } else {
                // Descanso: garante que o PWM esteja desligado.
                uint slice_num = pwm_gpio_to_slice_num(pin);
                pwm_set_enabled(slice_num, false);
            }
        }
    } else {
        // Nota (ou descanso) em andamento; verifica se atingiu a duração.
        uint32_t current_note_duration = note_duration[note_index];
        if (current_time - note_start_time >= current_note_duration) {
            // Finaliza a nota: desliga o PWM.
            uint slice_num = pwm_gpio_to_slice_num(pin);
            pwm_set_enabled(slice_num, false);

            // Inicia a pausa (gap) de 50 ms entre as notas.
            if (!gap_started) {
                gap_start_time = current_time;
                gap_started = true;
            } else {
                if (current_time - gap_start_time >= 50) {
                    // Pausa concluída; avança para a próxima nota.
                    note_index++;
                    if (note_index >= total_notes)
                        note_index = 0; // Reinicia a música se chegar ao fim.
                    // Reseta os estados para iniciar a próxima nota.
                    note_active = false;
                    gap_started = false;
                }
            }
        }
    }
}

//
// Para a reprodução da música, desabilitando a atualização da máquina de estados.
//
void buzzer_stop(void) {
    buzzer_enabled = false;
    // Desliga o PWM imediatamente (assumindo que o buzzer está em BUZZER_A)
    // Note: O pino deve ser informado na chamada de update. Aqui usamos uma abordagem genérica.
}

//
// Retoma a reprodução da música.
//
void buzzer_resume(void) {
    buzzer_enabled = true;
}