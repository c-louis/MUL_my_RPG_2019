/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** raycast
*/

#include "rpg.h"
#include "engine.h"
#include "my.h"

float get_distance(sfVector2f, sfVector2f);

int is_on_end(globals_t *gl)
{
    entity_t *player = gl->player;
    info_t *end_point = get_room_end(gl->rooms[gl->room_index]);

    if (get_distance(player->pos, end_point->pos) <= 100)
        return (1);
    return (0);
}

void swap_room_event(sfEvent *event, globals_t *gl)
{
    if (is_on_end(gl) && event->type == sfEvtKeyPressed
        && event->key.code == sfKeyE) {
        gl->room_index = gl->room_index + 1;
    }
}

void show_swap_room_key(sfRenderWindow *window, globals_t *gl)
{
    info_t *end_point = get_room_end(gl->rooms[gl->room_index]);

    if (!is_on_end(gl))
        return;
    if (!end_point) {
        my_printf("No endpoint in the room !\n");
        return;
    }
    sfText_setPosition(gl->end_room, end_point->pos);
}