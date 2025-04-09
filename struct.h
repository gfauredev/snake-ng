// Structures communes
#ifndef __STRUCT__
#define __STRUCT__

// #define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <stdint.h>

/**
 * @typedef vect_t
 * @brief structure vecteur
 */
typedef struct vect_s
{
    int8_t x; ///< Position horizontale
    int8_t y; ///< Position verticale
} vect_t;

/**
 * @typedef snake_part_t
 * @brief structure corps du serpent
 */
typedef struct snake_part_s
{
    uint32_t x;    ///< Position horizontale
    uint32_t y;    ///< Position verticale
    vect_t   vect; ///< Mouvement
} snake_part_t;

/**
 * @typedef snake_t
 * @struct snake_s
 * @brief Structure représentant le serpent
 */
typedef struct snake_s
{
    snake_part_t* head; ///< Tête du serpent
    snake_part_t* body; ///< Corps du serpent, tableau de `snake_part_t`[length]
    uint16_t      length; ///< Longueur du corps du serpent, sans la tête `head`
    uint16_t      length_body_tab; ///< Longueur max du tableau body
    uint16_t      speed;           ///< vitesse du serpent

} snake_t;

/**
 * @typedef effect_t
 * @brief Effet et couleur du fruit
 */
typedef struct
{
    void (*effect)(snake_t* snake); ///< Fonction d’effet
    SDL_Color color;                ///< Couleur RGBA SDL3
} effect_t;

/**
 * @typedef fruit_t
 * @brief Structure fruit
 */
typedef struct fruit_s
{
    SDL_Color color;
    uint32_t  x; ///< Position horizontale
    uint32_t  y; ///< Position verticale
    void (*effect)(snake_t* snake);
} fruit_t;

/**
 * @typedef state_t
 * @brief État global du jeu
 */
typedef struct
{
    SDL_Window*   window;   ///< La fenêtre
    SDL_Renderer* renderer; ///< Le moteur de rendu, configuré
    snake_t*      snake;    ///< Pointeur sur la structure du serpent
    fruit_t*      fruit;    ///< Pointer sur la structure du fruit à manger
    bool          pause;    ///< Faut-il mettre le jeu en pause ?
} state_t;
#endif
