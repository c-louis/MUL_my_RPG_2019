/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Particle handling
*/

#include <stdlib.h>

#include "particle.h"

point_t *create_particle(descriptor_t *desc)
{
    point_t *part = malloc(sizeof(point_t));

    if (!part || !desc)
        return (0);
    part->next = 0;
    part->prev = 0;
    part->life = 0;
    part->color = desc->color[0];
    part->pos = desc->org[0];
    part->vel = (sfVector2f){desc->speed[0], desc->speed[0]};
    return (part);
}
