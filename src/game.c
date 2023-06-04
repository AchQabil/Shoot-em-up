#include "../include/game.h"
#include "../include/stars.h"

void init_game(Game *game)
{
  graphics_init(WIDTH, HEIGHT, "Shoot'em up");
  
   // Initialiser les variables du jeu
  game->last_bullet_time = 0;
  game->bullet_count = MAX_PLAYER_BULLETS;
  game->enemy_count = ENEMY_COUNT;
  
  // Charger les images nécessaires

  /* Image player */
  game->player_sprite = MLV_load_image("data/img/player.png");
  if (game->player_sprite == NULL) {
    printf("Erreur lors du chargement de l'image du joueur\n");
    exit(1);
  }
  MLV_resize_image(game->player_sprite, PLAYER_WIDTH, PLAYER_HEIGHT);
  
  /* Image enemy */
  game->enemy_sprite = MLV_load_image("data/img/enemy.png");
  if (game->enemy_sprite == NULL) {
    printf("Erreur lors du chargement de l'image de l'ennemi\n");
    exit(1);
  }
  MLV_resize_image(game->enemy_sprite, ENEMY_WIDTH, ENEMY_HEIGHT);

  /* Image bullet player */
  game->player_bullet_sprite = MLV_load_image("data/img/shoot.png");
  if (game->player_bullet_sprite == NULL) {
    printf("Erreur lors du chargement de l'image de la balle du joueur\n");
    exit(1);
  }
  MLV_resize_image(game->player_bullet_sprite, BULLET_WIDTH, BULLET_HEIGHT);

  /* Image bullet enemy */
  game->enemy_bullet_sprite = MLV_load_image("data/img/bullet.png");
  if (game->enemy_bullet_sprite == NULL) {
    printf("Erreur lors du chargement de l'image de la balle de l'ennemi\n");
    exit(1);
  }
  MLV_resize_image(game->enemy_bullet_sprite, BULLET_WIDTH, BULLET_HEIGHT);
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

  for (int i = 0; i < ENEMY_COUNT; i++) {
    game->enemies[i].active = 1;
    game->enemies[i].x = rand() % (WIDTH - game->enemies[i].width);
    game->enemies[i].y = -i * enemy_spacing;
    game->enemies[i].width = ENEMY_WIDTH;
    game->enemies[i].height = ENEMY_HEIGHT;
    game->last_enemy_bullet_time[i] = 0;
  }

  for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
    game->player_bullets[i].active = 0;
    game->player_bullets[i].x = 0;
    game->player_bullets[i].y = 0;
    game->player_bullets[i].width = BULLET_WIDTH;
    game->player_bullets[i].height = BULLET_HEIGHT;
  }

  for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
    game->enemy_bullets[i].active = 0;
    game->enemy_bullets[i].x = 0;
    game->enemy_bullets[i].y = 0;
    game->enemy_bullets[i].width = BULLET_WIDTH;
    game->enemy_bullets[i].height = BULLET_HEIGHT;
  }

  stars_init(&game->stars);
}

void draw_game(const Game *game)
{
  graphics_clear();

  // dessiner les étoiles
  stars_draw(&game->stars);

   if (game->player_sprite != NULL) {
    MLV_draw_image(game->player_sprite, game->player.x, game->player.y);
  }

  for (int i = 0; i < game->enemy_count; i++) {
    if (game->enemies[i].active) {
      MLV_draw_image(game->enemy_sprite, game->enemies[i].x,
                     game->enemies[i].y);
    }
  }

  for (int i = 0; i < MAX_PLAYER_BULLETS; i++) {
    if (game->player_bullets[i].active) {
      MLV_draw_image(game->player_bullet_sprite, game->player_bullets[i].x,
                     game->player_bullets[i].y);
    }
  }

  for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
    if (game->enemy_bullets[i].active) {
      MLV_draw_image(game->enemy_bullet_sprite, game->enemy_bullets[i].x,
                     game->enemy_bullets[i].y);
    }
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

  for (int i = 0; i < game->enemy_count; i++) {
    if (game->enemies[i].active) {
      game->enemies[i].y += 3;

      if (game->enemies[i].y > HEIGHT) {
        game->enemies[i].y = -(game->enemies[i].height);
        game->enemies[i].x = rand() % (WIDTH - game->enemies[i].width);
        game->enemies[i].active = 1;
      }

      unsigned long current_time = MLV_get_time();
      unsigned long enemy_bullet_cooldown = 200;

      if (current_time - game->last_enemy_bullet_time[i] >
          enemy_bullet_cooldown) {
        int bullet_index =
            Bullet_list_get_free_index(game->enemy_bullets, MAX_ENEMY_BULLETS);
        if (bullet_index != -1) {
          Bullet *bullet = &(game->enemy_bullets[bullet_index]);
          bullet->active = 1;
          bullet->x = game->enemies[i].x + game->enemies[i].width / 2 -
                      bullet->width / 2;
          bullet->y = game->enemies[i].y + game->enemies[i].height;

          float dx = game->player.x - bullet->x;
          float dy = game->player.y - bullet->y;

          float magnitude = sqrt(dx * dx + dy * dy);
          dx /= magnitude;
          dy /= magnitude;

          float speed = 7.0;
          bullet->dx = speed * dx;
          bullet->dy = speed * dy;

          game->last_enemy_bullet_time[i] = current_time;
        }
      }
    }
  }

  game_handle_collision(game);
  stars_update(&game->stars);
}

void handle_input_game(Game *game, bool *quit){
  MLV_Keyboard_button key;
  MLV_Mouse_button mouse_button;
  MLV_Button_state state = MLV_RELEASED;

  unsigned long current_time = MLV_get_time();
  unsigned long bullet_cooldown = 200;

  MLV_get_event(&key, NULL, NULL, NULL, NULL, NULL, NULL, &mouse_button,
                &state);

  if (key == MLV_KEYBOARD_ESCAPE) {
    *quit = true;
  }

  switch (key) {
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

  for (int i = 0; i < game->enemy_count; i++) {
    if (game->enemies[i].active && game->enemies[i].y > game->player.y) {
      game->can_enemy_shoot = false;
      break;
    }
  }

  if (MLV_get_keyboard_state(MLV_KEYBOARD_SPACE) == MLV_PRESSED &&
      (current_time - game->last_bullet_time > bullet_cooldown)) {
    int bullet_index1 =
        Bullet_list_get_free_index(game->player_bullets, MAX_PLAYER_BULLETS);
    int bullet_index2 =
        Bullet_list_get_free_index(game->player_bullets, MAX_PLAYER_BULLETS);
    if (bullet_index1 != -1 && bullet_index2 != -1) {
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

void clean_game(Game *game)
{
  MLV_free_image(game->player_sprite);
  MLV_free_image(game->enemy_sprite);
  MLV_free_image(game->player_bullet_sprite);
  MLV_free_image(game->enemy_bullet_sprite);
  stars_cleanup(&game->stars);
}