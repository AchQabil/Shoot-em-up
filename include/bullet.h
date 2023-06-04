#ifndef BULLET_H
#define BULLET_H

#include "MLV/MLV_all.h"

/**
 * @struct Bullet
 * @brief Cette structure représente un projectile dans le jeu.
 */
typedef struct {
  int x;  /* Coordonnée x du projectile, indiquant sa position horizontale sur l'écran */
  int y;  /* Coordonnée y du projectile, indiquant sa position verticale sur l'écran */
  int dx; /* La variation de la coordonnée x du projectile à chaque mise à jour (frame) */
  int dy; /* La variation de la coordonnée y du projectile à chaque mise à jour (frame) */
  int width;        /* La largeur du projectile */
  int height;       /* La hauteur du projectile */
  int active;       /* Un indicateur booléen pour savoir si le projectile est actif (1) ou non (0) */
  MLV_Image *image; /* L'image du projectile qui sera affichée sur l'écran */
} Bullet;

/**
 * @brief Met à jour la position du projectile en modifiant ses coordonnées x et y.
 * @param bullet Un pointeur vers le projectile dont on doit mettre à jour la position.
 */
void Bullet_update_position(Bullet *bullet);

/**
 * @brief Dessine le projectile sur l'écran à sa position actuelle.
 * @param bullet Un pointeur vers le projectile à dessiner.
 */
void Bullet_draw(const Bullet *bullet);

/**
 * @brief Met à jour les positions de tous les projectiles dans le tableau.
 * @param bullets Un pointeur vers le tableau de projectiles à mettre à jour.
 * @param count Le nombre total de projectiles dans le tableau.
 */
void Bullet_list_update(Bullet *bullets, int count);

/**
 * @brief Dessine tous les projectiles du tableau sur l'écran à leurs positions actuelles.
 * @param bullets Un pointeur vers le tableau de projectiles à dessiner.
 * @param count Le nombre total de projectiles dans le tableau.
 */
void Bullet_list_draw(const Bullet *bullets, int count);

/**
 * @brief Trouve un projectile inactif dans le tableau.
 * @param bullets Un pointeur vers le tableau de projectiles.
 * @param count Le nombre total de projectiles dans le tableau.
 * @return L'index du premier projectile inactif trouvé dans le tableau. Si aucun projectile inactif n'est trouvé, la fonction retourne -1.
 */
int Bullet_list_get_free_index(const Bullet *bullets, int count);

#endif
