/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** particle engine animation
*/

#include "particle.h"

void animate_particle(point_t *particle, double delta)
{
    return;
}

void animate_system(syst_t *system, double delta)
{
    if (system->timer <= 0){
        append_particle(system, create_particle());
        system->timer = system->lifetime / qty;
    }
    for (point_t *pt = system->pt_head; pt != 0; pt = pt->next)
        animate_particle(pt, delta);
}

void animate_engine(part_t *engine, double delta)
{
    for (int i = 0; engine->systems[i] != 0; i++)
        animate_system(engine->systems[i], delta);
}
