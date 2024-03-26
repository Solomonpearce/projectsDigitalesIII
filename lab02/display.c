#include "pico/stdlib.h"

// Define los pines GPIO para los LEDs
const uint LED_PIN1 = 2;
const uint LED_PIN2 = 3;
const uint LED_PIN3 = 4;

// Define el pin GPIO para el botón de inicio
const uint BUTTON_START = 5;

int main() {
    // Inicializa la biblioteca stdio
    stdio_init_all();

    // Configura los pines de los LEDs como salida
    gpio_init(LED_PIN1);
    gpio_set_dir(LED_PIN1, GPIO_OUT);
    gpio_init(LED_PIN2);
    gpio_set_dir(LED_PIN2, GPIO_OUT);
    gpio_init(LED_PIN3);
    gpio_set_dir(LED_PIN3, GPIO_OUT);

    // Configura el pin del botón de inicio como entrada
    gpio_init(BUTTON_START);
    gpio_set_dir(BUTTON_START, GPIO_IN);
    gpio_pull_up(BUTTON_START); // Activa la resistencia de pull-up interna

    // Espera a que se presione el botón de inicio
    while(true) {
        // Verifica si el botón de inicio está presionado (activo bajo)
        if(gpio_get(BUTTON_START) == 0) {
            // Secuencia de inicio de los LEDs después de presionar el botón
            // Enciende todos los LEDs (111)
            gpio_put(LED_PIN1, 1);
            gpio_put(LED_PIN2, 1);
            gpio_put(LED_PIN3, 1);
            sleep_ms(500); // Espera medio segundo

            // Cambia a (011)
            gpio_put(LED_PIN1, 0);
            sleep_ms(500);

            // Cambia a (001)
            gpio_put(LED_PIN2, 0);
            sleep_ms(500);

            // Cambia a (000)
            gpio_put(LED_PIN3, 0);
            sleep_ms(500);

            // Espera a que se suelte el botón antes de continuar
            while(gpio_get(BUTTON_START) == 0) {
                sleep_ms(10); // Evita la salida inmediata debido al rebote del botón
            }

            // Aquí puedes continuar con la siguiente fase del juego
            break; // Este break es solo un ejemplo, ajusta según tu lógica de juego
        }
        sleep_ms(10); // Pequeña pausa para evitar saturación del CPU
    }

    // Lógica adicional del juego aquí...

    return 0;
}
