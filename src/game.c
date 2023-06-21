#include "../include/game.h"
#include "../include/stars.h"
#include "../include/collision.h"
#include "../include/explosion.h"

MLV_Image *load_image(const char *filename, int width, int height)
{
  MLV_Image *image = MLV_load_image(filename);
  if (image == NULL)
  {
    printf("Erreur lors du chargement des images %s\n", filename);
    exit(1);
  }

  MLV_resize_image(image, width, height);

  return image;
}

void init_game(Game *game)
{
  MLV_create_window("Shoot'em up", "Shoot'em up", WIDTH, HEIGHT);

  // Initialiser les variables du jeu
  game->last_bullet_time = 0;
  game->bullet_count = MAX_PLAYER_BULLETS;
  game->enemy_count = ENEMY_COUNT;
  game->explosion_count = MAX_EXPLOSIONS;
  game->time_elapsed = 0;
  game->last_update_time = MLV_get_time();

  // Charger les images nécessaires
  const char *player_image_path = "data/img/player.png";
  const char *enemy_image_path = "data/img/enemy.png";
  const char *player_bullet_image_path = "data/img/shoot.png";
  const char *enemy_bullet_image_path = "data/img/bullet.png";
  const char *heart_full_image_path = "data/img/heart_full.png";
  const char *heart_empty_image_path = "data/img/heart_empty.png";

  // Charger l'image du joueur
  game->player_sprite = load_image(player_image_path, PLAYER_WIDTH, PLAYER_HEIGHT);
  if (game->player_sprite == NULL)
  {
    printf("Erreur lors du chargement de l'image du joueur\n");
    exit(1);
  }

  // Charger l'image de l'ennemi
  game->enemy_sprite = load_image(enemy_image_path, ENEMY_WIDTH, ENEMY_HEIGHT);
  if (game->enemy_sprite == NULL)
  {
    printf("Erreur lors du chargement de l'image de l'ennemi\n");
    exit(1);
  }

  // Charger l'image de la balle du joueur
  game->player_bullet_sprite = load_image(player_bullet_image_path, BULLET_WIDTH, BULLET_HEIGHT);
  if (game->player_bullet_sprite == NULL)
  {
    printf("Erreur lors du chargement de l'image de la balle du joueur\n");
    exit(1);
  }

  // Charger l'image de la balle de l'ennemi
  game->enemy_bullet_sprite = load_image(enemy_bullet_image_path, BULLET_WIDTH, BULLET_HEIGHT);
  if (game->enemy_bullet_sprite == NULL)
  {
    printf("Erreur lors du chargement de l'image de la balle de l'ennemi\n");
    exit(1);
  }

  // Charger les images d'explosion
  char filename[30];
  for (int i = 0; i < NUM_EXPLOSION_IMAGES; i++)
  {
    sprintf(filename, "data/img/explosion%d.png", i);
    game->explosions[i].images[i] = load_image(filename, EXPLOSION_WIDTH, EXPLOSION_HEIGHT);
    if (game->explosions[i].images[i] == NULL)
    {
      printf("Erreur lors du chargement de l'image d'explosion %d\n", i);
      exit(1);
    }
  }

  // Charger les images des coeur du joueur
  game->heart_full = load_image(heart_full_image_path, HEART_WIDTH, HEART_HEIGHT);
  if (game->heart_full == NULL)
  {
    printf("Erreur lors du chargement de l'image du cœur plein\n");
    exit(1);
  }

  game->heart_empty = load_image(heart_empty_image_path, HEART_WIDTH, HEART_HEIGHT);
  if (game->heart_empty == NULL)
  {
    printf("Erreur lors du chargement de l'image du cœur vide\n");
    exit(1);
  }

  game->score = 0;
  game->time_elapsed = 0;
  game->hearts_remaining = 6;

  // Positionner le joueur
  game->player.x = WIDTH / 2;
  game->player.y = HEIGHT;
  game->player.dx = 7;
  game->player.dy = 7;
  game->player.move_up = false;
  game->player.move_down = false;
  game->player.move_left = false;
  game->player.move_right = false;
  game->player.width = PLAYER_WIDTH;
  game->player.height = PLAYER_HEIGHT;

  srand(time(NULL));

  int enemy_spacing = ENEMY_HEIGHT * 2;

  for (int i = 0; i < ENEMY_COUNT; i++)
  {
    game->enemies[i].active = 1;
    game->enemies[i].x = rand() % (WIDTH - game->enemies[i].width);
    game->enemies[i].y = -i * enemy_spacing;
    game->enemies[i].width = ENEMY_WIDTH;
    game->enemies[i].height = ENEMY_HEIGHT;
    game->last_enemy_bullet_time[i] = 0;

    // Générer une position x aléatoire en évitant que l'ennemi dépasse les limites de l'ecran
    int max_x = WIDTH - game->enemies[i].width;
    game->enemies[i].x = rand() % max_x;
  }

  for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
  {
    game->player_bullets[i].active = 0;
    game->player_bullets[i].x = 0;
    game->player_bullets[i].y = 0;
    game->player_bullets[i].width = BULLET_WIDTH;
    game->player_bullets[i].height = BULLET_HEIGHT;
  }

  for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
  {
    game->enemy_bullets[i].active = 0;
    game->enemy_bullets[i].x = 0;
    game->enemy_bullets[i].y = 0;
    game->enemy_bullets[i].width = BULLET_WIDTH;
    game->enemy_bullets[i].height = BULLET_HEIGHT;
    game->enemy_bullets[i].hit_player = false;
    game->enemy_bullets[i].hit_counter = 1;
  }

  for (int i = 0; i < MAX_EXPLOSIONS; i++)
  {
    explosion_init(&(game->explosions[i]), 0, 0);
    game->explosions[i].width = EXPLOSION_WIDTH;
    game->explosions[i].height = EXPLOSION_HEIGHT;
  }

  stars_init(&game->stars);
}

void draw_game(const Game *game)
{
  // dessiner les étoiles
  stars_draw(&game->stars);

  if (game->player_sprite != NULL)
  {
    MLV_draw_image(game->player_sprite, game->player.x, game->player.y);
  }

  for (int i = 0; i < game->enemy_count; i++)
  {
    if (game->enemies[i].active)
    {
      MLV_draw_image(game->enemy_sprite, game->enemies[i].x,
                     game->enemies[i].y);
    }
  }

  for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
  {
    if (game->player_bullets[i].active)
    {
      MLV_draw_image(game->player_bullet_sprite, game->player_bullets[i].x,
                     game->player_bullets[i].y);
    }
  }

  for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
  {
    if (game->enemy_bullets[i].active)
    {
      MLV_draw_image(game->enemy_bullet_sprite, game->enemy_bullets[i].x,
                     game->enemy_bullets[i].y);
    }
  }

  for (int i = 0; i < game->explosion_count; i++)
  {
    if (game->explosions[i].active)
    {
      explosion_draw(&(game->explosions[i]));
    }
  }

  // Dessiner le score
  char score_text[20];
  sprintf(score_text, "Score: %d", game->score);
  MLV_draw_text(10, 10, score_text, MLV_COLOR_WHITE);

  // Dessiner le temps écoulé
  MLV_draw_text(10, 30, "Time: %d s", MLV_COLOR_WHITE, game->time_elapsed / 1000);

  // Dessiner les cœurs
  int heart_x = WIDTH - 10 - HEART_WIDTH;
  int heart_y = 10;

  for (int i = 0; i < game->hearts_remaining; i++)
  {
    MLV_draw_image(game->heart_full, heart_x, heart_y);
    heart_x -= HEART_WIDTH + 5;
  }

  for (int i = game->hearts_remaining; i < 6; i++)
  {
    MLV_draw_image(game->heart_empty, heart_x, heart_y);
    heart_x -= HEART_WIDTH + 5;
  }

  // Actualise l'écran
  MLV_actualise_window();
}

void update_game(Game *game)
{
  bool quit = false;
  handle_input_game(game, &quit);
  player_update_position(&(game->player));
  Bullet_list_update(game->player_bullets, MAX_PLAYER_BULLETS);
  Bullet_list_update(game->enemy_bullets, MAX_ENEMY_BULLETS);
  for (int i = 0; i < game->enemy_count; i++)
  {
    if (game->enemies[i].active)
    {
      game->enemies[i].y += 3;

      if (game->enemies[i].y > HEIGHT)
      {
        game->enemies[i].y = -(game->enemies[i].height);
        game->enemies[i].active = 1;
      }

      unsigned long current_time = MLV_get_time();
      unsigned long enemy_bullet_cooldown = 200;

      game->time_elapsed += current_time - game->last_update_time;
      game->last_update_time = current_time;

      if (current_time - game->last_enemy_bullet_time[i] > enemy_bullet_cooldown)
      {
        int bullet_index = Bullet_list_get_free_index(game->enemy_bullets, MAX_ENEMY_BULLETS);
        if (bullet_index != -1)
        {
          Bullet *bullet = &(game->enemy_bullets[bullet_index]);
          bullet->active = 1;
          bullet->x = game->enemies[i].x + game->enemies[i].width / 2 - bullet->width / 2;
          bullet->y = game->enemies[i].y + game->enemies[i].height;

          float dx = game->player.x - bullet->x;
          float dy = game->player.y - bullet->y;

          // Calculez l'angle en utilisant atan2 qui gère le cas où dx est égal à zéro
          float angle = atan2(dy, dx);

          float speed = 7.0;
          // Utilisez l'angle pour déterminer la vitesse de la balle
          bullet->dx = speed * cos(angle);
          bullet->dy = speed * sin(angle);

          game->last_enemy_bullet_time[i] = current_time;
        }
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
  }

  for (int i = 0; i < game->explosion_count; i++)
  {
    if (game->explosions[i].active)
    {
      explosion_update(&(game->explosions[i]));
    }
  }

  game_handle_collision(game);
  stars_update(&(game->stars));
}

void handle_input_game(Game *game, bool *quit)
{
  MLV_Keyboard_button key;
  MLV_Mouse_button mouse_button;
  MLV_Button_state state = MLV_RELEASED;

  unsigned long current_time = MLV_get_time();
  unsigned long bullet_cooldown = 200;

  MLV_get_event(&key, NULL, NULL, NULL, NULL, NULL, NULL, &mouse_button, &state);

  if (key == MLV_KEYBOARD_ESCAPE)
  {
    *quit = true;
  }

  switch (key)
  {
  case MLV_KEYBOARD_UP:
    game->player.move_up = (state == MLV_PRESSED);
    break;
  case MLV_KEYBOARD_DOWN:
    game->player.move_down = (state == MLV_PRESSED);
    break;
  case MLV_KEYBOARD_LEFT:
    game->player.move_left = (state == MLV_PRESSED);
    break;
  case MLV_KEYBOARD_RIGHT:
    game->player.move_right = (state == MLV_PRESSED);
    break;
  default:
    break;
  }

  for (int i = 0; i < game->enemy_count; i++)
  {
    if (game->enemies[i].active && game->enemies[i].y > game->player.y)
    {
      game->can_enemy_shoot = false;
      break;
    }
  }

  if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED &&
      (current_time - game->last_bullet_time > bullet_cooldown))
  {
    int bullet_index1 = Bullet_list_get_free_index(game->player_bullets, MAX_PLAYER_BULLETS);
    int bullet_index2 = Bullet_list_get_free_index(game->player_bullets, MAX_PLAYER_BULLETS);
    if (bullet_index1 != -1 && bullet_index2 != -1)
    {
      Bullet *bullet1 = &(game->player_bullets[bullet_index1]);
      Bullet *bullet2 = &(game->player_bullets[bullet_index2]);
      bullet1->active = 1;
      bullet1->width = BULLET_WIDTH;
      bullet1->height = BULLET_HEIGHT;
      bullet1->x = game->player.x + game->player.width / 2 - bullet1->width / 2;
      bullet1->y = game->player.y;
      bullet1->dy = -5;

      bullet2->active = 1;
      bullet2->width = BULLET_WIDTH;
      bullet2->height = BULLET_HEIGHT;
      bullet2->x = game->player.x + game->player.width / 2 - bullet2->width / 2;
      bullet2->y = game->player.y;
      bullet2->dy = -5;

      bullet1->dx = 0;
      bullet2->dx = 0;

      game->last_bullet_time = current_time;
    }
  }
}

void end_game(Game *game)
{
  printf("Game Over\n");
  clean_game(game); // Libérer les ressources utilisées par le jeu
  exit(0);
}

void clean_game(Game *game)
{
  MLV_free_sound(game->game_sound);
  MLV_free_image(game->player_sprite);
  MLV_free_image(game->enemy_sprite);
  MLV_free_image(game->player_bullet_sprite);
  MLV_free_image(game->enemy_bullet_sprite);
  explosion_cleanup(game->explosions);
  stars_cleanup(&game->stars);
}