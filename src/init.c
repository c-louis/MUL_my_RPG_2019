/*
65;6001;1c** EPITECH PROJECT, 2020
** rpg
** File description:
** Init assets
*/

#include <stdio.h>
#include <stdlib.h>

#include "rpg.h"
#include "engine.h"
#include "my.h"

void init_engine(globals_t *gl)
{
    gl->rooms = get_rooms("assets/map.dat");
    if (!gl->rooms) {
        my_printf("Error in the Map you can't play with this map !\n");
        exit(84);
    }
    gl->player = NULL;
    gl->room_index = 0;
    if (init_player(gl)) {
        my_printf("Error in the Map you can't play with this map !\n");
        exit(84);
    }
}

void init_globals(globals_t *gl)
{
    gl->mode = (sfVideoMode) {1920, 1080, 32};
    gl->tex = sfRenderTexture_create(gl->mode.width, gl->mode.height, sfFalse);
    gl->sprite = sfSprite_create();
    sfSprite_setTexture(gl->sprite, gl->tex, sfTrue);
    gl->clock = sfClock_create();
    init_engine(gl);
}
