// fruit.c

#include "fruit.h"
#include <stdlib.h>
#include <time.h>

// Générer un nombre aléatoire dans un intervalle donné
uint32_t rand_range(uint32_t min, uint32_t max) {
    return min + rand() % (max - min + 1);
}
//
fruit_t spawn_fruit() {
    fruit_t new_fruit;
    new_fruit.color= RED;
    new_fruit.x = rand_range(0,MAP_WIDTH);
    new_fruit.y = rand_range(0,MAP_HEIGHT);
    new_fruit.effect = normal_effect;
    return new_fruit;
}

void normal_effect(snake_t *snake) {
    // Agrandir le serpent
    snake->lenght += 1;
}

void speed_effect(snake_t *snake) {
    snake->speed += 1;
}
