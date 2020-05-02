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

#include "engine.h"

typedef struct gl {
    sfVideoMode mode;
    sfRenderTexture *tex;
    sfSprite *sprite;
    sfShader *shader;
    sfRenderStates *state;
    sfClock *clock;
    room_t **rooms;
    entity_t *player;
    int room_index;
} globals_t;

void clean_memory(globals_t *gl);

void handle_event(sfRenderWindow *window, sfEvent *event, globals_t *gl);

void init_globals(globals_t *gl);

void main_loop(sfRenderWindow *window, globals_t *gl);

//Player init
int init_player(globals_t *room);

//Player movement function
void mouse_move_event(sfEvent *event, entity_t *player, globals_t *gl);
void move_entity(entity_t *entity, sfVector2f to, int speed, globals_t *gl);
int move_player_event(sfRenderWindow *window, sfEvent *event, globals_t *gl);

#endif
