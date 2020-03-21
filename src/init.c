/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Init assets
*/

#include "rpg.h"

void init_globals(globals_t *gl)
{
    gl->mode = (sfVideoMode) {1920, 1080, 32};
    gl->clock = sfClock_create();
    gl->engine = create_engine(gl->mode);
    append_system(gl->engine, create_system());
}
