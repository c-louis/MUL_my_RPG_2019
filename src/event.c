/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** event handling
*/

#include "rpg.h"

void handle_event(sfRenderWindow *window, sfEvent *event, globals_t *gl)
{
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event->type == sfEvtKeyPressed) {
        move_player_event(window, event, gl);
        show_swap_room_key(window, gl);
        swap_room_event(event, gl);
        attack_event(window, gl, event);
    }
    if (event->type == sfEvtMouseMoved)
        mouse_move_event(event, gl->player, gl, window);
}
