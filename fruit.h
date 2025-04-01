#ifndef __FRUIT__
#define __FRUIT__

#include "param.h"
#include "struct.h"

/**
 * @brief Fait apparaître un nouveau fruit
 * @return Une structure de fruit
 */
fruit_t spawn_fruit();

/**
 * @private
 * @brief L’effet d’un fruit normal (agrandir le serpent)
 * @param snake Le serpent à agrandir
 */
void normal_effect(snake_t snake);

/**
 * @private
 * @brief L’effet d’un fruit accélérant
 * @param snake Le serpent à accélérer
 */
void speed_effect(snake_t snake);

#endif
