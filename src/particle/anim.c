/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** particle engine animation
*/

#include <math.h>

#include "particle.h"

void animate_particle(point_t *particle, double delta)
{
    particle->pos.x += particle->vel.x * delta;
    particle->pos.y += particle->vel.y * delta;
    particle->life += delta;
}

void draw_point(framebuffer_t *fb, point_t *pt, descriptor_t *desc)
{
    sfColor color = desc->color[0];
    int size = desc->size[0];
    double ratio = 0;
    int dx = 0;
    int dy = 0;

    if (!pt || !fb)
        return;
    for (int i = pt->pos.x - size / 2; i < pt->pos.x + size / 2; i++){
        for (int j = pt->pos.y - size / 2; j < pt->pos.y + size / 2; j++){
            dx = i - (int) pt->pos.x;
            dy = j - (int) pt->pos.y;
            ratio = (size - 2 * sqrt(dx * dx + dy * dy)) / size;
            if (ratio <= 0.0f)
                continue;
            color.a = 255 * ratio;
            set_pixel(fb, pt->pos.x + i, pt->pos.y + j, color);
        }
    }
}

void animate_system(framebuffer_t *fb, syst_t *system, double delta)
{
    descriptor_t *desc = system->desc;

    if (system->timer <= 0){
        append_particle(system, create_particle(desc));
        system->timer = desc->lifetime / desc->qty;
    }
    system->timer -= delta;
    for (point_t *pt = system->pt_head; pt != 0; pt = pt->next){
        animate_particle(pt, delta);
        draw_point(fb, pt, desc);
    }
    for (point_t *pt = system->pt_head; pt != 0; pt = pt->next){
        if (pt->life > desc->lifetime){
            delete_particle(system, pt);
            pt = system->pt_head;
        }
    }
}

void animate_engine(part_t *engine, double delta)
{
    clear_fb(engine->fb);
    for (int i = 0; engine->systems[i] != 0; i++)
        animate_system(engine->fb, engine->systems[i], delta);
    update_engine(engine);
}
