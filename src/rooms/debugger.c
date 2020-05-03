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

void show_entities(entity_t **npc, entity_t **enemies)
{
    for (int i = 0; npc && npc[i]; i++) {
        my_printf("NPC %d :\n", i);
        my_printf("Pos : x = %f y = %f\n", npc[i]->pos.x, npc[i]->pos.y);
    }
    for (int i = 0; enemies && enemies[i]; i++) {
        my_printf("ENEMY %d :\n", i);
        my_printf("Pos : x = %f y = %f\n", enemies[i]->pos.x, enemies[i]->pos.y);
    }
}

void show_room(room_t *room)
{
    show_informations(room->info);
    show_entities(room->npc, room->enemies);
}

void show_rooms_information(room_t **rooms)
{
    /*for (int i = 0; rooms && rooms[i]; i++) {
        my_printf("ROOM %d :\n", i);
        show_room(rooms[i]);
    }*/
}