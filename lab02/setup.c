/**
 * @file setup.c
 * @brief Archivo para la configuración inicial de los pines del MCU.
 * @author Harold Gómez - Juan Carlos Medina 
 * @date 2024-27-03
 */

#include "setup.h"
#include "pico/stdlib.h"

/**
 * @mainpage Configuración de los pines
 * 
 * Nuestro display de 7 segmentos tiene los pines de la siguiente manera:
 * 
 *  --A--
 *  F   B
 *  --G--
 *  E   C
 *  --D--
 */

// Se definen los pines para los leds y los botones.
const uint LED_PINS[3] = {2, 3, 4}; 
const uint BUTTON_STARGAME = 5;
const uint FIRST_GPIO = 16;
const uint BUTTON_GPIO_3 = 26;
const uint BUTTON_GPIO_2 = 27;
const uint BUTTON_GPIO_1 = 28;
const uint GPIO_NPN1 = 6;
const uint GPIO_NPN2 = 7;
const uint GPIO_NPN3 = 8;
const uint GPIO_NPN4 = 9;

/**
 * @brief Inicializa los pines de los LEDs , botones, transistores y siete segmentos.
 * 
 * Esta función configura los pines asignados  como entradas o salidas según corresponda.
 */
void init_pins() {
  // Se activan los pines en los cuales están los leds
  for (int i = 0; i < 3; i++) {
    gpio_init(LED_PINS[i]);
    gpio_set_dir(LED_PINS[i], GPIO_OUT);
  }

  // Inicializa el pin del boton de inicio.
  gpio_init(BUTTON_STARGAME);
  gpio_set_dir(BUTTON_STARGAME, GPIO_IN);
  gpio_pull_up(BUTTON_STARGAME);

  // Inicializa los pines de los botones.
  gpio_init(BUTTON_GPIO_3);
  gpio_set_dir(BUTTON_GPIO_3, GPIO_IN);
  gpio_pull_up(BUTTON_GPIO_3);
  gpio_init(BUTTON_GPIO_2);
  gpio_set_dir(BUTTON_GPIO_2, GPIO_IN);
  gpio_pull_up(BUTTON_GPIO_2);
  gpio_init(BUTTON_GPIO_1);
  gpio_set_dir(BUTTON_GPIO_1, GPIO_IN);
  gpio_pull_up(BUTTON_GPIO_1);

  // Inicializa los pines de los transistores NPN.
  gpio_init(GPIO_NPN1);
  gpio_set_dir(GPIO_NPN1, GPIO_OUT);
  gpio_init(GPIO_NPN2);
  gpio_set_dir(GPIO_NPN2, GPIO_OUT);
  gpio_init(GPIO_NPN3);
  gpio_set_dir(GPIO_NPN3, GPIO_OUT);
  gpio_init(GPIO_NPN4);
  gpio_set_dir(GPIO_NPN4, GPIO_OUT);

  // Inicializa los pines de los segmentos del display.
  for (int gpio = FIRST_GPIO; gpio < FIRST_GPIO + 7; gpio++) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_set_outover(gpio, GPIO_OVERRIDE_INVERT);
  }
}