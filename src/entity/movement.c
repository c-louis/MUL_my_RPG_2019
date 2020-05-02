/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Allow entity to move
*/

#include "rpg.h"

sfVector2f get_newposition(sfVector2f from, sfVector2f to, float speed)
{
    float dx = to.x - from.x;
    float dy = to.y - from.y;
    float steps = (dx < 0 ? -dx : dx) > (dy < 0 ? -dy : dy) ?
        (dx < 0 ? -dx : dx) : (dy < 0 ? -dy : dy);
    float xinc = dx / steps;
    float yinc = dy / steps;

    if (steps == 0)
        return (from);
    if (steps < speed)
        return (to);
    for (int i = 0; i < speed; i++) {
        from.x += xinc;
        from.y += yinc;
    }
    return (from);
}

void move_entity(entity_t *entity, sfVector2f to, int speed, globals_t *gl)
{
    sfVector2f from = entity->pos;
    sfVector2f next_position = get_newposition(from, to, speed);
    sfConvexShape **walls = gl->rooms[gl->room_index]->walls;

    if (!entity || !entity->body)
        return;
    for (int i = 0; entity->body && entity->body[i]; i++) {
        sfConvexShape_setPosition(entity->body[i], next_position);
        if (!is_newpos_colliding_walls(entity->body[i], walls))
            continue;
        for (int y = 0; entity->body && entity->body[y]; y++) {
            sfConvexShape_setPosition(entity->body[y], entity->pos);
        }
        return;
    }
    entity->pos = next_position;
}