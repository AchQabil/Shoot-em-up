#include "../include/graphics.h"

void graphics_init(int width, int height, const char *title)
{
    MLV_create_window(title, title, width, height);
}

void graphics_clear()
{
    MLV_clear_window(MLV_COLOR_BLACK);
}

void graphics_draw_image(const MLV_Image *image, int x, int y)
{
    MLV_draw_image(image, x, y);
}

void graphics_update()
{
    MLV_update_window();
}

void graphics_cleanup()
{
    MLV_free_window();
}