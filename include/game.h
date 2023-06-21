#ifndef GAME_H
#define GAME_H

#include "MLV/MLV_all.h"
#include "bullet.h"
#include "player.h"
#include "stars.h"
#include "explosion.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 600           // Largeur de l'écran de jeu.
#define HEIGHT 800          // Hauteur de l'écran de jeu.
#define PLAYER_WIDTH 60     // Largeur du joueur.
#define PLAYER_HEIGHT 70    // Hauteur du joueur.
#define ENEMY_WIDTH 60      // Largeur de l'ennemi.
#define ENEMY_HEIGHT 70     // Hauteur de l'ennemi.
#define BULLET_WIDTH 5      // Largeur du projectile.
#define BULLET_HEIGHT 30    // Hauteur du projectile.
#define STAR_WIDTH 10       // Hauteur des étoiles.
#define STAR_HEIGHT 10      // Largeur des étoiles.
#define EXPLOSION_FRAMES 10 // Nombre de cadres d'explosion

#define MAX_ENEMY_BULLETS 10  // Nombre maximum de projectiles de l'ennemi.
#define MAX_PLAYER_BULLETS 30 // Nombre maximum de projectiles du joueur.
#define ENEMY_COUNT 100       // Nombre d'ennemis dans le jeu.
#define MAX_EXPLOSIONS 10     // Nombre maximum d'explosions
#define HEART_WIDTH 20
#define HEART_HEIGHT 20

/**
 * @brief Structure de données pour représenter un ennemi.
 */
typedef struct
{
  int x;            // Position horizontale de l'ennemi.
  int y;            // Position verticale de l'ennemi.
  int dx;           // Variation horizontale de la position de l'ennemi à chaque frame.
  int dy;           // Variation verticale de la position de l'ennemi à chaque frame.
  int width;        // Largeur de l'ennemi.
  int height;       // Hauteur de l'ennemi.
  bool active;      // Indique si l'ennemi est actif ou non.
  MLV_Image *image; // Image représentant l'ennemi.
} Enemy;

/**
 * @brief Structure de données pour représenter le jeu.
 */
typedef struct
{
  Player player;                                           // Le joueur.
  Stars stars;                                             // Les étoiles.

  Enemy enemies[ENEMY_COUNT];                              // Tableau d'ennemis.
  int enemy_count;                                         // Nombre d'ennemis.

  Bullet enemy_bullets[MAX_ENEMY_BULLETS];                 // Tableau de projectiles de l'ennemi.
  Bullet player_bullets[MAX_PLAYER_BULLETS];               // Tableau de projectiles du joueur.
  int bullet_count;                                        // Nombre de projectiles.

  Explosion explosions[MAX_EXPLOSIONS];                    // Tableau d'explosions.
  int explosion_count;                                     // Nombre d'explosions.

  MLV_Image *player_sprite;                                // Sprite du joueur.
  MLV_Image *enemy_sprite;                                 // Sprite des ennemis.
  MLV_Image *player_bullet_sprite;                         // Sprite du projectile du joueur.
  MLV_Image *enemy_bullet_sprite;                          // Sprite du projectile de l'ennemi.
  MLV_Image *explosion_sprites[NUM_EXPLOSION_IMAGES];      // Tableau d'images d'explosion.

  unsigned long last_bullet_time;                          // Dernière fois qu'un projectile a été tiré.
  unsigned long last_enemy_bullet_time[ENEMY_COUNT];       // Dernière fois qu'un projectile ennemi a été tiré pour chaque ennemi.

  bool can_enemy_shoot;

  int score;                                               // Score du joueur.
  int time_elapsed;                                        // Temps écoulé depuis le début du jeu en secondes.
  int hearts_remaining;                                    // Nombre de cœurs restants pour le joueur.
  MLV_Image *heart_full;                                   // Image du cœur plein pour afficher la vie du joueur.
  MLV_Image *heart_empty;                                  // Image du cœur vide pour afficher la vie perdue du joueur.
  unsigned long last_update_time;                          // Dernière fois que le jeu a été mis à jour.
  MLV_Sound *game_sound;                                   // Son du jeu.
} Game;


MLV_Image *load_image(const char *filename, int width, int height);

/**
 * @brief Initialise le jeu.
 * @param game Un pointeur vers l'instance du jeu à initialiser.
 */
void init_game(Game *game);

void load_images(Game *game);

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
 * @brief Termine le jeu et affiche le score final.
 * @param game Un pointeur vers l'instance du jeu à terminer.
 */
void end_game(Game *game);

/**
 * @brief Nettoie le jeu à la fin de la partie.
 * @param game Un pointeur vers l'instance du jeu à nettoyer.
 */
void clean_game(Game *game);

#endif