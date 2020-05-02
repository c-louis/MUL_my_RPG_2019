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

enum weapon_type {
    DISTANCE,
    BODY
};

typedef struct weapon {
    enum weapon_type type;
    float damage;
    float range;
} weapon_t;

typedef struct entity_stat {
    float health;
    float speed;
    float rotationSpeed;
    float armor;
} entity_stat_t;

typedef struct entity {
    sfConvexShape **body;
    entity_stat_t *stat;
} entity_t;

typedef struct s_light {
    sfVector2f position;
    float radius;
    sfBool state;
} light_t;

typedef struct s_room {
    sfVector2i size;
    light_t **lights;
    entity_t *player;
    entity_t **enemies;
    entity_t **npc;
    sfConvexShape **walls;
    sfColor color;
    sfTexture *tex;
} room_t;

typedef struct s_engine {
    sfSprite *background;
    //sfRenderState *shader;
    room_t **rooms;
} map_engine_t;

typedef struct file {
    unsigned char *data;
    int data_size;
} dfile_t;

int add_wall(dfile_t *a_data, room_t *room, int *i);
int add_room(room_t ***rooms, int *size, dfile_t *data, int *i);
int add_light(dfile_t *a_data, room_t *room, int *i);
room_t **get_rooms(char *path);

#endif
