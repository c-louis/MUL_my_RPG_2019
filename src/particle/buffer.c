/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Framebuffer
*/

#include <stdlib.h>

#include "particle.h"

void set_pixel(framebuffer_t *fb, int x, int y, sfColor color)
{
    int pos = (x + fb->width * y) * 4;
    double ratio;

    if (x < 0 || y < 0 || x >= fb->width || y >= fb->height)
        return;
    if (color.a != 255){
        ratio = (double) color.a / 255;
        fb->pixels[pos + 0] *= (1 - ratio);
        fb->pixels[pos + 1] *= (1 - ratio);
        fb->pixels[pos + 2] *= (1 - ratio);
        fb->pixels[pos + 0] += (ratio) * color.r;
        fb->pixels[pos + 1] += (ratio) * color.g;
        fb->pixels[pos + 2] += (ratio) * color.b;
    }else{
        fb->pixels[pos + 0] = color.r;
        fb->pixels[pos + 1] = color.g;
        fb->pixels[pos + 2] = color.b;
    }
    fb->pixels[pos + 3] = 255;
}

void clear_fb(framebuffer_t *fb)
{
    for (int i = 0; i < fb->width * fb->height * 4; i++)
        fb->pixels[i] = 0;
}

void update_engine(part_t *engine)
{
    sfTexture_updateFromPixels(engine->fb_tex, engine->fb->pixels,
        engine->fb->width, engine->fb->height, 0, 0);
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
