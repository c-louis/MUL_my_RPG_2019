/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** map header for struct and dico
*/

enum entity_type {
    ENEMY,
    PLAYER,
    NPC
};

typedef struct point {
    int x;
    int y;
} point_t;

typedef struct entity {
    enum entity_type type;
    point_t position;
    char *dialog;
} mp_entity_t;

typedef struct shape {
    point_t point[9]; // Octogon maximum
} shape_t;

typedef struct light {
    point_t position;
    float radius;
    int default_state; // [0,1]
} light_room_t;

typedef struct room {
    int height;
    int width;
    unsigned char color[4];
    shape_t shapes[16];
    mp_entity_t entities[20];
    light_room_t lights[10];
} h_room_t;

static const h_room_t room_example =
{
    1920,
    1080,
    {255, 255, 255, 255},
    {
        (shape_t) {
            (point_t) {100, 100},
            (point_t) {100, 50},
            (point_t) {150, 50},
            (point_t) {150, 100},
            (point_t) {-1, -1}
        },
        (shape_t) {
            (point_t) {50, 0},
            (point_t) {100, 0},
            (point_t) {100, 1000},
            (point_t) {50, 1000},
            (point_t) {-1, -1}
        },
        (shape_t) {
            (point_t) {-1, -1}
        }
    },
    {
        (mp_entity_t) {
            (enum entity_type) PLAYER,
            (point_t) {100, 200},
            0
        },
        (mp_entity_t) {
            (enum entity_type) NPC,
            (point_t) {110, 210},
            "dialog/npc_1.dialog"
        },
        (mp_entity_t) {
            (enum entity_type) ENEMY,
            (point_t) {1000, 2000},
            0
        }
    },
    {
        (light_room_t) {
            (point_t) {101, 201},
            42,
            1
        }
    }
};
