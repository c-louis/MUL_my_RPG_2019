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
#include "hud.h"
#include "particle.h"

typedef struct gl {
    sfVideoMode mode;
    sfShader *shader;
    sfRenderStates *state;
    sfClock *clock;
    room_t **rooms;
    sfConvexShape ***light_polys;
    entity_t *player;
    sfView *main_view;
    sfView *hud_view;
    e_bank_t *bank;
    sfGlslVec3  *light_shader_obj;
    sfText *end_room;
    sfText *quest;
    int room_index;
    hud_t *hud;
    part_t *particle;
} globals_t;

typedef struct file {
    unsigned char *data;
    int data_size;
    globals_t *gl;
} dfile_t;

void clean_memory(globals_t *gl);
void handle_event(sfRenderWindow *window, sfEvent *event, globals_t *gl);
void init_globals(globals_t *gl);
void main_loop(sfRenderWindow *window, globals_t *gl);

// init Hud
void init_hud(globals_t *gl);
void set_points(sfConvexShape *shape, sfFloatRect rect);
void update_ends(globals_t *gl);
void consume_item(globals_t *gl, sfEvent *event);

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
void mouse_move_event(sfEvent *, entity_t *, globals_t *, sfRenderWindow *);
int move_entity(entity_t *entity, sfVector2f to, int speed, globals_t *gl);
int move_player_event(sfRenderWindow *window, sfEvent *event, globals_t *gl);
void move_camera(globals_t *gl);

// Room init
int add_wall(dfile_t *a_data, room_t *room, int *i);
int add_room(room_t ***rooms, int *size, dfile_t *data, int *i);
int add_light(dfile_t *a_data, room_t *room, int *i);
room_t **get_rooms(char *path, globals_t *gl);
e_bank_t *get_enemies(char *path);

// Entity copy init
entity_t *init_new_enemy(dfile_t *data, sfVector2f pos, char info[3]);
entity_t *init_new_npc(dfile_t *data, sfVector2f pos, char info[3]);

// Handling
int add_info(dfile_t *a_data, room_t *room, int *i);
int add_entity(dfile_t *a_data, room_t *room, int *i);
int add_body_to_en(dfile_t *a_data, entity_t *entity, int *i, int j);
int add_loot(entity_t *entity, dfile_t *data, int *i);
int add_item(e_bank_t *bank, int *item_size, dfile_t *data, int *i);
int add_body_to_item(dfile_t *a_data, loot_t *item, int *i, int j);
int add_enemy_static(e_bank_t *bank, int *size, dfile_t *data, int *i);
void check_enemies_life(globals_t *gl);
int move_enemy(entity_t *entity, globals_t *gl);

// Light handling
int check_bound(sfVector2f *buf, sfVector2f from, sfVector2f to,
    sfFloatRect rect);
int check_raycast(sfVector2f *buf, sfFloatRect rect, int *written,
    sfConvexShape *shape);

// Debugger functions
void show_rooms_information(room_t **rooms);
void show_bank_information(e_bank_t *bank);
void show_bank_loots(loot_t **loots);
void show_entities(entity_t **npc, entity_t **e);

// Gameplay function
int is_on_end(globals_t *gl);
void swap_room_event(sfEvent *event, globals_t *gl);
void show_swap_room_key(sfRenderWindow *window, globals_t *gl);

void add_item_to_word(globals_t *gl, int id, sfVector2f pos);
void remove_item_from_word(globals_t *gl, loot_t *loot);
loot_t *copy_item(globals_t *gl, int id);

#endif
