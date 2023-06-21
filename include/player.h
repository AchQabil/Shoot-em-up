#ifndef PLAYER_H
#define PLAYER_H

#include "MLV/MLV_all.h"
#include <stdbool.h>

/**
 * @brief Structure de données pour représenter le joueur.
 * @field x          Position horizontale du joueur.
 * @field y          Position verticale du joueur.
 * @field dx         Variation horizontale de la position du joueur à chaque frame.
 * @field dy         Variation verticale de la position du joueur à chaque frame.
 * @field width      Largeur du joueur.
 * @field height     Hauteur du joueur.
 * @field image      Image représentant le joueur.
 * @field move_up    Indicateur du mouvement vers le haut du joueur.
 * @field move_down  Indicateur du mouvement vers le bas du joueur.
 * @field move_left  Indicateur du mouvement vers la gauche du joueur.
 * @field move_right Indicateur du mouvement vers la droite du joueur.
 * @field active     Indicateur de l'activité du joueur (true ou false).
 */
typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    int width;
    int height;
    MLV_Image *image;
    bool move_up;
    bool move_down;
    bool move_left;
    bool move_right;
    bool active;
} Player;

/**
 * @brief Met à jour la position du joueur en fonction des variations dx et dy.
 * @param player Pointeur vers une structure Player représentant le joueur.
 */
void player_update_position(Player *player);


#endif
