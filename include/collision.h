#ifndef COLLISION_H
#define COLLISION_H

#include "game.h"
#include <MLV/MLV_all.h>
#include <stdbool.h>

/**
 * @struct Entity
 * @brief Représente une entité générique dans le jeu, pouvant être un joueur, un ennemi ou un projectile.
 */
typedef struct
{
    int x;       /* Coordonnée x de l'entité, indiquant sa position horizontale sur l'écran */
    int y;       /* Coordonnée y de l'entité, indiquant sa position verticale sur l'écran */
    int width;   /* La largeur de l'entité */
    int height;  /* La hauteur de l'entité */
    bool active; /* Un indicateur booléen pour savoir si l'entité est active (true) ou non (false) */
} Entity;

/**
 * @brief Gère les collisions entre les entités du jeu.
 * @param game Un pointeur vers l'instance du jeu à traiter.
 */
void game_handle_collision(Game *game);

/**
 * @brief Vérifie si deux entités se chevauchent.
 * @param entity1 Un pointeur vers la première entité.
 * @param entity2 Un pointeur vers la seconde entité.
 * @return Retourne true si les entités se chevauchent, et false sinon.
 */
bool is_colliding(Entity *entity1, Entity *entity2);

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

/**
 * @brief Cherche un index d'explosion inactif.
 * @param game Un pointeur vers l'instance du jeu.
 * @return L'index de la première explosion inactive trouvée. Si aucune explosion inactive n'est trouvée, la fonction retourne -1.
 */
int find_inactive_explosion(Game *game);

#endif