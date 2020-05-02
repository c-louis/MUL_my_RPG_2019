/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Allow player to rotate (focus mouse)
*/

#include <stdlib.h>

#include "rpg.h"
#include "engine.h"

void mouse_move_event(sfEvent *event, entity_t *player, globals_t *gl)
{
    sfVector2f mouse;
    float angle = 0;
    float old_angle = sfConvexShape_getRotation(player->body[0]);

    if (event->type != sfEvtMouseMoved)
        return;
    mouse = (sfVector2f) {event->mouseMove.x, event->mouseMove.y};
    angle = get_angle(player->pos, mouse);
    for (int i = 0; player->body[i]; i++) {
        sfConvexShape_setRotation(player->body[i], angle);
        if (!is_newpos_colliding_walls(player->body[i],
            gl->rooms[gl->room_index]->walls))
            continue;
        for (int y = 0; player->body[y]; y++) {
            sfConvexShape_setRotation(player->body[y], old_angle);
        }
        return;
    }
}

// LES TROIS FONCTION EN DESSOUS SOUS A BOUGER DANS DAUTRE FICHIER

int init_player(globals_t *room)
{
    room->player = malloc(sizeof(entity_t));
    if (!room->player)
        return (1);
    room->player->body = malloc(sizeof(sfConvexShape *) * 2);
    if (!room->player->body)
        return (1);
    room->player->body[0] = sfConvexShape_create();
    if (!room->player->body[0])
        return (1);
    sfConvexShape_setPointCount(room->player->body[0], 4);
    sfConvexShape_setPoint(room->player->body[0], 0, (sfVector2f) {0, 0});
    sfConvexShape_setPoint(room->player->body[0], 1, (sfVector2f) {0, 100});
    sfConvexShape_setPoint(room->player->body[0], 2, (sfVector2f) {100, 100});
    sfConvexShape_setPoint(room->player->body[0], 3, (sfVector2f) {100, 0});
    sfConvexShape_setFillColor(room->player->body[0], sfWhite);
    sfConvexShape_setOrigin(room->player->body[0], (sfVector2f) {50, 50});
    sfConvexShape_setPosition(room->player->body[0], (sfVector2f) {500, 500});
    room->player->body[1] = 0;
    room->player->pos = (sfVector2f) {500, 500};
    return (0);
}