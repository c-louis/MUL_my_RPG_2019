/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Draw loop
*/

#include "rpg.h"

void main_loop(sfRenderWindow *window, globals_t *gl)
{
    sfTime time = sfClock_restart(gl->clock);
    double delta = sfTime_asMilliseconds(time) / 16000;

    animate_engine(gl->engine, delta);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, gl->engine->res, NULL);
    sfRenderWindow_display(window);
}
