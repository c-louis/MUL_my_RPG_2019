/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2019
** File description:
** lib_csfml
*/

#ifndef LIB_CSFML_H_
#define LIB_CSFML_H_

/*

    Library created by Mathieu R. for MUL_my_rpg_2019

*/

#define EXIT_SUCCESS 1
#define EXIT_FAILURE 0
#define EXIT_MALOC 0

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>


// [Window Function]

sfRenderWindow *create_window(sfVideoMode mode, char *title, sfUnit32 style);
sfVideoMode create_video_mode(int width, int height, int bits_per_pixel);


// [Sprite Function]

int init_sprite(sprite_t *sprite, const init_sprite_t *sprite_data);
int create_sprite(sprite_t *sprite);
int init_sprite_texture(sprite_t *sprite, char *pathname);
void init_vector(sprite_t *sprite, float x, float y);


#endif /* !LIB_CSFML_H_ */