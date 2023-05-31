#include "../include/game.h"
#include "../include/stars.h"
#include "../include/graphics.h"

void init_game(Game *game)
{
  graphics_init(WIDTH, HEIGHT, "Shoot'em up");

  game->player_sprite = MLV_load_image("data/img/player.png");
  MLV_resize_image(game->player_sprite, PLAYER_WIDTH, PLAYER_HEIGHT);

  // Positionner le joueur
  game->player.x = WIDTH / 2 - PLAYER_WIDTH / 2;
game->player.y = HEIGHT - PLAYER_HEIGHT - 60;

  game->player.width = PLAYER_WIDTH;
  game->player.height = PLAYER_HEIGHT;

  stars_init(&game->stars);
}

void draw_game(const Game *game)
{
  graphics_clear();

  // dessiner les étoiles
  stars_draw(&game->stars);

  // Dessinez le joueur
  MLV_draw_image(game->player_sprite, game->player.x, game->player.y);

  // Actualise l'écran
  MLV_actualise_window();
}

void update_game(Game *game)
{
  bool *quit = false;
  handle_input_game(game, &quit);

  stars_update(&game->stars);
}

void handle_input_game(Game *game, bool *quit)
{
}

void clean_game(Game *game)
{
  MLV_free_image(game->player_sprite);
  stars_cleanup(&game->stars);
}