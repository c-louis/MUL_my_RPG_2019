/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** raycast utils
*/

#include "engine.h"
#include "rpg.h"

int get_point_counts(room_t *room)
{
    int count = 0;

    //TODO: add only if in window bounds
    for (int i = 0; room->walls && room->walls[i] != 0; i++)
        count += sfConvexShape_getPointCount(room->walls[i]) * 3;
    return (count + 4);
}

int check_raycast(sfVector2f *buf, sfVector2f from, sfVector2f to,
    sfConvexShape *shape)
{
    int points = sfConvexShape_getPointCount(shape);
    sfVector2f f_p;
    sfVector2f t_p;
    sfVector2f res;

    for (int i = 0; i < points - 1; i++){
        f_p = sfConvexShape_getPoint(shape, i);
        t_p = sfConvexShape_getPoint(shape, i + 1);
        res = get_inter(from, to, f_p, t_p);
        if (res.x != -1 && res.y != -1){
            *buf = res;
            return (1);
        }
    }
    return (0);
}

int check_bound(sfVector2f *buf, sfVector2f from, sfVector2f to,
    sfFloatRect rect)
{
    sfVector2f bound = get_inter(from, to, (sfVector2f) {rect.left,
        rect.top}, (sfVector2f) {rect.width, rect.height});

    if (bound.x != -1 && bound.y != -1){
        *buf = bound;
        return (1);
    }
    return (0);
}
