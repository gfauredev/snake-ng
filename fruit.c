// Gestion des fruits
#include <SDL3/SDL_log.h>
#include <stdlib.h>

#include "fruit.h"
#include "param.h"
#include "struct.h"

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
 * @brief Effet fruit normal: aggrandis le serpent
 * @param snake Le serpent à aggrandir
 */
void normal_effect(snake_t* snake)
{
    snake->length += 1; // Agrandir le serpent
}

/**
 * @brief Effet fruit speed: accélère le serpent
 * @param snake Le serpent à accélérer
 */
void speed_effect(snake_t* snake)
{
    snake->length += 1; // Agrandir le serpent
    snake->speed += 1;  // Accélère le serpent
}

/**
 * @brief Effet fruit speed: accélère le serpent
 * @param snake Le serpent à accélérer
 */
void double_effect(snake_t* snake)
{
    snake->length += 2; // Agrandir plus le serpent
}
effect_t effects[] = {
    {normal_effect, FRUIT_NORMAL_C},
    { speed_effect,  FRUIT_SPEED_C},
    {double_effect, FRUIT_DOUBLE_C}
};

// Probabilités d’apparition des effets
#define PROBA_ALL 100
uint8_t effects_proba[] = {70, 20, 10};

/**
 * @brief Fais apparaître un fruit quelque part sur la zone de jeu
 */
fruit_t* spawn_fruit()
{
    fruit_t* fruit = malloc(sizeof(fruit_t));
    fruit->x       = rand_range(1, MAP_WIDTH - 1);
    fruit->y       = rand_range(1, MAP_HEIGHT - 1);
    if (DEBUG >= 1)
        SDL_Log("Fruit: Apparition (%d, %d)", fruit->x, fruit->y); // DEBUG
    uint8_t effect_index = 0;
    uint8_t proba        = rand_range(0, PROBA_ALL);
    if (DEBUG >= 2)
        SDL_Log("\tRNG: %d", proba); // DEBUG
    while (1)
    {
        if (proba > effects_proba[effect_index])
        {
            proba -= effects_proba[effect_index];
            effect_index++;
        }
        else
            break;
    }
    if (DEBUG >= 2)
        SDL_Log("\tEffet: %d", effect_index); // DEBUG
    fruit->effect = effects[effect_index].effect;
    fruit->color  = effects[effect_index].color;
    return fruit;
}
