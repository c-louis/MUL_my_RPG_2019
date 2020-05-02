/*
** EPITECH PROJECT, 2019
** my_header
** File description:
** Header for the game engine
*/

#ifndef _RPG_ENGINE_H
#define _RPG_ENGINE_H

#include <SFML/Window.h>
#include <SFML/Graphics.h>

enum direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

enum weapon_type {
    DISTANCE,
    BODY
};

typedef struct weapon {
    enum weapon_type type;
    float damage;
    float range;
} weapon_t;

typedef struct loot_bank {
    sfConvexShape **body;
} loot_t;

typedef struct loot_table {
    unsigned char id;
    unsigned char quantity;
    unsigned char prob;
} loot_table_t;

typedef struct entity_stat {
    float health;
    float speed;
    float rotationspeed;
    float armor;
} entity_stat_t;

typedef struct information {
    unsigned char type;
    sfVector2f pos;
    char id_obj;
} info_t;

typedef struct entity {
    sfConvexShape **body;
    sfVector2f pos;
    entity_stat_t *stat;
    loot_table_t **loot_table;
} entity_t;

typedef struct s_light {
    sfVector2f position;
    float radius;
    sfBool state;
} light_t;

typedef struct s_room {
    sfVector2i size;
    light_t **lights;
    entity_t **enemies;
    entity_t **npc;
    info_t **info;
    sfConvexShape **walls;
    sfColor color;
    sfTexture *tex;
} room_t;

typedef struct file {
    unsigned char *data;
    int data_size;
} dfile_t;

typedef struct entity_bank {
    entity_t **enemies_bank;
    entity_t **npc_bank;
    loot_t **loot;
} e_bank_t;

int add_wall(dfile_t *a_data, room_t *room, int *i);
int add_room(room_t ***rooms, int *size, dfile_t *data, int *i);
int add_light(dfile_t *a_data, room_t *room, int *i);
room_t **get_rooms(char *path);

// Handling
int add_info(dfile_t *a_data, room_t *room, int *i);
int add_entity(dfile_t *a_data, room_t *room, int *i);
int add_body_to_en(dfile_t *a_data, entity_t *entity, int *i, int j);
int add_loot(entity_t *entity, dfile_t *data, int *i);
int add_item(e_bank_t *bank, int *item_size, dfile_t *data, int *i);
int add_body_to_item(dfile_t *a_data, loot_t *item, int *i, int j);
int add_enemy_static(e_bank_t *bank, int *size, dfile_t *data, int *i);

// Math utils
float get_angle(sfVector2f player, sfVector2f mouse);
float get_orientation(sfVector2f a, sfVector2f b, sfVector2f p);
int is_colliding(sfConvexShape *shape, sfVector2f point);
int are_shape_colliding(sfConvexShape *shape1, sfConvexShape *shape2);

// entity drawing
int draw_entity(sfRenderWindow *window, entity_t *entity);

// Entity movement
int is_newpos_colliding_walls(sfConvexShape *shape, sfConvexShape **w);

// File handling
char *read_file(char *path);
int get_filesize(char *path);

// Room Getter
info_t *get_room_start(room_t *room);
info_t *get_room_end(room_t *room);

#endif
