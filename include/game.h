#ifndef GAME_H
#define GAME_H

#include "MLV/MLV_all.h"
#include "bullet.h"
#include "enemy.h"
#include "graphics.h"
#include "player.h"
#include "stars.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 600             // Largeur de l'écran de jeu.
#define HEIGHT 800            // Hauteur de l'écran de jeu.
#define PLAYER_WIDTH 60       // Largeur du joueur.
#define PLAYER_HEIGHT 70      // Hauteur du joueur.
#define ENEMY_WIDTH 60        // Largeur de l'ennemi.
#define ENEMY_HEIGHT 70       // Hauteur de l'ennemi.
#define BULLET_WIDTH 5        // Largeur du projectile.
#define BULLET_HEIGHT 30      // Hauteur du projectile.
#define STAR_WIDTH 10         // Hauteur des étoiles.
#define STAR_HEIGHT 10        // Largeur des étoiles.
#define MAX_ENEMY_BULLETS 20  // Nombre maximum de projectiles de l'ennemi.
#define MAX_PLAYER_BULLETS 30 // Nombre maximum de projectiles du joueur.
#define ENEMY_COUNT 8         // Nombre d'ennemis dans le jeu.

/**
 * @brief Structure de données pour représenter le jeu.
 */
typedef struct {
  Player player;                             // Le joueur.
  Stars stars;                               // Les étoiles.

  Enemy enemies[ENEMY_COUNT];                // Tableau d'ennemis.
  int enemy_count;                           // Nombre d'ennemis.
  
  Bullet enemy_bullets[MAX_ENEMY_BULLETS];   // Tableau de projectiles de l'ennemi.
  Bullet player_bullets[MAX_PLAYER_BULLETS]; // Tableau de projectiles du joueur.
  int bullet_count;                          // Nombre de projectiles.
  
  MLV_Image *player_sprite;                  // Sprite du joueur.
  MLV_Image *enemy_sprite;                   // Sprite des ennemis.
  MLV_Image *player_bullet_sprite;           // Sprite du projectile du joueur.
  MLV_Image *enemy_bullet_sprite;            // Sprite du projectile de l'ennemi.
  
  unsigned long last_bullet_time;            // Dernière fois qu'un projectile a été tiré.
  unsigned long last_enemy_bullet_time[ENEMY_COUNT]; // Dernière fois qu'un projectile ennemi a été tiré pour chaque ennemi.
  
  bool can_enemy_shoot;                      // Indicateur si l'ennemi peut tirer.
} Game;


/**
 * @brief Initialise le jeu.
 * @param game Un pointeur vers l'instance du jeu à initialiser.
 */
void init_game(Game *game);


/**
 * @brief Dessine les éléments du jeu.
 * @param game Un pointeur vers l'instance du jeu à dessiner.
 */
void draw_game(const Game *game);


/**
 * @brief Met à jour l'état du jeu.
 * @param game Un pointeur vers l'instance du jeu à mettre à jour.
 */
void update_game(Game *game);


/**
 * @brief Gère les entrées des utilisateurs.
 * @param game Un pointeur vers l'instance du jeu où gérer les entrées.
 * @param quit Un pointeur vers une variable booléenne pour indiquer si le joueur souhaite quitter.
 */
void handle_input_game(Game *game, bool *quit);


/**
 * @brief Nettoie le jeu à la fin de la partie.
 * @param game Un pointeur vers l'instance du jeu à nettoyer.
 */
void clean_game(Game *game);

#endif
