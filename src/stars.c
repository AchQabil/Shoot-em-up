#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/stars.h"

#include "../include/game.h"

void stars_init(Stars *stars)
{
  for (int i = 0; i < MAX_STARS; i++)
  {
    stars->active[i] = 0;
    stars->image[i] = NULL;
  }
}

void stars_create_star(Stars *stars, int num_stars)
{
  for (int i = 0; i < num_stars; i++)
  {
    int index = -1;
    for (int j = 0; j < MAX_STARS; j++)
    {
      if (!stars->active[j])
      {
        index = j;
        break;
      }
    }

    if (index != -1)
    {
      if (stars->image[index] == NULL)
      {
        stars->image[index] = MLV_load_image("data/img/star.png");
        if (stars->image[index] == NULL)
        {
          printf("Erreur lors du chargement de l'image\n ");
          exit(1);
        }
        MLV_resize_image_with_proportions(stars->image[index], STAR_WIDTH, STAR_HEIGHT);
      }

      stars->active[index] = 1;
      stars->x[index] = rand() % WIDTH;
      stars->y[index] = 0;
      stars->speed[index] = rand() % 4 + 2;
    }
  }
}

void stars_update(Stars *stars)
{
  for (int i = 0; i < MAX_STARS; i++)
  {
    if (stars->active[i])
    {
      stars->y[i] += stars->speed[i];

      if (stars->y[i] > HEIGHT)
      {
        stars->active[i] = 0;
      }
    }
  }
}

void stars_draw(const Stars *stars)
{
  for (int i = 0; i < MAX_STARS; i++)
  {
    if (stars->active[i])
    {
      MLV_draw_image(stars->image[i], stars->x[i], stars->y[i]);
    }
  }
}

void stars_cleanup(Stars *stars)
{
  for (int i = 0; i < MAX_STARS; i++)
  {
    if (stars->image[i] != NULL)
    {
      MLV_free_image(stars->image[i]);
      stars->image[i] = NULL;
    }
  }
}