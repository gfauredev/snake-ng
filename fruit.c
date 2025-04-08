// fruit.c

#include <stdlib.h>

#include "fruit.h"
#include "param.h"

/**
 * @brief Générer un nombre aléatoire dans un intervalle donné
 * @param min Minimum
 * @param max Maximum
 */
uint32_t rand_range(uint32_t min, uint32_t max)
{
    return min + rand() % (max - min + 1);
}

/**
 * @brief Fais apparaître un fruit quelque part sur la zone de jeu
 */
fruit_t spawn_fruit()
{
    fruit_t new_fruit;
    new_fruit.color  = FRUIT1_C;
    new_fruit.x      = rand_range(1, MAP_WIDTH - 1);
    new_fruit.y      = rand_range(1, MAP_HEIGHT - 1);
    new_fruit.effect = normal_effect;
    return new_fruit;
}

/**
 * @brief Effet fruit normal: aggrandis le serpent
 * @param snake Le serpent à aggrandir
 */
void normal_effect(snake_t* snake)
{
    // Agrandir le serpent
    snake->length += 1;
}

/**
 * @brief Effet fruit speed: accélère le serpent
 * @param snake Le serpent à accélérer
 */
void speed_effect(snake_t* snake)
{
    snake->speed += 1;
}
