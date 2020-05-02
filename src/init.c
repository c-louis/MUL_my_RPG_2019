/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Init assets
*/

#include <stdio.h>
#include <stdlib.h>

#include "rpg.h"
#include "engine.h"
#include "my.h"

int init_player_body(sfConvexShape *shape, sfVector2f pos)
{
    sfConvexShape_setPointCount(shape, 4);
    sfConvexShape_setPoint(shape, 0, (sfVector2f) {0, 0});
    sfConvexShape_setPoint(shape, 1, (sfVector2f) {0, 100});
    sfConvexShape_setPoint(shape, 2, (sfVector2f) {100, 100});
    sfConvexShape_setPoint(shape, 3, (sfVector2f) {100, 0});
    sfConvexShape_setFillColor(shape, sfWhite);
    sfConvexShape_setOrigin(shape, (sfVector2f) {50, 50});
    sfConvexShape_setPosition(shape, pos);
    return (0);
}

int init_player(globals_t *room)
{
    info_t *start = get_room_start(room->rooms[0]);
    sfVector2f pos = start ? start->pos : (sfVector2f) {0, 0};

    if (!start) {
        my_printf("First room must have a start !\n");
        return (1);
    }
    room->player = malloc(sizeof(entity_t));
    if (!room->player)
        return (1);
    room->player->body = malloc(sizeof(sfConvexShape *) * 2);
    if (!room->player->body)
        return (1);
    room->player->body[0] = sfConvexShape_create();
    if (!room->player->body[0])
        return (1);
    init_player_body(room->player->body[0], pos);
    room->player->body[1] = 0;
    room->player->pos = pos;
    return (0);
}

void init_engine(globals_t *gl)
{
    gl->rooms = get_rooms("assets/map.dat");
    if (!gl->rooms) {
        my_printf("Error in the Map you can't play with this map !\n");
        exit(84);
    }
    show_rooms_information(gl->rooms);
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
    gl->clock = sfClock_create();
    gl->main_view = sfView_create();
    gl->hud_view = sfView_create();
    sfView_setSize(gl->main_view, (sfVector2f) {1920, 1080});
    sfView_setSize(gl->hud_view, (sfVector2f) {1920, 1080});
    init_engine(gl);
    sfView_setCenter(gl->main_view, gl->player->pos);
}
