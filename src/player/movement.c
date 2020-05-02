/*
** EPITECH PROJECT, 2020
** rpg
** File description:
** Allow Player to move
*/

#include <stdlib.h>

#include "rpg.h"

int is_newpos_colliding_walls(sfConvexShape *shape, sfConvexShape **w) {
    for (int i = 0; w[i]; i++) {
        if (are_shape_colliding(w[i], shape)
            || are_shape_colliding(shape, w[i])) {
            return (1);
        }
    }
    return (0);
}

void move_camera(globals_t *gl)
{
    sfVector2f player = gl->player->pos;

    sfView_setCenter(gl->main_view, player);
}

int move_player_event(sfRenderWindow *window, sfEvent *event, globals_t *gl)
{
    entity_t *p = gl->player;
    sfVector2i mouse_i = sfMouse_getPositionRenderWindow(window);
    sfVector2f mouse =
        sfRenderWindow_mapPixelToCoords(window, mouse_i, gl->main_view);
    int s = 5 + (event->key.shift == sfTrue ? 10 : 0);

    switch(event->key.code) {
        case sfKeyZ:
            return (move_entity(p, mouse, s, gl));
        case sfKeyQ:
            return (move_entity(p, (sfVector2f) {-mouse.x, mouse.y}, s, gl));
        case sfKeyS:
            return (move_entity(p, (sfVector2f) {-mouse.x, -mouse.y}, s, gl));
        case sfKeyD:
            return (move_entity(p, (sfVector2f) {mouse.x, -mouse.y}, s, gl));
    }
    return (0);
}