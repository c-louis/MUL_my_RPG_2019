/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** struct_csfml
*/

#ifndef STRUCT_CSFML_H_
#define STRUCT_CSFML_H_

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>


// Static Non-Build Struct

typedef struct s_sprite
{
    char *pathname;
    sfSprite *img;
    sfTexture *texture;
    sfVector2f speed;
    sfIntRect *rect;
    sfVector2f vect;
    sfVector2f init;
}sprite_t;

typedef struct s_button
{
    sprite_t b_sprite;
    sfFloatRect rect;
    sfIntRect rect_tab[3];
    int current_rect;
    int (*fct) (void *data, void *win, void *game);
}button_t;


// Static Pre-Build Struct

typedef struct s_init_sprite
{
    char *path;
    int x_coor;
    int y_coor;
}init_sprite_t;

typedef struct s_init_but
{
    char *path;
    int x_coor;
    int y_coor;
    int (*fct) (void *data, void *win, void *game);
    float rect_height;
    float rect_width;
    sfIntRect rect_tab[3];
}init_but_t;

#endif /* !STRUCT_CSFML_H_ */