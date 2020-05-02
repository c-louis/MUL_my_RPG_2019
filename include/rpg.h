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
    //sfRenderTexture *tex;
    //sfSprite *sprite;
    sfShader *shader;
    sfRenderStates *state;
    sfClock *clock;
    room_t **rooms;
    sfConvexShape ***light_polys;
    entity_t *player;
    sfView *main_view;
    sfView *hud_view;
    int room_index;
} globals_t;

void clean_memory(globals_t *gl);

void handle_event(sfRenderWindow *window, sfEvent *event, globals_t *gl);

void init_globals(globals_t *gl);

void main_loop(sfRenderWindow *window, globals_t *gl);

// light
int alloc_poly_light(sfConvexShape ***poly, room_t *room, light_t *light);
sfConvexShape ***alloc_polygones(room_t *room);
void free_polygones(sfConvexShape ***poly);

sfVector2f get_inter(sfVector2f from, sfVector2f to, sfVector2f f_p,
    sfVector2f t_p);

sfVector2f *get_raycasts(light_t *light, room_t *room, int, int);
int get_point_counts(room_t *room);
void update_lights(sfConvexShape ***poly, globals_t *gl);

void do_raycast(sfVector2f *buf, sfVector2f from, sfVector2f to, room_t *room);
void clean_rays(sfVector2f *casts, light_t *light, room_t *room);

//Player init
int init_player(globals_t *room);

//Player movement function
void mouse_move_event(sfEvent *event, entity_t *player, globals_t *gl, sfRenderWindow *window);
void move_entity(entity_t *entity, sfVector2f to, int speed, globals_t *gl);
int move_player_event(sfRenderWindow *window, sfEvent *event, globals_t *gl);

#endif
