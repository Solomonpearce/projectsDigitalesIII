/**
 * @file game_logic.c 
 * @brief archivo de implementación de la logica del juego
 * @author Harold Gómez 
 * @date 2024-25-03 
 * @author Juan Carlos Medina
 * @date 2024-28-03
 */


#include "game_logic.h"
#include "pico/stdlib.h"
#include "setup.h"
#include <stdlib.h>
#include "hardware/gpio.h"
#include <stdio.h>
#include "pico/time.h"

// Se reutilizan los pines de otro modulo con extern
extern const uint LED_PINS[3];
extern const uint BUTTON_STARGAME;
extern const uint BUTTON_GPIO_3;
extern const uint BUTTON_GPIO_2;
extern const uint BUTTON_GPIO_1;
extern const uint FIRST_GPIO;
extern const uint GPIO_NPN1;
extern const uint GPIO_NPN2;
extern const uint GPIO_NPN3;
extern const uint GPIO_NPN4;


/**
 * @brief Secuencia de inicio de los leds del juego.
 * 
 * Enciende y apaga los leds en un patrón específico.
 */
void start_sequence()
{
    for (int i = 2; i >= 0; i--)
    {
        gpio_put(LED_PINS[i], 1);
    }
    // Tiempo de espera para apagar los leds
    sleep_ms(500);

    // APAGADO
    for (int i = 0; i < 3; i++)
    {
        gpio_put(LED_PINS[i], 0);
        sleep_ms(500);
    }
}

/**
 * @brief Espera a que se presione el botón de inicio.
 * 
 * Esta función se encarga de esperar a que se presione el botón de inicio.
 */
void wait_for_button_press()
{
    // Espera a que se presione el botón de inicio
    while (gpio_get(BUTTON_STARGAME) == 1)
    {
        tight_loop_contents();
    }
    // Debounce - Espera un momento para evitar rebotes del botón
    sleep_ms(200);
}

/**
 * @brief Genera un tiempo aleatorio de espera.
 * 
 * Genera un tiempo aleatorio entre 1 y 10 segundos.
 */
void random_time()
{
    unsigned int wait_time = 1 + rand() % 10;
    sleep_ms(wait_time * 1000); // conversión a milisegundos y espera.
}

/**
 * @brief Enciende un led aleatorio.
 * 
 * Enciende un led aleatorio de los tres disponibles.
 * 
 * @param led_on Un puntero a una variable que se actualizará con el índice del LED encendido.
 */
void random_led(uint *led_on)
{

    *led_on = rand() % 3;
    gpio_put(LED_PINS[*led_on], 1); // Enciende el led al que se apunta
    
}

/**
 * @brief Espera a que se presione un botón y actualiza la variable button_on.
 * 
 * @param button_on Un puntero a una variable que se actualizará con el índice del botón presionado.
 */
void selection_button(uint *button_on)
{

    // Espera a que se presione el botón de inicio
    if (!gpio_get(BUTTON_GPIO_3) == 1)
    {
        *button_on = 2;
    }
    else if (!gpio_get(BUTTON_GPIO_2) == 1)
    {
        *button_on = 1;
    }
    else if (!gpio_get(BUTTON_GPIO_1) == 1)
    {
        *button_on = 0;
    }
}


/**
 * @brief Controla el display de 7 segmentos.
 * 
 * @param led_on Un puntero a una variable que contiene el índice del LED encendido.
 */
void L7seg(uint *led_on)
{
    int sec = 0;
    int sec2 = 0;
    int min = 0;
    int min2 = 0;
    int ya = 0;
    uint button_on = 5;
    int Error = 0;
    int Pena = 0;
    int ErrorP = 0;
    int bits[14] = {
        0x3f, // 0
        0x06, // 1
        0x5b, // 2
        0x4f, // 3
        0x66, // 4
        0x6d, // 5
        0x7d, // 6
        0x07, // 7
        0x7f, // 8
        0x67, // 9
        0x54, // n
        0x5c, // o
        0x0,  // Apagado
        0x73  // P
    };
    while (ya == 0)
    {
        /**
         * @details
         * 
         * Cuenta hacia arriba o hacia abajo dependiendo de la entrada del botón.
         * Estamos haciendo un pull down en el switch activo, por lo que invertimos el get para hacer
         * que una presión cuente hacia abajo.
         */

        if (sec == 9)
        {
            sec = 0;

            if (sec2 == 9)
            {
                sec2 = 0;
                if (Pena > 0)
                {
                    min2++;
                    Pena = 0;
                }
                if (min == 9)
                {
                    min = 0;
                    if (min2 >= 9)
                    {
                        min2 = 0;
                        ErrorP = 1;
                        sec2 = 12;
                        sec = 13;
                        min = 11;
                        min2 = 10;
                    }
                    else
                    {
                        min2++;
                    }
                }
                else
                {
                    min++;
                }
            }
            else
            {
                sec2++;
            }
        }
        else
        {
            sec++;
        }

        absolute_time_t end_time = make_timeout_time_us(1000);
        while (!time_reached(end_time))
        {
            selection_button(&button_on);
            if (button_on == *led_on)
            {
                Error = 1;
                gpio_put(LED_PINS[*led_on], 0);
                sec2 = *led_on;
                min = button_on;
            }
            else if (button_on == 0 || button_on == 1 || button_on == 2)
            {
                Error = 0;
                if (!gpio_get(BUTTON_GPIO_3) == 1 || !gpio_get(BUTTON_GPIO_2) == 1 || !gpio_get(BUTTON_GPIO_1) == 1)
                {
                    Pena++;
                }
            }
            else
            {
                Error = 0;
            }
            do
            {
                int32_t mask = bits[sec] << FIRST_GPIO;
                int32_t maskG = 0x7F << FIRST_GPIO; // se cambia el valor de 7 pines
                gpio_put_masked(maskG, mask);

                // gpio_put(LED_PINS[FIRST_GPIO], (bits[sec] >> FIRST_GPIO)& 1);
                gpio_put(GPIO_NPN2, 0);
                gpio_put(GPIO_NPN3, 0);
                gpio_put(GPIO_NPN1, 0);
                gpio_put(GPIO_NPN4, 1);
                absolute_time_t end_time1 = make_timeout_time_us(250);

                while (!time_reached(end_time1))
                {
                    tight_loop_contents();
                }
                gpio_clr_mask(mask);

                int32_t mask1 = bits[sec2] << FIRST_GPIO;
                gpio_put_masked(maskG, mask1);

                // gpio_put(LED_PINS[FIRST_GPIO], (bits[sec2] >> FIRST_GPIO)& 1);
                gpio_put(GPIO_NPN1, 0);
                gpio_put(GPIO_NPN3, 0);
                gpio_put(GPIO_NPN2, 0);
                gpio_put(GPIO_NPN3, 1);
                absolute_time_t end_time2 = make_timeout_time_us(250);
                while (!time_reached(end_time2))
                {
                    tight_loop_contents();
                }
                gpio_clr_mask(mask1);
                int32_t mask2 = bits[min] << FIRST_GPIO;
                gpio_put_masked(maskG, mask2);
                // gpio_put(LED_PINS[FIRST_GPIO], (bits[min] >> FIRST_GPIO)& 1);
                gpio_put(GPIO_NPN1, 0);
                gpio_put(GPIO_NPN3, 0);
                gpio_put(GPIO_NPN4, 0);
                gpio_put(GPIO_NPN2, 1);
                absolute_time_t end_time3 = make_timeout_time_us(250);
                while (!time_reached(end_time3))
                {
                    tight_loop_contents();
                }
                gpio_clr_mask(mask2);
                int32_t mask3 = bits[min2] << FIRST_GPIO;
                gpio_put_masked(maskG, mask3);
                // gpio_put(LED_PINS[FIRST_GPIO], (bits[min2] >> FIRST_GPIO)& 1);
                gpio_put(GPIO_NPN4, 0);
                gpio_put(GPIO_NPN2, 0);
                gpio_put(GPIO_NPN3, 0);
                gpio_put(GPIO_NPN1, 1);
                absolute_time_t end_time4 = make_timeout_time_us(250);
                while (!time_reached(end_time4))
                {
                    tight_loop_contents();
                }

                gpio_clr_mask(mask3);
                if ((!gpio_get(BUTTON_STARGAME) == 1 && Error == 1) || (!gpio_get(BUTTON_STARGAME) == 1 && ErrorP == 1))
                {

                    ya = 0;
                    Error = 0;
                    game_loop();
                }
            } while (Error == 1 || ErrorP == 1);
        }

        /**
         * @details
         * 
         * Estamos comenzando con GPIO 2, nuestro mapa de bits comienza en el bit 0, por lo que se desplaza para comenzar en 2.
         */
        // int32_t mask = bits[val] << FIRST_GPIO;

        /**
         * @details
         * 
         * ¡Establece todos nuestros GPIOs de una vez.
         * Si algo más está usando GPIO, es posible que queramos usar gpio_put_masked()
         */
        // gpio_set_mask(mask);
        // sleep_ms(250);
        // gpio_clr_mask(mask);
    }
}

/**
 * @brief Inicia el bucle del juego.
 * 
 * Esta función se encarga de controlar el flujo del juego.
 */
void game_loop()
{
    uint led_on = 5;

    init_pins();

    while (true)
    {
        wait_for_button_press(); // Espera la presión del botón con debounce
        start_sequence();        // Inicia la secuencia de los LEDs
        // Aquí ira el resto de la lógica del juego
        random_time();
        random_led(&led_on);

        L7seg(&led_on);
    }
}