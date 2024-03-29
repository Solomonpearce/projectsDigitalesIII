/**
 * @file main.c
 * @brief Archivo principal del juego de reacción.
 * @author Harold Gómez
 * @date 2024-25-03
 */

#include "pico/stdlib.h"
#include "game_logic.h"

/**
 * @brief Función principal del programa.
 * 
 * Esta función inicializa el sistema de E/S estándar y luego entra en el bucle del juego.
 * 
 * @return Siempre devuelve 0.
 */
int main() {
    stdio_init_all(); // Inicializar el sistema de E/S estándar
    
    /**
     * @brief Iniciar el bucle del juego.
     * 
     * Esta función se encarga de controlar el flujo del juego.
     */
    game_loop();

    return 0;
}