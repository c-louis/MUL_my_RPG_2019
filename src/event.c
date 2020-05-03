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
}
