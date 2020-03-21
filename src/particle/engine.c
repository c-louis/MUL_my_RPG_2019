/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** particle engine
*/

#include <stdlib.h>

#include "particle.h"
#include "my.h"

void set_pixel(framebuffer_t *fb, int x, int y, sfColor color)
{
    int pos = (x + fb->width * y) * 4;

    fb->pixels[pos + 0] = color.r;
    fb->pixels[pos + 1] = color.g;
    fb->pixels[pos + 2] = color.b;
    fb->pixels[pos + 3] = color.a;
}

framebuffer_t *create_framebuffer(sfVideoMode mode)
{
    framebuffer_t *fb = malloc(sizeof(framebuffer_t));

    if (!fb)
        return (0);
    fb->pixels = malloc(sizeof(char) * (mode.width * mode.height * 4));
    fb->width = mode.width;
    fb->height = mode.height;
    return (fb);
}

part_t *create_engine(sfVideoMode mode)
{
    part_t *engine = malloc(sizeof(part_t));

    if (!engine)
        return (0);
    engine->fb = create_framebuffer(mode);
    engine->fb_tex = sfTexture_create(mode.width, mode.height);
    engine->res = sfSprite_create();
    engine->systems = malloc(sizeof(syst_t *));
    if (!engine->systems)
        return (0);
    engine->systems[0] = 0;
    sfTexture_updateFromPixels(engine->fb_tex, engine->fb->pixels,
        mode.width, mode.height, 0, 0);
    sfSprite_setTexture(engine->res, engine->fb_tex, sfTrue);
    return (engine);
}

void append_system(part_t *engine, syst_t *system)
{
    int sys_len = 0;

    if (!engine || !system || !engine->systems)
        return;
    for (; engine->systems[sys_len] != 0; sys_len++);
    engine->systems = my_realloc(engine->systems,
        sizeof(syst_t *) * (sys_len + 1), sizeof(syst_t *) * (sys_len + 2));
    engine->systems[sys_len] = system;
    engine->systems[sys_len + 1] = 0;
}

void remove_system(part_t *engine, syst_t *system)
{
    return;
}
