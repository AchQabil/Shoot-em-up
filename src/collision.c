#include "../include/collision.h"
#include "../include/explosion.h"

#include <stdbool.h>

int find_inactive_explosion(Game *game)
{
  for (int i = 0; i < game->explosion_count; i++)
  {
    if (!game->explosions[i].active)
    {
      return i;
    }
  }
  return -1; // Retourne -1 si aucune explosion inactif n'est trouvé
}

void game_handle_collision(Game *game)
{
  // Collision entre joueur et ennemis
  for (int i = 0; i < game->enemy_count; i++)
  {
    if (game->enemies[i].active &&
        rectangles_overlap(game->player.x, game->player.y, game->player.width,
                           game->player.height, game->enemies[i].x,
                           game->enemies[i].y, game->enemies[i].width,
                           game->enemies[i].height))
    {
      if (game->enemies[i].y >= 0)
      {                                  // Vérifier si l'ennemi est visible
        game->enemies[i].active = false; // Supprimer l'ennemi

        // Ajouter explosion
        int explosion_index = find_inactive_explosion(game);
        if (explosion_index != -1)
        {
          explosion_activate(&game->explosions[explosion_index], game->enemies[i].x, game->enemies[i].y);
        }

        // Incrémenter le score
        game->score += 10;
      }
    }
  }

  // Vérifie si une balle ennemie touche le joueur
  for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
  {
    if (game->enemy_bullets[i].active &&
        rectangles_overlap(game->player.x, game->player.y, game->player.width, game->player.height,
                           game->enemy_bullets[i].x, game->enemy_bullets[i].y, game->enemy_bullets[i].width, game->enemy_bullets[i].height))
    {
      // Si le joueur est touché par une balle ennemie, décrémenter le compteur de la balle
      game->enemy_bullets[i].hit_counter--;

      // Si le compteur de la balle atteint 0, la balle devient inactive
      if (game->enemy_bullets[i].hit_counter <= 0)
      {
        game->enemy_bullets[i].active = false;
      }

      // Décrémenter les coeurs restants du joueur
      game->hearts_remaining--;

      // Si le joueur a perdu tous ses coeurs, terminer le jeu
      if (game->hearts_remaining <= 0)
      {
        end_game(game);
        return;
      }
    }

    // Collision entre balles du joueur et ennemis
    for (int i = 0; i < game->bullet_count; i++)
    {
      for (int j = 0; j < game->enemy_count; j++)
      {
        if (game->player_bullets[i].active && game->enemies[j].active &&
            rectangles_overlap(
                game->player_bullets[i].x, game->player_bullets[i].y,
                game->player_bullets[i].width, game->player_bullets[i].height,
                game->enemies[j].x, game->enemies[j].y, game->enemies[j].width,
                game->enemies[j].height))
        {
          game->player_bullets[i].active = false; // Supprimer la balle
          if (game->enemies[j].y >= 0)
          {                                  // Vérifier si l'ennemi est visible
            game->enemies[j].active = false; // Supprimer l'ennemi

            // Ajouter explosion
            int explosion_index = find_inactive_explosion(game);
            if (explosion_index != -1)
            {
              explosion_activate(&game->explosions[explosion_index], game->enemies[j].x, game->enemies[j].y);
            }

            // Incrémenter le score
            game->score += 10;
          }
        }
      }
    }
  }
}

bool is_colliding(Entity *entity1, Entity *entity2)
{
  if (entity1->x < entity2->x + entity2->width &&
      entity1->x + entity1->width > entity2->x &&
      entity1->y < entity2->y + entity2->height &&
      entity1->height + entity1->y > entity2->y)
  {
    return true;
  }
  return false;
}

bool rectangles_overlap(int x1, int y1, int width1, int height1, int x2, int y2,
                        int width2, int height2)
{
  if (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 &&
      y1 + height1 > y2)
  {
    return true;
  }
  return false;
}