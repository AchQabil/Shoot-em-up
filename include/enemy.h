#ifndef ENEMY_H
#define ENEMY_H

#include "MLV/MLV_all.h"

/**
 * @brief Structure de données pour représenter un ennemi.
 */
typedef struct {
  int x;         // Position horizontale de l'ennemi.
  int y;         // Position verticale de l'ennemi.
  int dx;        // Variation horizontale de la position de l'ennemi à chaque frame.
  int dy;        // Variation verticale de la position de l'ennemi à chaque frame.
  int width;     // Largeur de l'ennemi.
  int height;    // Hauteur de l'ennemi.
  int active;    // Indique si l'ennemi est actif ou non.
  MLV_Image *image; // Image représentant l'ennemi.
} Enemy;

/**
 * @brief Initialise un ennemi avec des valeurs spécifiées.
 * @param enemy L'ennemi à initialiser.
 * @param x, y Les coordonnées de départ de l'ennemi.
 * @param dx, dy Les variations initiales de position de l'ennemi.
 * @param width, height Les dimensions de l'ennemi.
 * @param image L'image représentant l'ennemi.
 */
void enemy_init(Enemy *enemy, int x, int y, int dx, int dy, int width,
                int height, MLV_Image *image);

/**
 * @brief Active un ennemi.
 * @param enemy L'ennemi à activer.
 */
void enemy_activate(Enemy *enemy);

/**
 * @brief Désactive un ennemi.
 * @param enemy L'ennemi à désactiver.
 */
void enemy_deactivate(Enemy *enemy);

/**
 * @brief Définit la vitesse d'un ennemi.
 * @param enemy L'ennemi dont on veut définir la vitesse.
 * @param dx, dy Les nouvelles valeurs de variation de position de l'ennemi.
 */
void enemy_set_speed(Enemy *enemy, int dx, int dy);

/**
 * @brief Met à jour la position de l'ennemi en fonction des variations dx et dy.
 * @param enemy L'ennemi dont on veut mettre à jour la position.
 */
void enemy_update_position(Enemy *enemy);

/**
 * @brief Dessine l'ennemi à sa position actuelle en utilisant le sprite spécifié.
 * @param enemy L'ennemi à dessiner.
 * @param sprite Le sprite à utiliser pour dessiner l'ennemi.
 */
void enemy_draw(const Enemy *enemy, const MLV_Image *sprite);

/**
 * @brief Met à jour la position de chaque ennemi dans la liste en appelant la fonction enemy_update_position.
 * @param enemies Un tableau d'ennemis.
 * @param count Le nombre d'ennemis dans le tableau.
 */
void enemy_list_update(Enemy *enemies, int count);

/**
 * @brief Dessine chaque ennemi de la liste à sa position actuelle en utilisant le sprite spécifié.
 * @param enemies Un tableau d'ennemis.
 * @param sprite Le sprite à utiliser pour dessiner les ennemis.
 * @param count Le nombre d'ennemis dans le tableau.
 */
void enemy_list_draw(const Enemy *enemies, const MLV_Image *sprite, int count);

/**
 * @brief Renvoie 1 si la liste des ennemis est vide, 0 sinon.
 * @param enemies Un tableau d'ennemis.
 * @param count Le nombre d'ennemis dans le tableau.
 * @return 1 si le tableau est vide, 0 sinon.
 */
int enemy_list_is_empty(const Enemy *enemies, int count);

#endif
