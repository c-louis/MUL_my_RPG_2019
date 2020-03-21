/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** System movements description
*/

#include <stdlib.h>

#include "particle.h"
#include "my.h"

void desc_set_region_square(descriptor_t *desc, sfIntRect rect, char dir)
{
    int pt_nb = abs(vert(dir) ? rect.top - rect.width :
        rect.left - rect.height) / 10;
    int pt_start = vert(dir) ? rect.left : rect.top;
    int pt_end = vert(dir) ? rect.width : rect.height;
    int pt_step = (pt_end - pt_start) / pt_nb;
    int pt_dx = vert(dir) ? rect.width : 0;
    int pt_dy = vert(dir) ? 0 : rect.height;

    free(desc->org);
    free(desc->dir);
    desc->dir = 0;
    desc->org = malloc(sizeof(sfVector2f) * (pt_nb + 1));
    desc->org[pt_nb] = (sfVector2f) {-1, -1};
    for (int i = 0; i < pt_nb; i ++)
        desc->org[i] = (sfVector2f) {rect.top + pt_dx * i,
            rect.left + pt_dy * i};
}
