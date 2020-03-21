/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** particle engine animation
*/

#include "particle.h"

void animate_particle(point_t *particle, double delta)
{
    particle->pos.x += particle->vel.x * delta;
    particle->pos.y += particle->vel.y * delta;
    particle->life += delta;
}

void animate_system(syst_t *system, double delta)
{
    descriptor_t *desc = system->desc;

    if (system->timer <= 0){
        append_particle(system, create_particle(desc));
        system->timer = desc->lifetime / desc->qty;
    }
    system->timer -= delta;
    for (point_t *pt = system->pt_head; pt != 0; pt = pt->next)
        animate_particle(pt, delta);
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
        animate_system(engine->systems[i], delta);
    for (int i = 0; engine->systems[i] != 0; i++)
        for (point_t *pt = engine->systems[i]->pt_head; pt != 0; pt = pt->next)
            set_pixel(engine->fb, pt->pos.x, pt->pos.y, sfYellow);
    update_engine(engine);
}
