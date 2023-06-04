#include "../include/graphics.h"

void graphics_init(int width, int height, const char *title){
    MLV_create_window(title, title, width, height);
}

void graphics_clear(){
    MLV_clear_window(MLV_COLOR_BLACK);
}

void graphics_draw_image(const MLV_Image *image, int x, int y){
    MLV_draw_image(image, x, y);
}

void graphics_draw_rectangle(int x, int y, int width, int height, MLV_Color color) {
    MLV_draw_filled_rectangle(x, y, width, height, color);
}


void graphics_draw_text(const char* text, int x, int y, MLV_Color color) {
    MLV_draw_text(x, y, text, color);
}

void graphics_update(){
    MLV_update_window();
}

void graphics_cleanup(){
    MLV_free_window();
}