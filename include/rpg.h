/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** main header
*/

#ifndef _RPG_H
#define _RPG_H

#define USAGE ""                                \
    "./my_rpg\n"

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>

typedef struct gl {
    sfVideoMode mode;
    sfTexture *tex;
    sfSprite *sprite;
    sfShader *shader;
    sfRenderStates *state;
    sfClock *clock;
} globals_t;

void clean_memory(globals_t *gl);

void handle_event(sfRenderWindow *window, sfEvent *event, globals_t *gl);

void init_globals(globals_t *gl);

void main_loop(sfRenderWindow *window, globals_t *gl);


#endif
