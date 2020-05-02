/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Rooms Debugger
*/

#include <stdlib.h>

#include "rpg.h"
#include "my.h"

void show_informations(info_t **infos)
{
    for (int i = 0; infos && infos[i]; i++) {
        my_printf("Info %d :\n", i);
        my_printf("Type : %d\n", infos[i]->type);
        my_printf("Pos : x = %f y = %f\n", infos[i]->pos.x, infos[i]->pos.y);
        if (infos[i]->type == 2)
            my_printf("Object ID = %d\n", infos[i]->id_obj);
    }
}

void show_room(room_t *room)
{
    show_informations(room->info);
}

void show_rooms_information(room_t **rooms)
{
    for (int i = 0; rooms && rooms[i]; i++) {
        show_room(rooms[i]);
    }
}