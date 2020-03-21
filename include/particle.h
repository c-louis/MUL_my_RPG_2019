/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** particle engine header
*/

#ifndef _PAR_H
#define _PAR_H

#include <SFML/Graphics.h>
#include <SFML/Window.h>

#define DIR_DOWN  (0 >> 0)
#define DIR_UP    (1 >> 0)
#define DIR_LEFT  (1 >> 1)
#define DIR_RIGHT (1 >> 1 || 1 >> 0)

#define vert(x) (x == DIR_UP || x == DIR_DOWN)

typedef struct fb {
    char *pixels;
    int width;
    int height;
} framebuffer_t;

typedef struct desc {
    sfColor *color;
    int *size;
    double offset;
    double *speed;
    double lifetime;
    double duration;
    int qty;
    char flags;
    sfVector2f *dir;
    sfVector2f *org;
    char id;
    double timer;
} descriptor_t;

typedef struct pt {
    struct pt *next;
    struct pt *prev;
    sfVector2f pos;
    sfVector2f vel;
    sfColor color;
    double life;
} point_t;

typedef struct sys {
    descriptor_t *desc;
    point_t *pt_head;
} syst_t;

typedef struct par {
    framebuffer_t *fb;
    sfTexture *fb_tex;
    sfSprite *res;
    syst_t **systems;
} part_t;

part_t *create_engine(sfVideoMode mode);
descriptor_t *create_descriptor(void);
syst_t *create_system(void);

void append_particle(syst_t *system, point_t *particle);
void delete_particle(syst_t *system, point_t *particle);

void append_system(part_t *engine, syst_t *system);
void remove_system(part_t *engine, syst_t *system);

void desc_append_color(descriptor_t *desc, sfColor color);
void desc_append_size(descriptor_t *desc, int n_size);
void desc_append_speed(descriptor_t *desc, double n_speed);

void desc_set_region_square(descriptor_t *desc, sfIntRect rect, char dir);

void animate_engine(part_t *engine, double delta);

#endif
