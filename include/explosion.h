#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "MLV/MLV_all.h"
#include <stdbool.h>
#include <stdlib.h>

#define NUM_EXPLOSION_IMAGES 8
#define EXPLOSION_DURATION 1000 // Durée de l'explosion en millisecondes.
#define EXPLOSION_WIDTH 100     // Largeur de l'explosion.
#define EXPLOSION_HEIGHT 100    // Hauteur de l'explosion.

typedef struct
{
    int x;                                   // Position horizontale de l'explosion.
    int y;                                   // Position verticale de l'explosion.
    bool active;                             // Indique si l'explosion est active ou non.
    unsigned long start_time;                // Moment de l'activation de l'explosion.
    int current_image;                       // Index de l'image actuelle de l'explosion.
    MLV_Image *images[NUM_EXPLOSION_IMAGES]; // Tableau d'images de l'explosion.
    int width;                               // Largeur de l'explosion.
    int height;                              // Hauteur de l'explosion.
} Explosion;

/**
 * @brief Initialise une explosion à une position donnée.
 * @param explosion L'explosion à initialiser.
 * @param x La position horizontale de l'explosion.
 * @param y La position verticale de l'explosion.
 */
void explosion_init(Explosion *explosion, int x, int y);

/**
 * @brief Active une explosion à une position donnée.
 * @param explosion L'explosion à activer.
 * @param x La position horizontale de l'explosion.
 * @param y La position verticale de l'explosion.
 */
void explosion_activate(Explosion *explosion, int x, int y);

/**
 * @brief Dessine l'explosion à sa position actuelle en utilisant l'image correspondante.
 * @param explosion L'explosion à dessiner.
 */
void explosion_draw(const Explosion *explosion);

/**
 * @brief Met à jour l'état de l'explosion.
 * @param explosion L'explosion à mettre à jour.
 */
void explosion_update(Explosion *explosion);

/**
 * @brief Nettoie les ressources utilisées par les explosions.
 * @param explosions Le tableau d'explosions.
 */
void explosion_cleanup(Explosion *explosions);
#endif
