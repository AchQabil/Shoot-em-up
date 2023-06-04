#ifndef COLLISION_H
#define COLLISION_H

#include "game.h"
#include <stdbool.h>

/**
 * @brief Gère les collisions entre les entités du jeu.
 * @param game Un pointeur vers l'instance du jeu à traiter.
 */
void game_handle_collision(Game *game);

/**
 * @brief Vérifie si deux rectangles se chevauchent.
 * @param x1, y1 Les coordonnées du coin supérieur gauche du premier rectangle.
 * @param width1, height1 La largeur et la hauteur du premier rectangle.
 * @param x2, y2 Les coordonnées du coin supérieur gauche du deuxième rectangle.
 * @param width2, height2 La largeur et la hauteur du deuxième rectangle.
 * @return Retourne true si les rectangles se chevauchent, et false sinon.
 */
bool rectangles_overlap(int x1, int y1, int width1, int height1, int x2, int y2,
                        int width2, int height2);

#endif
