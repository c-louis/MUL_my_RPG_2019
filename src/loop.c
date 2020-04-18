/*
** EPITECH PROJECT, 2020
** my_rpg
** File description:
** Draw loop
*/

#include "rpg.h"

void draw_background(sfRenderWindow *window, globals_t *gl)
{
    room_t *room = gl->rooms[0];

    for (int i = 0; room->walls && room->walls[i]; i++) {
        sfRenderWindow_drawConvexShape(window, room->walls[i], 0);
        //printf("Drawing wall %i! \n", i);
    }
    sfTexture_updateFromRenderWindow(room->tex, window, 0, 0);
    sfSprite_setTexture(gl->sprite, room->tex, 0);
    //sfRenderWindow_drawSprite(window, gl->sprite, gl->state);
}

void main_loop(sfRenderWindow *window, globals_t *gl)
{
    sfTime time = sfClock_getElapsedTime(gl->clock);
    sfInt32 i_time = sfTime_asMicroseconds(time);
    float f_time = ((float) i_time) / 100;

    draw_background(window, gl);
    sfShader_setFloatParameter(gl->shader, "u_time", f_time);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, gl->sprite, 0);
    sfRenderWindow_display(window);
}
