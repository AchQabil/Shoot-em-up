#include "../include/collision.h"

#include <stdbool.h>

void game_handle_collision(Game *game) {
  // Collision entre joueur et ennemis
  for (int i = 0; i < game->enemy_count; i++) {
    if (game->enemies[i].active &&
        rectangles_overlap(game->player.x, game->player.y, game->player.width,
                           game->player.height, game->enemies[i].x,
                           game->enemies[i].y, game->enemies[i].width,
                           game->enemies[i].height)) {
      if (game->enemies[i].y >= 0) { // Vérifier si l'ennemi est visible
        game->enemies[i].active = 0; // Supprimer l'ennemi
      }
    }
  }

  // Collision entre balles du joueur et ennemis
  for (int i = 0; i < game->bullet_count; i++) {
    for (int j = 0; j < game->enemy_count; j++) {
      if (game->player_bullets[i].active && game->enemies[j].active &&
          rectangles_overlap(
              game->player_bullets[i].x, game->player_bullets[i].y,
              game->player_bullets[i].width, game->player_bullets[i].height,
              game->enemies[j].x, game->enemies[j].y, game->enemies[j].width,
              game->enemies[j].height)) {
        game->player_bullets[i].active = 0; // Supprimer la balle
        if (game->enemies[j].y >= 0) {      // Vérifier si l'ennemi est visible
          game->enemies[j].active = 0;      // Supprimer l'ennemi

          // Régénérer l'ennemi
          int enemy_spacing = (8 * HEIGHT) / game->enemy_count;
          game->enemies[j].x = rand() % (WIDTH - game->enemies[j].width);
          game->enemies[j].y = -((j + 1) * enemy_spacing);
          game->enemies[j].active = 1;
        }
      }
    }
  }
}

bool rectangles_overlap(int x1, int y1, int width1, int height1, int x2, int y2,
                        int width2, int height2) {
  if (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 &&
      y1 + height1 > y2) {
    return true;
  }
  return false;
}