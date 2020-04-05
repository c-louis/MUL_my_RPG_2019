/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Draw loop
*/

#include "rpg.h"

void main_loop(sfRenderWindow *window, globals_t *gl)
{
    sfTime time = sfClock_getElapsedTime(gl->clock);
    sfInt32 i_time = sfTime_asMicroseconds(time);
    float f_time = ((float) i_time) / 100;

    sfShader_setFloatParameter(gl->shader, "u_time", f_time);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, gl->sprite, gl->state);
    sfRenderWindow_display(window);
}
