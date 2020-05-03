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

void draw_point(syst_t *syst, point_t *pt,
    sfRenderWindow *window, sfRenderStates *state)
{
    int size = syst->desc->size[0];
    sfColor c = syst->desc->color[0];

    sfSprite_setScale(syst->sprite, (sfVector2f) {size, size});
    sfSprite_setPosition(syst->sprite, (sfVector2f) {pt->pos.x - size / 2, pt->pos.y - size / 2});
    sfShader_setVec2Uniform(state->shader, "u_resolution", (sfGlslVec2) {size, size});
    sfShader_setVec3Uniform(state->shader, "u_color", (sfGlslVec3) {c.r, c.g, c.b});
    sfShader_setIntUniform(state->shader, "u_size", size);
    sfRenderWindow_drawSprite(window, syst->sprite, state);
}

void animate_system(syst_t *system, double delta,
    sfRenderWindow *window, sfRenderStates *state)
{
    descriptor_t *desc = system->desc;

    if (system->timer <= 0){
        append_particle(system, create_particle(desc));
        system->timer = desc->lifetime / desc->qty;
    }
    system->timer -= delta;
    for (point_t *pt = system->pt_head; pt != 0; pt = pt->next){
        animate_particle(pt, delta);
        draw_point(system, pt, window, state);
    }
    for (point_t *pt = system->pt_head; pt != 0; pt = pt->next){
        if (pt->life > desc->lifetime){
            delete_particle(system, pt);
            pt = system->pt_head;
        }
    }
}

void animate_engine(part_t *engine, double delta, sfRenderWindow *window)
{
    for (int i = 0; engine->systems[i] != 0; i++)
        animate_system(engine->systems[i], delta, window, engine->state);
    update_engine(engine, delta);
}
